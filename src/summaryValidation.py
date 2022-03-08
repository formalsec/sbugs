#!/usr/bin/env python3

import argparse
from SummValidation import ValidationGenerator, CCompiler


def get_cmd_args():
	parser = argparse.ArgumentParser(description='Generate Summary Validation Tests')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='test.c',
						help='Output name')

	parser.add_argument('concreteFunction', metavar='concrete_function', type=str,
						help='Path to file containing concrete function')

	parser.add_argument('summary', metavar='summary_file', type=str,
						help='Path to file containing the summary being evaluated')

	parser.add_argument('--summ_name', metavar='name', type=str,
						help='Name of the summary in the given path')
	
	parser.add_argument('--func_name', metavar='name', type=str,
						help='Name of the concrete function in the given path')

	parser.add_argument('--arraysize', metavar='value', nargs='+', type=int, required=False, default=[5],
						help='Define array sizes to use for tests (default:5)')

	parser.add_argument('--lib', metavar='path', nargs='+', type=str, required=False,
						help='Path to external files needed to compile the test binary')

	parser.add_argument('-compile', action='store_true',
						help='Compile the generated test')
	
	parser.add_argument('-memory', action='store_true',
						help='Evaluate a summary with memory manipulation side-effects')

	return parser.parse_args()



if __name__ == "__main__":

	
	#Command line arguments
	args = get_cmd_args()
	
	concrete_function = args.concreteFunction
	target_summary = args.summary
	outputfile = args.o
	arraysize = args.arraysize
	summ_name = args.summ_name
	cncr_name = args.func_name
	ccompile = args.compile
	lib_paths = args.lib
	memory = args.memory

	valgenerator = ValidationGenerator(concrete_function, target_summary,
					 			 		outputfile,
										arraysize, memory,
										cncr_name, summ_name)
	valgenerator.gen()

	if ccompile:
		bin_name = outputfile[:-2] #Remove '.c'
		comp = CCompiler(outputfile, bin_name, lib_paths)
		comp.compile()
