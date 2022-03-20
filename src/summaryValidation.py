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
						help='Define array sizes for each tests (default:5)')

	parser.add_argument('--maxvalue', metavar='value', nargs='+', type=int, required=False, default=[],
						help='Define values to constrain numeric values')

	parser.add_argument('--lib', metavar='path', nargs='+', type=str, required=False,
						help='Path to external files needed to compile the test binary')

	parser.add_argument('-compile', action='store_true',
						help='Compile the generated test')
	
	parser.add_argument('-memory', action='store_true',
						help='Evaluate a summary with memory manipulation side-effects')

	parser.add_argument('-config', metavar='path', type=str, required=False,
						help='Config file')


	return parser.parse_args()


def parse_config(conf):
	f = open(conf, "r")
	lines = f.readlines()
	f.close()

	array_size = []
	max_num = []

	for l in lines:
		l = l.strip()
		split = l.split(' ')
		if 'array_size' in split[0]:
			array_size = [size for size in map(lambda x: int(x), split[1:])]

		if 'max_num' in split[0]:
			max_num = [size for size in map(lambda x: int(x), split[1:])]

	return array_size, max_num

if __name__ == "__main__":

	
	#Command line arguments
	args = get_cmd_args()
	
	concrete_function = args.concreteFunction
	target_summary = args.summary
	outputfile = args.o
	arraysize = args.arraysize
	maxvalue = args.maxvalue
	summ_name = args.summ_name
	cncr_name = args.func_name
	ccompile = args.compile
	lib_paths = args.lib
	memory = args.memory
	config_file = args.config

	if config_file:
		arraysize, maxvalue = parse_config(config_file)
		if arraysize == []:
			arraysize = [5]

	valgenerator = ValidationGenerator(concrete_function, target_summary,
					 			 		outputfile,
										arraysize, maxvalue, memory,
										cncr_name, summ_name)
	valgenerator.gen()

	if ccompile:
		bin_name = outputfile[:-2] #Remove '.c'
		comp = CCompiler(outputfile, bin_name, lib_paths)
		comp.compile()
