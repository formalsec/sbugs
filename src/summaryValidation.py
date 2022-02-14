#!/usr/bin/env python3

import argparse
from SummValidation import ValidationGenerator


def get_cmd_args():
	parser = argparse.ArgumentParser(description='Generate Summary Validation Tests')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='test.c',
						help='Output name')

	parser.add_argument('concreteFunction', metavar='concrete_function', type=str,
						help='Path to the concrete function')

	parser.add_argument('summary', metavar='summary_file', type=str,
						help='Path to the summary being evaluated')

	parser.add_argument('-summ_lib', action='store_true',
						help='Whether target summary is contained in a library')

	parser.add_argument('--fakelib', metavar='path', type=str,
					help='Path to pycparser fake libc')
	
	parser.add_argument('--arraySize', metavar='value', type=int, required=False, default=10,
						help='Define array size (default:10)')

	return parser.parse_args()



if __name__ == "__main__":

	
	#Command line arguments
	args = get_cmd_args()
	
	concrete_function = args.concreteFunction
	target_summary = args.summary
	outputfile = args.o
	arraysize = args.arraySize
	fakelib = args.fakelib
	summ_lib = args.summ_lib


	valgenerator = ValidationGenerator(target_summary, concrete_function,
					 			 	   outputfile, arraysize,
					 			 	   summ_lib, fakelib=fakelib)
	valgenerator.gen()