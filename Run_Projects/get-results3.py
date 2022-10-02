#!/usr/bin/env python3

import argparse
import json
import os
import re
import sys


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

	
	def trim(self, line:str, macros:dict = None):
		if macros:
			for key in macros.keys():
				if key in line:

					m = macros[key]
					if isinstance(m,str):
						line = line.replace(key, macros[key])
					
					else:
						value, var = m
						key_ = key[:-1]
						macros_in_lines = re.findall(fr'{key_}\(.*\)', line)
						for ml in macros_in_lines:
							
							vl = ml.split('(')[1]
							vl = vl[:-1]

							value_aux = value.replace(var, vl)
							line = line.replace(ml, value_aux)


		line = line.strip()
		line = re.sub(r'[(){}; ]', '', line)	
		line = re.sub(r'else', '', line)  
		line = re.sub(r'(\/\*.*?\*+\/|\/\/.*)', '', line) #Remove comments
		return line
	

	def get_macros(self, proj):
		macros = {}

		files = os.listdir(proj)
		filtered_files = []
		for file in files:
			if file.endswith('.c') or file.endswith('.h'):
				filtered_files.append(file)

		for file in filtered_files:

			f = open(f'{proj}/{file}', 'r')
			for line in f:
				line = line.strip()
				line = re.sub(r'(\/\*.*?\*+\/|\/\/.*)', '', line) #Remove comments

				#Get macros
				if re.match(r'^\# *define', line):
					
					split = line.split()
					if len(split) >= 3:
						
						name = split[1]
						
						value = split[2]
						value = re.sub(r'[()]', '', value)

						if '(' and ')' in name:
							name = re.sub(r'[)]', '', name)
							
							name_split = name.split('(')
							name = name_split[0] + '('
							var = name_split[1]
							value = (value, var)

						macros[name] = value
				
				macros['NULL'] = '0'

			f.close()
		return macros


	def find_line(self, line:str, file:str, macros:dict):
		matches = []
		trimmed = []
		f = open(file, 'r')
		i = 1
		orig_line = line
		line = self.trim(line)
		
		for l in f:	

			l = self.trim(l, macros=macros)
			trimmed.append(l)

			if not l:
				i += 1
				continue
			
			if line in l:
				matches.append(i)
			i += 1

		if len(matches) == 0:
			i = 1
			for l in trimmed:
				if not l:
					i += 1
					continue

				if l in line and i-1 not in matches:
					matches.append(i)
				i += 1		
		
		if len(matches) == 0:
			line = orig_line.strip()
			split = line.split()
			line = ''.join(split[1:])
			line = self.trim(line)


			i = 1
			for l in trimmed:
				if not l:
					i += 1
					continue

				if line in l or l in line:
					print(l)
					matches.append(i)
					i += 1		
		
		return matches



	def num_ifs(self, lineno:int, file:str):

		f = open(file, 'r')
		lines = f.readlines()
		f.close()

		lines = lines[:lineno]
		section = []

		#Remove comments
		for l in lines:
			new_l = re.sub(r'(\/\*.*?\*+\/|\/\/.*)', '', l)
			section.append(new_l) 
					
		section_string = ''.join(section)
		section_string = re.sub(r'(\/\*(\*(?!\/)|[^*])*\*\/)', '', section_string)
		if_matches = re.findall(r'if *\(', section_string)

		return len(if_matches)


	def remove_ambigous(self, file:str, original:str, target:int, matches:list) -> int:
		print('Target: ',target)
		print('Matches: ', matches)

		if len(matches) == 0:
			return -1

		target_ifs = self.num_ifs(target, file) 
		
		#Get 'if' count for all the matches
		matches_ifs = []
		for m in matches:
			ifs = self.num_ifs(m, original)
			matches_ifs.append( (m, ifs) )
		
		#Get the exact if count to the target line
		exact = []
		for m in matches_ifs:
			_, n_ifs = m
			
			if n_ifs == target_ifs:
				exact.append(m)

		if len(exact) == 1:
			l, _ = exact[0] 
			return l
		
		elif len(exact) == 0:
			if len(matches) == 1:
				return matches[0]
			else:
				print('Mismatch in ifs number')
				return -1

		else:
			print('Multiple exact \'if\' counts')
			best_match = exact[0]
			for m in exact[1:]:

				l, _ = m
				bl, _ = best_match

				if self.diff(target, l) < self.diff(target, bl):
					best_match = m

				elif self.diff(target, l) == self.diff(target, bl):
					best_match = min(l, bl)						
			
			return best_match[0]



	def convert(self, lineno:int, file:str):
		validated, line = self.verify_reported(lineno, file)
		if not validated:
			#print('Invalid line: ', lineno, line)
			return -1
		
		original = f'{self.project}/{file}'
		pre = f'{self.preprocessed}/{file}'

		macros = self.get_macros(self.project)

		matches = self.find_line(line, original, macros)
		match = self.remove_ambigous(pre, original, lineno, matches)
		
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
		#self.results.sort(key=lambda p : int(p.split('_')[-1]))

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