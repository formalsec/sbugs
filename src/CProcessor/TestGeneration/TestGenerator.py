import sys, os, traceback

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from CProcessor.C_Generator import C_FileGenerator
from CProcessor import config
from .Visitors.FunctionArgs import ArgVisitor
from .Visitors.Structs import StructVisitor
from .utils import defineMacro, defineInclude, mainFunction, returnValue, createFunction 
from .utils import InitialVisitor, FUEL_MACRO, ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO



class TestGenerator(C_FileGenerator):
	def __init__(self, inputfile, outputfile, fuel,
				 arraysize, pointersize,
				 fakelib=None, save_ast=False, target=None):


		self.fuel = fuel
		self.arraysize = arraysize
		self.pointersize = pointersize
		self.target = target

		super().__init__(inputfile, outputfile,
						 fakelib ,save_ast)
		

	def _place_testcode(self, ast, code, mainblock):
		index = 0
		for stmt in ast.ext:
			if isinstance(stmt, FuncDef):
				if stmt.decl.name == 'main':
					stmt.body = mainFunction(mainblock)
					ast.ext = ast.ext[:index] + code + ast.ext[index:]
					return
			index += 1

		#File does not contain a main function
		ast.ext += code
		decl = createFunction(name='main',\
				args=None,returnType='int')
		main = FuncDef(decl, None, mainFunction(mainblock), None)
		ast.ext.append(main)
		return


	def constrain_number(self, number):
		code = []

		ptr = UnaryOp('&', ID(number))

		if config.CONSTRAIN_UPPER:
			if config.CONSTRAIN_MAX_ARRAY:
				config.GLOBAL_MAX = config.max_array_size

			upper = Constant('int', str(config.GLOBAL_MAX))
			code.append(FuncCall(ID('_assume_leq'), ExprList([ptr, upper])))
		
		if config.CONSTRAIN_LOWER:
			lower = Constant('int', str(config.GLOBAL_MIN))
			code.append(FuncCall(ID('_assume_geq'), ExprList([ptr, lower])))

		return code


	def constrain_numbers(self, args):
		code = []
		if config.global_vars is not None:
			numbers = config.global_vars.numbers()
			for n in numbers:
				if n in args:
					code += self.constrain_number(n)
		return code

	
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


	def gen(self):

		try:
			#PreProcess inputfile
			includes = self._preprocess_file(self.inputfile, self.tmpfile, add_stdlib=True)
			
			#Add macros for teste generation
			includes.append(defineMacro(FUEL_MACRO, self.fuel))
			includes.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))
			includes.append(defineMacro(POINTER_SIZE_MACRO, self.pointersize))


			#Parse new file
			ast = parse_file(self.tmpfile, use_cpp=True,
				cpp_path='gcc',
				cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])            

			#Initial visitor to get all relevant elements
			vis = InitialVisitor()
			vis.visit(ast)

			fun_decls = vis.fun_dict
			structs = vis.structs
			aliases = vis.aliases 

			#Final list of strings to be written to file
			codeList = []

			#Generate functions responsible for creating symbolic structs
			struct_generator = StructVisitor(structs, aliases)
			codeList +=  struct_generator.symbolic_structs()

			#Create actual test functions
			testsDict = self.create_tests(fun_decls, structs, aliases) 
			codeList += testsDict.values()

			#Place tests to be called in main()
			maincode = []
			if self.target:
				maincode.append(f'test_{self.target}')

			else:
				maincode += testsDict.keys()

			self._place_testcode(ast, codeList, maincode)

			#Generate string from ast
			generator = c_generator.CGenerator()
			generated_string = generator.visit(ast)

			#Write ast to temporary file
			tmpfile = open(self.tmpfile, "w")
			tmpfile.write(generated_string)
			tmpfile.flush()

			#PostPreProcess temporary file
			final_code = self._postprocess_file(self.tmpfile, includes,
							 generator=os.path.basename(__file__),
							 stubs=config.stubs)
			

			self._remove_files(self.tmpfile)

			#Write final output file
			outfile = open(self.outputfile, "w")
			outfile.writelines(final_code)

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())
