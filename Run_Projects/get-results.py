#!/usr/bin/env python3

import argparse
import json
import sys
import os
import re


def cmd_args():
	parser = argparse.ArgumentParser(description='Run student projects')

	parser.add_argument('results', metavar='results', type=str,
						help='Results directory')
	
	parser.add_argument('projects', metavar='projects', type=str,
						help='Projects directory')

	parser.add_argument('-lconvert',  action='store_true',
						help='Convert error lines (preprocessed to original file)')

	parser.add_argument('-o', metavar='out_dir', type=str,
						help='Specify output directory')

	args = parser.parse_args()
	return args


class LineCoverter:
	def __init__(self, project) -> None:
		self.project = project
		self.preprocessed = f'{self.project}/preprocessed'

	def diff(self, l1, l2):
		return abs(l2-l1)

	def get_macros(self, file):
		macros = {}
		f = open(file, 'r')
		for line in f:
			line = line.strip()
			if re.match(r'^\# *define', line) and '(' not in line:
				split = line.split()
				macros[split[-2]] = split[-1]
		f.close()
		return macros


	def trim(self, line:str, macros:dict = None):
		if macros:
			for key in macros.keys():
				if key in line:
					line = line.replace(key, macros[key])

		line = line.strip()
		line = re.sub(r'[(){}; ]', '', line)
		line = re.sub(r'(\/\*.*?\*+\/|\/\/.*)', '', line)
		return line

	def get_line(self, lineno, file):
		f = open(file, 'r')
		lines = f.readlines()
		f.close()
		return lines[lineno - 1]

	def find_line(self, line, file, macros):
		matches = []
		f = open(file, 'r')
		i = 1
		for l in f:
			
			line = self.trim(line)
			l = self.trim(l, macros)

			if not l:
				i += 1
				continue
			
			if line in l:
				matches.append(i)
			i += 1
		return matches

	def convert(self, lineno, file):
		original = f'{self.project}/{file}'
		pre = f'{self.preprocessed}/{file}'

		macros = self.get_macros(original)
		

		line = self.get_line(lineno, pre)
		matches = self.find_line(line, original, macros)

		assert len(matches) > 0, f'Unable to match line {lineno} in {self.project} {file}'

		if len(matches) > 1:
			print(f'> Multiple line candidates in {original}' )
			print(f'> Possible Lines: {matches}')
			print(f'> Choosing the closest to {lineno}: ', end='')

		best_match = matches[0]
		for match in matches[1:]:
			if self.diff(lineno, match) < self.diff(lineno, best_match):
				best_match = match

			elif self.diff(lineno, match) == self.diff(lineno, best_match):		
				sys.exit(f'Equidistant line candidates, line:{match} and line:{best_match}')
		
		if len(matches) > 1:
			print(f'{best_match}\n')
		
		return best_match


class ParseLog:
	def __init__(self, log) -> None:
		self.log = log

		self.Error = 'Error:'
		self.File = 'File:'
		self.Line = 'Line:'
		self.Stack = 'Stack:'
	

	def split_line(self, line, delim, index=1):
		split = line.split(delim, index)
		return split[index]

	def get_main_values(self, f):	
		for line in f:
			if self.Error in line:
				error_type = self.split_line(line, ':')
				error_type = error_type.strip()
			elif self.File in line:
				file_name = self.split_line(line, ':')
				file_name = file_name.strip()
			elif self.Line in line:
				code_line = self.split_line(line, ':')
				code_line = code_line.strip()
			else:
				continue	
		return error_type, file_name, code_line

	
	
	def get_stack(self, f):
		stack = False
		for line in f:
			if self.Stack in line:
				stack = True
				continue
			if stack:
				trimmed = line.strip()
				if trimmed.startswith('#') and 'in' in line:
					call = self.split_line(line, ' at ')
					if '/' not in call:
						file = call.split(':')[0]
						code_line = call.split(':')[1]
						return file.strip(), code_line.strip()
				else:
					continue
			else:
				continue
		return None



	def parse(self):
		f1 = open(self.log, 'r')
		f2 = open(self.log, 'r')
		error, file, line = self.get_main_values(f1)
		stack_file, stack_line = self.get_stack(f2)
		f1.close()
		f2.close()

		if '/' not in file:
			assert(file == stack_file)
			assert(line == stack_line)
		else:
			file = stack_file
			line = stack_line
			assert('/' not in file)

		return [file, line, error]



class ParseResults:
	def __init__(self, results, projects, out, lconvert = True) -> None:
		
		self.results_path = results
		self.projects_path = projects
		self.out = out
		self.lconvert = lconvert

		self.results = os.listdir(self.results_path)
		self.results.sort(key=lambda p : int(p.split('_')[-1]))

		self.ignore_errors = ['external call with symbolic argument: printf']

		self.total_errors = 0
		self.error_types = {}
		self.no_errors = []


	def update_global(self, error):
		_, _, error_desc = error
		self.total_errors += 1
		
		if error_desc in self.error_types.keys():
			self.error_types[error_desc] += 1
		else:
			self.error_types[error_desc] = 1
			

	def log_json(self, path, results):
		file = open(path, 'w+')
		json_object = json.dumps(results, indent = 2)  
		file.write(json_object)
		return
	
	def create_error_obj(self, error):
		file, line, error_desc = error
		error_obj = {
			'file':file,
			'line':line,
			'error':error_desc,
		}
		return error_obj

	def create_global_obj(self):
		global_obj = {
			'Total errors': self.total_errors,
			'Error Types': self.error_types,
			'No errors found': self.no_errors
		}
		return global_obj

	def create_proj_obj(self, name):
		proj_obj = {
			'name': name,
			'errors': []
		}
		return proj_obj

	def convert_lines(self, error, proj):
		file, line, error_desc = error
		
		if 'Project_' in proj:
			proj = proj.split('_')[1]
		
		proj_path = f'{self.projects_path}/{proj}'
		
		lc = LineCoverter(proj_path)
		lineno = lc.convert(int(line), file)

		return [file, lineno, error_desc]

	def filter_errors(self, error):
		_, _, error_desc = error
		for ignore in self.ignore_errors:
			if ignore in error_desc or ignore == error_desc:
				return False
		return True


	def parse_proj(self, proj):
		
		proj_json_obj = self.create_proj_obj(proj)
		errors = []
		
		proj_path = f'{self.results_path}/{proj}'
		logs = os.listdir(proj_path)
		
		for log in logs:
		
			if log.endswith('.err'):
				log_path = f'{self.results_path}/{proj}/{log}'
				parser = ParseLog(log_path)
				error = parser.parse()
				errors.append(error)
		
		filtered_errors = list(filter(self.filter_errors, errors))
		
		if not filtered_errors:
			self.no_errors.append(proj)

		for err in filtered_errors:

			if self.lconvert:
				err = self.convert_lines(err, proj)	
			
			self.update_global(err)
			err_obj = self.create_error_obj(err)
			proj_json_obj['errors'].append(err_obj)
	
		return proj_json_obj


	def save_results(self):
		os.makedirs(self.out, exist_ok=True)

		for proj in self.results:
			print(f'==> Parsing {proj}')
			
			proj_json_obj = self.parse_proj(proj)
			
			log = f'{self.out}/{proj}.json'
			self.log_json(log, proj_json_obj)

		global_obj = self.create_global_obj()
		global_log = f'{self.out}/Global_stats.json'
		
		self.log_json(global_log, global_obj)
		


		
if __name__ == "__main__":
	
	ARGS = cmd_args()
	results = ARGS.results
	projects = ARGS.projects
	lconvert = ARGS.lconvert
	out = ARGS.o

	if results[-1] == '/':
		results = results[:-1]

	if projects[-1] == '/':
		projects = projects[:-1]

	if not out:
		out = results.split('/')[-1]
		out = f'Parsed_{out}'
	
	parser = ParseResults(results, projects, out, lconvert=lconvert)
	parser.save_results()