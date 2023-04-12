#!/usr/bin/env python3

import argparse
import os

def cmd_args():
	parser = argparse.ArgumentParser(description='Run student projects')


	parser.add_argument('--tool', choices=['static', 'symbolic', 'fuzzers'], default='static',
						help='Specify the tool category')

	args = parser.parse_args()
	return args

def clean(path:str):
	os.system(f'rm -rf {path}')


#Run all tools of category
def benchmark(category:str):

	#Clean previous results
	clean(f'projects/outputs/{category}')

	tools = f'projects/scripts/benchmarking/{category}'
	scripts = list(filter(lambda x: x.endswith('.sh') and '.old' not in x, os.listdir(tools)))

	for script in sorted(scripts):
		print(f'Running {script}')
		os.system(f'cd {tools} && ./{script}')



if __name__ == "__main__":
	args = cmd_args()
	tool = args.tool
	benchmark(tool)
	
