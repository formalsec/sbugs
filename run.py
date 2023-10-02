#!/usr/bin/env python3

import os
import sys
import argparse


def cmd_args():
	parser = argparse.ArgumentParser(description='Run student projects')

	parser.add_argument('--category', choices=['static', 'symbolic', 'fuzzers'], default='static',  required=True,
						help='Specify the tool category')

	parser.add_argument('--tool',  nargs='+',
		     			choices=['clang', 'cobra', 'cppcheck', 'flawfinder', 'frama-c', 'infer', 'pulse', 'uno'],
		     			default=[],
						help='Specify the tool category')

	args = parser.parse_args()
	return args


def clean(path:str):
	os.system(f'rm -rf {path}')


def check_tools(category:str):
	tool_categories = {
		'static':[
			'clang', 'cobra', 'cppcheck', 'flawfinder',
	    	'frama-c', 'infer', 'pulse', 'uno'
		]
	}

	for tool in tools:
		if not tool in tool_categories[category].keys():
			sys.exit(f'{tool} does not belong in the {category} category')




def time(category:str):
	time = f'./scripts/utils/times.py'
	outs = f'projects/outputs/{category}'

	for tool in outs:
		print(f'Timming: {tool}')
		path = f'{outs}/{tool}'
		os.system(f'{time} {path} > {path}/times.json')



#Parse all tools in a category
def parse(category:str):
	dir = f'projects/scripts/parsers/{category}'
	scripts = list(filter(lambda x: x.endswith('.py') and '.old', os.listdir(dir)))

	for script in sorted(scripts):
		print(f'Parsing: {script}')
		os.system(f'cd {dir} && ./{script}')



#Run all tools in a category
def benchmark(category:str, tools=[]):
	dir = f'projects/scripts/benchmarking/{category}'

	if not tools:
		scripts = list(filter(lambda x: x.endswith('.sh') and '.old' not in x, os.listdir(dir)))
	else:
		scripts = list(map(lambda x: x + '.sh'), tools)

	for script in sorted(scripts):
		print(f'Benchmarking: {script}')
		os.system(f'cd {dir} && ./{script}')



if __name__ == "__main__":
	args = cmd_args()
	tools = args.tool
	category = args.category

	#Check if any selected tools correspond to selected category
	check_tools(category, tools)
	
	#Clean previous results
	clean(f'projects/outputs/{category}')

	benchmark(category)
	parse(category)
	time(category)
