#!/usr/bin/env python3

import argparse
from PreProcessing.PreProcessor import PreProcessor
from TestGeneration.TestGenerator import TestGenerator


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

	parser.add_argument('-preprocess', action='store_true',
						help='Pre-process input file')
 
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
	preprocess = args.preprocess


	if preprocess:
		preprocessor = PreProcessor(inputfile, outputfile,
				 fakelib=fakelib, save_ast=save_ast)
		
		inputfile = preprocessor.gen()


	testGenerator = TestGenerator(inputfile, outputfile,
					 fuel, arraysize, pointersize,
					 fakelib=fakelib, save_ast=save_ast)

	testGenerator.gen()