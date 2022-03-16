import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from SummValidation.CGenerator import CGenerator
from SummValidation.ArgGen.Symbolic_Args import Symbolic_Args
from SummValidation.APIGen.APIGen import API_Gen
from SummValidation.APIGen import API
from SummValidation.TestGen.TestGen import TestGen

from SummValidation.Utils.utils import defineMacro, returnValue, createFunction 
from SummValidation.Utils.utils import SIZE_MACRO 
from SummValidation.Utils.visitors import InitialVisitor, FCallsVisitor, ReturnTypeVisior


class ValidationGenerator(CGenerator):
	def __init__(self, concrete_func, summary,
				 outputfile,
				 arraysize, memory = False,
				 cncrt_name = None, summ_name=None,
				 fakelib=None):

		super().__init__(outputfile, summary, concrete_func, fakelib)

		self.arraysize = arraysize
		self.memory = memory

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
				self._exit("ERROR: Concrete function not found"
						  "in the given file: \'{self.concrete_file}\'")
			else:
				cncrt = c_functions[self.cncr_name]

		if self.summ_name:
			if self.summ_name not in s_names:
				self._exit("ERROR: Summary not found in"
						 f"the given file: \'{self.summary_path}\'")
			else:
				summ = c_functions[self.summ_name]


		if not cncrt:

			if len(c_names) == 0:
				self._exit(f"ERROR: No functions provided in: \'{self.concrete_file}\'")
			
			elif len(c_names) == 1:
				cncrt, = list(c_functions.values())
				self.cncrt_name, = c_names
			
			else: 
				message = ("No function name provided!\n"
						  "ERROR: There should be only one concrete function"
						  f"to be compared with in \'{self.concrete_file}\'")				
				self._exit(message)

		if not summ:

			if len(s_names) == 0:
				self._exit(f"ERROR: No summary provided in: \'{self.summary_path}\'")
			
			elif len(s_names) == 1:
				summ, = list(s_functions.values())
				self.summ_name, = s_names
			
			else:
				message = ("No function name provided!\n"
						  "ERROR: There should be only one"
						  f"target summary in \'{self.summary_path}\'")
				self._exit(message)

			return [cncrt, summ]
	
		
	#Get function arguments
	def _get_function_args(self, defs):
		cncrt_def, summ_def = defs
		
		cncrt_args = cncrt_def.decl.type.args.params if cncrt_def.decl.type.args else None
		summ_args = summ_def.decl.type.args.params if summ_def.decl.type.args else None

		args_vis1 = Symbolic_Args(cncrt_args)
		args_vis2 = Symbolic_Args(summ_args)

		args1 = args_vis1.get_types()
		args2 = args_vis2.get_types()

		if args1 != args2:
			msg = (
				"Arguments do not match!\n"
				f"Summary path: \'{self.summary_path}\'\n"
				f"Concrete Function: \'{self.concrete_file}\'")
			self._exit(msg)

		return cncrt_args


	#Get return type
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
			self._exit(msg)

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
		
		#Add core api functions
		headers = []
		headers += API.type_defs
		headers += API.validation_api.values()
		headers.append('\n')

		#Visitor to get all function calls
		call_vis = FCallsVisitor()
		call_vis.visit(summ_def)
		calls = call_vis.fcalls()

		#Check if calls are api functions
		#Only add stubs for functions not already added by API.validation_api
		for c in calls: 
			if c in API.all_api.keys():
				stub = API.all_api[c]
				if c not in API.validation_api:
					headers.append(stub)
		headers.append('\n')

		#Size macros
		i = 0
		for size in self.arraysize:	
			i += 1	
			headers.append(defineMacro(f'{SIZE_MACRO}_{i}', size))

		return headers


	#Generate summary validation test
	def gen(self):
		try:
			tmp_concrete = self._add_fake_include(self.concrete_file)
			tmp_summary = self._add_fake_include(self.summary_path)

			function_defs, args, ret_type = self._parse_functions(tmp_concrete, tmp_summary)
			header = self._gen_headers(function_defs)

			#Generation helpers
			api_gen = API_Gen()
			test_gen = TestGen(args, ret_type, self.cncrt_name, self.summ_name, self.memory)
						
			#Main function to run the tests	
			main_body = []
			main = createFunction(name='main',args=None, returnType='int')

			#Save fresh state on which to run all tests
			main_body.append(api_gen.save_current_state('fresh_state'))
				
			i = 0
			test_defs = []
			for i in range(1, len(self.arraysize)+1):

				#Create test 
				test_name = f'test_{i}'
				macro = f'{SIZE_MACRO}_{i}'
				test_defs.append(test_gen.createTest(test_name, macro, i))
				
				#Call test function from main
				main_body.append(FuncCall(ID(test_name), ExprList([])))

				if i < len(self.arraysize):
					main_body.append(api_gen.halt_all('fresh_state'))


			block = Compound(main_body)
			main_ast = FuncDef(main, None, block, None)

			gen_ast = FileAST(function_defs + test_defs)
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

