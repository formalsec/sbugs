#!/usr/bin/env python3

import argparse
import sys, os

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from typeGenerators import InputGenVisitor
from structGenerator import StructGen
from utils import defineMacro, mainFunction, returnValue, createFunction 
from utils import InitialVisitor, FUEL_MACRO, ARRAY_SIZE_MACRO, POINTER_SIZE_MACRO



class testGenerator():
	def __init__(self, inputfile, outputfile, fuel=5, arraysize=10, pointersize=5,\
				 fakelib=None, save_ast=False):
		
		self.inputfile = inputfile
		self.outputfile = outputfile
		
		self.fuel = fuel
		self.arraysize = arraysize
		self.pointersize = pointersize
		
		self.save_ast = save_ast
		self.fakelib = '../Fake_libc'


		if fakelib is not None:
			self.fakelib = fakelib

		#Parse File
		self.ast = parse_file(self.inputfile, use_cpp=True,
			cpp_path='gcc',
			cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])

		if self.save_ast:
			file = open('ast.txt', "w")
			file.write(str(self.ast))


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

			vis = InputGenVisitor(structs,aliases)   
			vis.visit(arg)
			
			call_args.append(vis.argname) 
			fblock += vis.code

	   
		#Add the function call to the Ast
		fblock.append(FuncCall(ID(fname), ExprList(call_args)))
		fblock.append(returnValue(None)) #Return (void)

		#Create a block containg the test code
		block = Compound(fblock)

		#Create the actual test function
		decl = createFunction(name=testname,\
			args=None,\
			returnType='void')

		#Place the block inside a function definition
		func_def_ast = FuncDef(decl, None, block, None)

		#Generate the final string with the test
		gen = c_generator.CGenerator()
		str_ast = gen.visit(func_def_ast)

		return (testname, str_ast) #Return (key,value) tuple


	#Create tests for all functions
	#Returns a dictionary -> {fname : ast}
	def create_tests(self, f_decls, structs, aliases):
		return {k: v for k, v in map(lambda x :self.create_test(x, f_decls[x],\
				 structs, aliases), f_decls) if v is not None} 



	def gen(self):            

		#Initial visitor to get all relevant elements
		vis = InitialVisitor()
		vis.visit(self.ast)

		fun_decls = vis.fun_dict
		structs = vis.structs
		aliases = vis.aliases  

		#Final list of strings to be written to file
		codeList = []

		#Add Macros for size (array size and fuel)
		codeList.append(defineMacro(FUEL_MACRO, self.fuel))
		codeList.append(defineMacro(ARRAY_SIZE_MACRO, self.arraysize))
		codeList.append(defineMacro(POINTER_SIZE_MACRO, self.pointersize)+'\n')

		#Generate functions responsible for creating symbolic structs
		struct_generator = StructGen(structs, aliases)
		codeList +=  struct_generator.symbolic_structs()

		#Create actual test functions
		testsDict = self.create_tests(fun_decls, structs, aliases) 
		codeList += testsDict.values()

		#Main function to call tests
		codeList.append(mainFunction(testsDict.keys()))

		#Write to file
		file = open(self.outputfile, "w")
		file.write(f'/*File generated by {os.path.basename(__file__)}*/\n\n')
		for c in codeList:
			file.write(f'{c}\n')





def get_cmd_args():
	parser = argparse.ArgumentParser(description='Generate Symbolic Tests')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='out.c',
						help='Output name')

	parser.add_argument('--fuel', metavar='value', type=int, required=False, default=5,
						help='Define \'Fuel\' value (default:5)')

	parser.add_argument('--arraySize', metavar='value', type=int, required=False, default=10,
						help='Define array size (default:10)')

	parser.add_argument('--pointerSize', metavar='value', type=int, required=False, default=5,
						help='Define array size allocated for pointers (*) (default:5)')

	parser.add_argument('targetFile', metavar='file', type=str,
						help='The name of the target C file')

	parser.add_argument('-ast', action='store_true',
						help='Save input ast for debug')

	parser.add_argument('--fakelib', metavar='path', type=str,
						help='Path to pycparser fake libc')
 
	return parser.parse_args()



if __name__ == "__main__":

	
	#Command line arguments
	args = get_cmd_args()
	
	inputfile = args.targetFile
	outputfile = args.o
	fuel = args.fuel
	arraysize = args.arraySize
	pointersize = args.pointerSize
	fakelib = args.fakelib
	save_ast = args.ast

	

	testGenerator = testGenerator(inputfile, outputfile,
					 fuel, arraysize, pointersize,
					 fakelib=fakelib, save_ast=save_ast)

	testGenerator.gen()