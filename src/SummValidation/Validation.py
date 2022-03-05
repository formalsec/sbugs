import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from SummValidation.CGenerator import CGenerator
from SummValidation.ArgGen.Symbolic_Args import Symbolic_Args
from SummValidation.APIGen.APIGen import API_Gen
from SummValidation.APIGen import API


from .utils import defineMacro, returnValue, createFunction 
from .utils import InitialVisitor, ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO


class ValidationGenerator(CGenerator):
	def __init__(self, summary, concrete_func, outputfile,
				 arraysize, summ_name=None, cncrt_name = None, fakelib=None):

		super().__init__(outputfile, fakelib)


		self.summary_path = summary
		self.concrete_file = concrete_func
		self.arraysize = arraysize

		#Summary name (if summ is not isolated in a file, e,g in a library)
		self.summ_name = summ_name
		self.cncrt_name = cncrt_name


	#Get the target functions ast_def from the functions in the given files
	def _get_function_defs(self, c_functions, s_functions):
		cncrt = None
		summ = None

		c_names = c_functions.keys()
		s_names = s_functions.keys()

		if self.cncrt_name:
			if self.cncrt_name not in c_names:
				sys.exit(f"Concrete function not found in the given file: \'{self.concrete_file}\'")
			else:
				cncrt = c_functions[self.cncr_name]

		if self.summ_name:
			if self.summ_name not in s_names:
				sys.exit(f"Summary not found in the given file: \'{self.summary_path}\'")
			else:
				summ = c_functions[self.summ_name]


		if not cncrt:

			if len(c_names) == 0:
				sys.exit(f"No functions provided in: \'{self.concrete_file}\'")
			
			elif len(c_names) == 1:
				cncrt, = list(c_functions.values())
				self.cncrt_name, = c_names
			
			else: 
				message = ("No function name provided!"
						  f" There should be only one concrete function to be compared with in \'{self.concrete_file}\'")				
				sys.exit(message)

		if not summ:

			if len(s_names) == 0:
				sys.exit(f"No summary provided in: \'{self.summary_path}\'")
			
			elif len(s_names) == 1:
				summ, = list(s_functions.values())
				self.summ_name, = s_names
			
			else:
				message = ("No function name provided!"
						  f" There should be only one target summary in \'{self.summary_path}\'")
				sys.exit(message)

			return [cncrt, summ]
		

	def _get_function_args(self, defs):
		cncrt_def, summ_def = defs
		return cncrt_def.decl.type.args.params if cncrt_def.decl.type.args else None


	def _get_ret_type(self, defs):
		cncrt_def, summ_def = defs
		return cncrt_def.decl.type.type.type.names[0]
	

	#Parse target functions from the given files
	#Returns (ast_defs, ast_args, ret_type)
	def _parse_functions(self):
		
		#Parse files
		ast_cnctr = parse_file(self.concrete_file, use_cpp=True,
			cpp_path='gcc',
			cpp_args=['-E', f'-I{self.fakelib}'])            
		
		ast_summ = parse_file(self.summary_path, use_cpp=True,
			cpp_path='gcc',
			cpp_args=['-E', f'-I{self.fakelib}'])


		#Initial visitor to get the functions from both files
		vis_cncrt = InitialVisitor(ast_cnctr)
		vis_summ = InitialVisitor(ast_summ)

		#Functions in each file
		cnctr_functions = vis_cncrt.functions()
		summ_functions = vis_summ.functions()

		defs = self._get_function_defs(cnctr_functions, summ_functions)
		args = self._get_function_args(defs)
		ret = self._get_ret_type(defs)
		return defs, args, ret


	#Gen headers
	#Typedefs, API stubs and Macros
	def _gen_headers(self):
		headers = []
		
		#Typedefs
		headers += API.type_defs
		headers.append('\n')
		
		#API stubs
		headers += API.validation_api.values()
		headers.append('\n')

		headers += API.standard_api.values()
		headers.append('\n')

		headers += API.constraints_api.values()
		headers.append('\n')

		#Macros
		headers.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))
		headers.append(defineMacro(POINTER_SIZE_MACRO, self.arraysize))
		return headers


	#Generate summary validation test
	def gen(self):

		try:
			header = self._gen_headers()
			function_defs, args, ret_type = self._parse_functions()

			#Main function to run the test
			main = createFunction(name='main',
						args=None,
						returnType='int')

			#Helper objects
			sym_args_gen = Symbolic_Args()
			api_gen = API_Gen()

			#Create symbolic args
			args_code, args_names = sym_args_gen.create_symbolic_args(args)
			
			#Build Test body
			#Body contains the test code
			body = [
				*args_code,

				api_gen.save_current_state('initial_state'),

				sym_args_gen.call_function(self.cncrt_name, args_names, 'ret1', ret_type),
				api_gen.get_cnstr('cnstr1', 'ret1', ret_type),
				api_gen.add_expr('cnctr', 'cnstr1'),
				
				api_gen.halt_all('initial_state'),

				sym_args_gen.call_function(self.summ_name, args_names, 'ret2', ret_type),			
				api_gen.get_cnstr('cnstr2', 'ret2', ret_type),
				api_gen.add_expr('summ', 'cnstr2'),

				api_gen.check_implications('result', 'cnctr', 'summ'),
				api_gen.print_counterexamples('result'),

				#Return
				returnValue(Constant('int', str(0)))
			]

			#Create main function ast
			block = Compound(body)
			main_ast = FuncDef(main, None, block, None)

			gen_ast = FileAST(function_defs)
			gen_ast.ext.append(main_ast)

			#Generate string from ast
			generator = c_generator.CGenerator()
			generated_string = generator.visit(gen_ast)

			file_name = os.path.basename(__file__)
			self._write_to_file(generated_string, header, file_name)

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())

