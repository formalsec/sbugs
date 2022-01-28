#!/usr/bin/env python3

import argparse
import traceback

from CProcessor import PreProcessor


def get_cmd_args():
	parser = argparse.ArgumentParser(description='Generate Symbolic Tests')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='out.c',
						help='Output name')
	
	parser.add_argument('targetFile', metavar='file', type=str,
						help='The name of the target C file')
	
	parser.add_argument('--fakelib', metavar='path', type=str,
						help='Path to pycparser fake libc')

	parser.add_argument('-ast', action='store_true',
						help='Save input ast for debug')

	
	return parser.parse_args()



if __name__ == "__main__":

	#Command line arguments
	args = get_cmd_args()
	inputfile = args.targetFile
	outfile = args.o
	fakelib = args.fakelib
	save_ast = args.ast

	preprocessor = PreProcessor(inputfile, outfile,
				 fakelib=fakelib, save_ast=save_ast)
	
	preprocessor.gen()
