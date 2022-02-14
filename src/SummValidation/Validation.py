import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from SummValidation.C_Generator import C_FileGenerator


from .utils import defineMacro, defineInclude, mainFunction, returnValue, createFunction 
from .utils import InitialVisitor, FUEL_MACRO, ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO


class ValidationGenerator(C_FileGenerator):
	def __init__(self, summary, concrete_func, outputfile,
				 arraysize, summ_lib, fakelib=None):

		super().__init__(outputfile, fakelib)


		self.summary_path = summary
		self.concrete_file = concrete_func
		self.arraysize = arraysize

		self.summ_lib = summ_lib
		self.fakelib = 'Fake_libc'

		if fakelib is not None:
			self.fakelib = fakelib



	def _place_testcode(self, ast, code, mainblock):

		ast.ext += code
		decl = createFunction(name='main',\
				args=None,returnType='int')
		main = FuncDef(decl, None, mainFunction(mainblock), None)
		ast.ext.append(main)
		return

	
	#Create a single test
	def create_test(self, fname, args, structs, aliases):

		testname = f'test_{fname}'
		
		if fname == 'main':
			return ('main', None) #Ignore 'main' function

		fblock = []     #Test code to be generated
		call_args = []  #Arguments to call the function		

		#Function has no arguments
		if args is None:
			args = []
		
		#Visit arguments 
		for arg in args:

			vis = ArgVisitor(structs, aliases)   
			vis.visit(arg)
			code = vis.gen_code()

			if code is None:
				return (fname, None)
			
			call_args.append(vis.argname)
			fblock += code

		#Constrain global vars denoting numbers
		fblock += self.constrain_numbers(call_args)
	   
		
		#Add the function call to the Ast
		fblock.append(FuncCall(ID(fname), ExprList([a for a in map(lambda x: ID(x), call_args)])))
		fblock.append(returnValue(None)) #Return (void)

		#Create a block containg the test code
		block = Compound(fblock)

		#Create the actual test function
		decl = createFunction(name=testname,
							  args=None,
							  returnType='void')

		#Place the block inside a function definition
		func_def_ast = FuncDef(decl, None, block, None)

		return (testname, func_def_ast) #Return (key,value) tuple


	#Create tests for all functions
	#Returns a dictionary -> {fname : ast}
	def create_tests(self, f_decls, structs, aliases):
		return {k: v for k, v in \
		map(lambda x :self.create_test(x, f_decls[x], structs, aliases), f_decls)\
		if v is not None} 


	def create_symbolic_args(self, function):
		pass

	def _check_functions(self, functions):
		if len(functions) == 0:
			sys.exit("No concrete function provided")
		if len(functions) > 1:
			sys.exit("There should be only one concrete function to be compared with")


	def gen(self):

		try:
			#PreProcess inputfile
			includes = self._preprocess_file(self.concrete_file, self.tmpfile)
			
			#Add macros for teste generation
			includes.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))

			#Parse new file
			ast = parse_file(self.tmpfile, use_cpp=True,
				cpp_path='gcc',
				cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])            

			
			#Initial visitor to get all relevant elements
			vis = InitialVisitor()
			vis.visit(ast)

			functions = vis.functions()
			self._check_functions(functions)

			function = functions[0]

			
			#Place tests to be called in main()
			maincode = []
			maincode.append(f'{function}')


			self._place_testcode(ast, [], maincode)

			#Generate string from ast
			generator = c_generator.CGenerator()
			generated_string = generator.visit(ast)

			self._write_to_file(generated_string, includes)

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())
