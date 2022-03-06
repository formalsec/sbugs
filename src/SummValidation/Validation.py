import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from SummValidation.CGenerator import CGenerator
from SummValidation.ArgGen.Symbolic_Args import Symbolic_Args
from SummValidation.APIGen.APIGen import API_Gen
from SummValidation.APIGen import API

from SummValidation.Utils.utils import defineMacro, returnValue, createFunction 
from SummValidation.Utils.utils import ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO
from SummValidation.Utils.visitors import InitialVisitor, FCallsVisitor, ReturnTypeVisior


class ValidationGenerator(CGenerator):
	def __init__(self, concrete_func, summary, outputfile,
				 arraysize, summ_name=None, cncrt_name = None, fakelib=None):

		super().__init__(outputfile, summary, concrete_func, fakelib)

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
				sys.exit(f"ERROR: Concrete function not found in the given file: \'{self.concrete_file}\'")
			else:
				cncrt = c_functions[self.cncr_name]

		if self.summ_name:
			if self.summ_name not in s_names:
				sys.exit(f"ERROR: Summary not found in the given file: \'{self.summary_path}\'")
			else:
				summ = c_functions[self.summ_name]


		if not cncrt:

			if len(c_names) == 0:
				sys.exit(f"ERROR: No functions provided in: \'{self.concrete_file}\'")
			
			elif len(c_names) == 1:
				cncrt, = list(c_functions.values())
				self.cncrt_name, = c_names
			
			else: 
				message = ("No function name provided!\n"
						  f"ERROR: There should be only one concrete function to be compared with in \'{self.concrete_file}\'")				
				sys.exit(message)

		if not summ:

			if len(s_names) == 0:
				sys.exit(f"ERROR: No summary provided in: \'{self.summary_path}\'")
			
			elif len(s_names) == 1:
				summ, = list(s_functions.values())
				self.summ_name, = s_names
			
			else:
				message = ("No function name provided!\n"
						  f"ERROR: There should be only one target summary in \'{self.summary_path}\'")
				sys.exit(message)

			return [cncrt, summ]
		

	def _get_function_args(self, defs):
		cncrt_def, summ_def = defs
		
		cncrt_args = cncrt_def.decl.type.args.params if cncrt_def.decl.type.args else None
		summ_args = summ_def.decl.type.args.params if summ_def.decl.type.args else None

		args_vis1 = Symbolic_Args()
		args_vis2 = Symbolic_Args()

		args1 = args_vis1.get_types(cncrt_args)
		args2 = args_vis2.get_types(summ_args)

		if args1 != args2:
			msg = (
				"Arguments do not match!\n"
				f"Summary path: \'{self.summary_path}\'\n"
				f"Concrete Function: \'{self.concrete_file}\'"
				)
			sys.exit(msg)

		return cncrt_args


	def _get_ret_type(self, defs):
		cncrt_def, summ_def = defs

		cncrt_ret = cncrt_def.decl.type.type
		summ_ret = summ_def.decl.type.type

		ret_vis1 = ReturnTypeVisior()
		ret_vis2 = ReturnTypeVisior()

		ret_vis1.visit(cncrt_ret)
		ret_vis2.visit(summ_ret)

		ret1 = ret_vis1.get_ret()
		ret2 = ret_vis2.get_ret()

		if ret1 != ret2:
			msg = (
				"Return values do not match!\n"
				f"Summary path: \'{self.summary_path}\'\n"
				f"Concrete Function: \'{self.concrete_file}\'"
				)
			sys.exit(msg)

		return ret1

	#Parse target functions from the given files
	#Returns (ast_defs, ast_args, ret_type)
	def _parse_functions(self, concrete, summary):
		
		#Parse files
		ast_cnctr = parse_file(concrete, use_cpp=True,
			cpp_path='gcc',
			cpp_args=['-E', f'-I{self.fakelib}'])            
		
		ast_summ = parse_file(summary, use_cpp=True,
			cpp_path='gcc',
			cpp_args=['-E', f'-I{self.fakelib}'])


		#Initial visitor to get the functions from both files
		vis_cncrt = InitialVisitor(ast_cnctr, filename = self.concrete_file)
		vis_summ = InitialVisitor(ast_summ, filename = self.summary_path)

		#Functions in each file
		cnctr_functions = vis_cncrt.functions()
		summ_functions = vis_summ.functions()

		defs = self._get_function_defs(cnctr_functions, summ_functions)
		args = self._get_function_args(defs)
		ret = self._get_ret_type(defs)
		return defs, args, ret


	#Gen headers
	#Typedefs, API stubs and Macros
	def _gen_headers(self, defs):
		_ , summ_def = defs
		
		call_vis = FCallsVisitor()
		call_vis.visit(summ_def)
		calls = call_vis.fcalls()

		headers = []
		headers += API.type_defs
		headers += API.validation_api

		for c in calls:
			if c in API.all_api.keys():
				headers.append(API.all_api[c])
		
		headers.append('\n')

		#Macros
		headers.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))
		headers.append(defineMacro(POINTER_SIZE_MACRO, self.arraysize))
		return headers


	#Generate summary validation test
	def gen(self):
		try:
			tmp_concrete = self._add_fake_include(self.concrete_file)
			tmp_summary = self._add_fake_include(self.summary_path)

			function_defs, args, ret_type = self._parse_functions(tmp_concrete, tmp_summary)
			header = self._gen_headers(function_defs)
						
			#Main function to run the test
			main = createFunction(name='main',
						args=None,
						returnType='int')

			#Helper objects
			sym_args_gen = Symbolic_Args()
			api_gen = API_Gen()

			#Create symbolic args
			args_code, args_names = sym_args_gen.create_symbolic_args(args)
			
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
			self._remove_files(tmp_concrete, tmp_summary)

		except Exception:
			self._remove_files(tmp_concrete, tmp_summary)
			print(traceback.format_exc())

