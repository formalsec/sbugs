#!/usr/bin/env python3

import argparse
import traceback

from CProcessor import PreProcessor


def get_cmd_args():
	parser = argparse.ArgumentParser(description='Pre-Process C file')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='out.c',
						help='Output name')
	
	parser.add_argument('targetFile', metavar='file', type=str,
						help='The name of the target C file')

	parser.add_argument('-ast', action='store_true',
						help='Save input ast for debug')

	parser.add_argument('-Global', action='store_true',
						help='Add global variables to function arguments')

	parser.add_argument('-no_scanf', action='store_false',
						help='Do not replace scanf calls')

	
	return parser.parse_args()



if __name__ == "__main__":

	#Command line arguments
	args = get_cmd_args()
	inputfile = args.targetFile
	outfile = args.o
	save_ast = args.ast
	io = args.no_scanf 
	global_vars = args.Global

	preprocessor = PreProcessor(inputfile, outfile, io, global_vars,
				 	save_ast=save_ast)
	
	preprocessor.gen()
