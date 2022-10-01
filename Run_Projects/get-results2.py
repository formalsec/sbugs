#!/usr/bin/env python3

import argparse
import json
import os
import re


def cmd_args():
	parser = argparse.ArgumentParser(description='Run student projects')

	parser.add_argument('results', metavar='results', type=str,
						help='Results directory')
	
	parser.add_argument('projects', metavar='projects', type=str,
						help='Projects directory')

	parser.add_argument('--projs', nargs='*', default=[],
						help='Parse only specific projects')

	parser.add_argument('-lconvert',  action='store_true',
						help='Convert error lines (preprocessed to original file)')

	parser.add_argument('-lerrors',  action='store_true',
						help='Log possible error lines ')

	parser.add_argument('-o', metavar='out_dir', type=str,
						help='Specify output directory')

	args = parser.parse_args()
	return args


class LineProcessor:
	def __init__(self, project) -> None:
		self.project = project
		self.preprocessed = f'{self.project}/preprocessed'

		self.valid = {}

	def diff(self, l1, l2):
		return abs(l2-l1)

	
	def get_line(self, lineno, file) -> str:
		#print(lineno, file)
		f = open(file, 'r')
		lines = f.readlines()
		f.close()
		return lines[lineno - 1]

	
	def get_macros(self, file):
		macros = {}
		f = open(file, 'r')
		for line in f:
			line = line.strip()

			#Get simple variable macros
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
		line = re.sub(r'else', '', line)  
		line = re.sub(r'(\/\*.*?\*+\/|\/\/.*)', '', line) #Remove comments
		return line


	def find_line(self, line:str, file:str, macros:dict):
		matches = []
		trimmed = []
		f = open(file, 'r')
		i = 1
		line = self.trim(line)
		
		for l in f:	
			l = self.trim(l, macros)
			trimmed.append(l)

			if not l:
				i += 1
				continue
			
			if line in l:
				matches.append(i)
			i += 1

		if len(matches) == 0:
			i = 0
			for l in trimmed:
				if not l:
					i += 1
					continue

			if l in line and i-1 not in matches:
				matches.append(i)
			i += 1		

		return matches

	
	def get_valid_line(self, line, file, match, macros=None, backwards=False, target=True):
		
		l = self.get_line(line, file)
		l = self.trim(l, macros)
		
		if target:
			used = self.valid[match][0]
		else:
			used = self.valid[match][1]

		while l == '' or line in used:
			if backwards:
				line -= 1
			else:
				line += 1
			
			l = self.get_line(line, file)
			l = self.trim(l)


		if target:
			self.valid[match][0].append(line)
		else:
			self.valid[match][1].append(line)

		return l


	def validate_line(self, file:str, original:str, target:int, line:int, surround:int, macros:dict) -> bool:
		
		l1 = self.get_valid_line(target - surround, file, match=line, backwards=True)
		l2 = self.get_valid_line(target + surround, file, match=line)

		original_l1 = self.get_valid_line(line - surround, original, match=line, macros=macros, backwards=True, target=False)
		original_l2 = self.get_valid_line(line + surround, original, match=line, macros=macros, target=False)


		if ((l1 in original_l1) or (original_l1 in l1)) and ((l2 in original_l2) or (original_l2 in l2)):
			return True
		else:
			return False


	def remove_ambigous(self, file:str, original:str, target:int, matches:list, macros:dict) -> int:
		for m in matches:
			self.valid[m] = [[],[]]
		i = 1
		lines = matches.copy()
		while len(lines) > 1:
			lines_aux = lines.copy()
			for l in lines:
				if not self.validate_line(file, original, target, l, i, macros):
					lines_aux.remove(l)
			lines = lines_aux
			i += 1

		if len(lines) == 1:
			return lines[0]
		else:
			return -1



	def convert(self, lineno:int, file:str):
		validated, _ = self.verify_reported(lineno, file)
		if not validated:
			return -1
		
		original = f'{self.project}/{file}'
		pre = f'{self.preprocessed}/{file}'

		macros = self.get_macros(original)
		line = self.get_line(lineno, pre)


		#Help Debug
		#print(lineno, line)

		matches = self.find_line(line, original, macros)
		match = self.remove_ambigous(pre, original, lineno, matches, macros)

		
		if len(matches) > 1:
			print(f'Line {lineno} Matches: {matches}')
			print('Final Match', match)

		return match



	def verify_reported(self, lineno, file):
		pre = f'{self.preprocessed}/{file}'
		line = self.get_line(lineno, pre)
		sline = line.strip()
		validated = True

		if not sline:
			validated = False
		elif len(sline) < 10 and ';' not in sline:
			validated = False

		return validated, line






class Error():
	def __init__(self, file, line, desc) -> None:
		self.file = file
		self.line = line
		self.desc = desc

	def __repr__(self) -> str:
		return f'{self.file} : {self.line} : {self.desc}'

	def json(self):
		error_obj = {
			'file':self.file,
			'line':self.line,
			'error':self.desc
		}
		return error_obj		

	def to_list(self):
		return [self.file, self.line, self.desc]





class KleeParseLog:
	def __init__(self, logpath) -> None:
		self.logpath = logpath

		self.Error = 'Error:'
		self.File = 'File:'
		self.Line = 'Line:'
		self.Stack = 'Stack:'
	
		self.ignore_errors = ['external call with symbolic argument: printf']


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


	def filter_errors(self, error:Error):
		_, _, error_desc = error.to_list()
		for ignore in self.ignore_errors:
			if ignore in error_desc or ignore == error_desc:
				return False
		return True	


	def parse_log(self, log) -> Error:
		f1 = open(log, 'r')
		f2 = open(log, 'r')
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

		return Error(file, line, error)


	def parse(self):
		errors = []
		logs = os.listdir(self.logpath)
		for log in logs:
			if log.endswith('.err'):
				log_path = f'{self.logpath}/{log}'
				error = self.parse_log(log_path)
				errors.append(error)

		errors = list(filter(self.filter_errors, errors))
		return errors



class ParseResults:
	def __init__(self, results, projects, out,
				lconvert = True, specific = [], lerrors=False) -> None:	
		
		self.results_path = results
		self.projects_path = projects
		self.out = out
		self.lconvert = lconvert
		self.lerrors = lerrors
		
		if self.lerrors:
			self.lwrong = open('wrong_lines.txt','w+')
			self.lwrong.write('(Possibly) Incorrect lines reported\n')

		if len(specific) == 0:
			self.results = os.listdir(self.results_path)
		else:
			self.results = specific
		self.results.sort(key=lambda p : int(p.split('_')[-1]))

		self.total_errors = 0
		self.error_types = {}
		self.no_errors = []
		self.convert_err = 0


	def update_global(self, error:Error):
		_, _, error_desc = error.to_list()
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

	def create_global_obj(self):
		global_obj = {
			'Total errors': self.total_errors,
			'Not Converted': self.convert_err,
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

	def convert_line(self, error:Error, proj:str):
		file, line, error_desc = error.to_list()
		
		if 'Project_' in proj:
			proj = proj.split('_')[1]
		
		proj_path = f'{self.projects_path}/{proj}'		
		lp = LineProcessor(proj_path)
		lineno = lp.convert(int(line), file)

		if lineno < 0:
			self.convert_err += 1

		return Error(file, lineno, error_desc)


	def verify_line(self, error:Error, proj:str):
		file, lineno, _ = error.to_list()
		
		if 'Project_' in proj:
			proj = proj.split('_')[1]
		proj_path = f'{self.projects_path}/{proj}'	

		lp = LineProcessor(proj_path)
		validated, line = lp.verify_reported(int(lineno), file)
			
		if not validated:
			self.lwrong.write(f'{proj} {file}:{lineno} {line}')



	def parse_proj(self, proj:str):		
		proj_json_obj = self.create_proj_obj(proj)	
		proj_path = f'{self.results_path}/{proj}'
		
		parser = KleeParseLog(proj_path)
		errors = parser.parse()
				
		if not errors:
			self.no_errors.append(proj)

		for err in errors:
			
			if self.lerrors:
				self.verify_line(err, proj)

			if self.lconvert:
				err = self.convert_line(err, proj)
			
			self.update_global(err)
			proj_json_obj['errors'].append(err.json())
	
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

		if self.lerrors:
			self.lwrong.close()
		

def addPrefix(prefix:str, name:str):
	return prefix + name
		
if __name__ == "__main__":
	
	ARGS = cmd_args()
	results  = ARGS.results
	projects = ARGS.projects
	lconvert = ARGS.lconvert
	lerrors	 = ARGS.lerrors
	
	specific = ARGS.projs
	specific = [addPrefix('Project_',p) if p.isnumeric() else p for p in specific]


	out = ARGS.o

	if results[-1] == '/':
		results = results[:-1]

	if projects[-1] == '/':
		projects = projects[:-1]

	if not out:
		out = results.split('/')[-1]
		out = f'Parsed_{out}'
	
	parser = ParseResults(results, projects, out,
						lconvert=lconvert, specific=specific, lerrors=lerrors)
	parser.save_results()