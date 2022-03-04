import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from SummValidation.C_Generator import C_FileGenerator
from SummValidation.ArgGen.Visitors.FunctionArgs import ArgVisitor

from .utils import defineMacro, mainFunction, returnValue, createFunction 
from .utils import InitialVisitor, ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO, stubs


class ValidationGenerator(C_FileGenerator):
	def __init__(self, summary, concrete_func, outputfile,
				 arraysize, summ_name=None, cncr_name = None, fakelib=None):

		super().__init__(outputfile, fakelib)


		self.summary_path = summary
		self.concrete_file = concrete_func
		self.arraysize = arraysize

		#Summary name (if summ is not isolated in a file, e,g in a library)
		self.summ_name = summ_name
		self.cncr_name = cncr_name


	
	#Create validation test
	def create_test(self, c_fname, s_fname, args):


		fblock = []     #Test code to be generated
		call_args = []  #Arguments to call the function		

		#Function has no arguments
		if args is None:
			args = []
		
		#Visit arguments 
		for arg in args:

			vis = ArgVisitor()   
			vis.visit(arg)
			code = vis.gen_code()

			call_args.append(vis.argname)
			fblock += code

		
		#Add the function call to the Ast
		fblock.append(FuncCall(ID(c_fname), ExprList([a for a in map(lambda x: ID(x), call_args)])))
		fblock.append(FuncCall(ID(s_fname), ExprList([a for a in map(lambda x: ID(x), call_args)])))
		
		fblock.append(returnValue(Constant('int', str(0)))) #Return 0

		#Create a block containg the test code
		block = Compound(fblock)

		#Create the actual test function
		decl = createFunction(name='main',
							  args=None,
							  returnType='int')

		#Place the block inside a function definition
		func_def_ast = FuncDef(decl, None, block, None)

		return func_def_ast 


	def _check_functions(self, c_functions, s_functions=None):
		if len(c_functions) == 0:
			sys.exit("No concrete function provided")
		if len(c_functions) > 1:
			sys.exit("There should be only one concrete function to be compared with")

		if s_functions is not None:
			if len(s_functions) == 0:
				sys.exit("No summary provided")
			if len(s_functions) > 1:
				sys.exit("There should be only one target summary")			


	
	def _process_includes(self):
		includes = self._get_includes(self.concrete_file)

		if self.summ_name is None:
			includes += self._get_includes(self.summary_path)


		return list(set([inc for inc in map(lambda x: x.replace(' ', ''), includes)]))


	#Gen test if summary is in a file
	def gen(self):

		try:

			includes = self._process_includes()

			#Add macros for test generation
			includes.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))
			includes.append(defineMacro(POINTER_SIZE_MACRO, self.arraysize))

			#Parse files
			ast_cnctr = parse_file(self.concrete_file, use_cpp=True,
				cpp_path='gcc',
				cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])            


			ast_summ = parse_file(self.summary_path, use_cpp=True,
				cpp_path='gcc',
				cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])

			
			#Initial visitor to get the functions from both files
			vis_cncrt = InitialVisitor(ast_cnctr)
			vis_summ = InitialVisitor(ast_summ)


			cnctr_functions = vis_cncrt.function_names()
			summ_functions = vis_summ.function_names()

			#Check if only one concrete function and summary are provided
			self._check_functions(cnctr_functions, summ_functions)

			cnctr_fname, = cnctr_functions
			summ_fname, = summ_functions

			function_defs = [*vis_summ.function_defs(), *vis_cncrt.function_defs()]

			gen_ast = FileAST(function_defs)

			args, = vis_cncrt.function_args()

			test_ast = self.create_test(cnctr_fname, summ_fname, args)
			gen_ast.ext.append(test_ast)

			#Generate string from ast
			generator = c_generator.CGenerator()
			generated_string = generator.visit(gen_ast)

			file_name = os.path.basename(__file__)
			self._write_to_file(generated_string, includes, file_name, stubs)

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())
