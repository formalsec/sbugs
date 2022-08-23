#!/usr/bin/env python3

from threading import Thread
import subprocess as sp
from time import ctime, time
import argparse
import signal
import sys
import os


from CProcessor import PreProcessor

GB_4 = 4194304
MIN_15 = 60*15

def cmd_args():
	parser = argparse.ArgumentParser(description='Run student projects')

	parser.add_argument('project', type=str,
						choices=['iaed_p1','iaed_p2',
						'asa_1819_p1', 'asa_1819_p2',
						'asa_1920_p1', 'asa_1920_p2'],
						help='Specify the IAED project')

	parser.add_argument('--tool', choices=['klee'],
						help='Specify the symbolic the execution tool')

	parser.add_argument('-original', action='store_true',
						help='Run the original projects')

	parser.add_argument('-preprocess_only', action='store_true',
						help='Only preprocess projects')
	
	parser.add_argument('--projs', nargs='*', default=[],
						help='Run/Preprocess only specific projects')

	parser.add_argument('--timeout', metavar='sec', type=int,
						help='Timeout in seconds (default: 900s, 15min)', default=900)
	
	parser.add_argument('--threads', metavar='num', type=int,
						help='Number of threads to use (default: 1)', default=1)
   
	args = parser.parse_args()
	return args




class RunCommands():
	def __init__(self, nthreads):
		self.nthreads = nthreads

	def divide_commands(self, commands, n_threads):
		division = []
		for _ in range(n_threads):
			division.append([])

		for i in range(len(commands)):
			division[i % len(division)].append(commands[i])		
		
		return division


	def run_popen(self, commands):
		for c in commands:
			try:
				c_string = ' '.join(c)
				print(c_string, flush=True)
				
				p = sp.Popen(f'ulimit -s unlimited; ulimit -Sv {GB_4} && {c_string}',
							 stdout=sp.DEVNULL, stderr=sp.DEVNULL,
							 shell=True)
				try:
					p.wait(timeout=MIN_15 + 10) #15min +10sec

				#Catch timeout exception and kill child process
				except sp.TimeoutExpired:
					print(f'\n[!] 15min Timeout Detected: {c}')
					p.send_signal(signal.SIGKILL)
					p.wait()
			
			except Exception as e:
				print(f'There was an exception:{e}')
		return


	def run_os_system(self, commands):
		for c in commands:
			try:
				c_string = ' '.join(c)

				print(f'Running {c_string}')
				os.system(f'ulimit -s unlimited -Sv {GB_4} && {c_string} > /dev/null 2>&1')
				print(f'Done {c_string}')
			
			except Exception as e:
				print(f'Exception in {c_string}:{e}')
		return


	def run(self, commands):
		
		start = time()
		activeThreads = []
		commands_division = self.divide_commands(commands, self.nthreads)

		for i in range(1, len(commands_division)):
			
			args = [commands_division[i]]

			t = Thread(target=self.run_popen, args=args)
			t.start()
			activeThreads.append(t)

		self.run_popen(commands_division[0])

		#Wait for threads
		for t in activeThreads:
			t.join()
		
		end = time()
		elapsed = round(end-start, 3)
		 
		print(f'Elapsed: {elapsed} seconds ({round(elapsed/3600,2)} hours)')
		return


class Klee():
	def __init__(self, path, projects, original, timeout, threads):
		
		self.path = path
		self.projects = projects
		self.original = original
		self.timeout = timeout
		self.threads = threads
		self.results_dir = f'Results/Klee/{self.path}'
		
		self.flags = ['--posix-runtime',
					 '--libc=uclibc',
					 '--only-output-states-covering-new',
					 '-max-time=900','--watchdog']

	
	def compile(self, path, proj, orginal):
		if orginal:
			print(f'Compiling Llvm bytecode for Project {proj}')
			os.system(f'make -C {path}/{proj} bc -s')
		else:
			print(f'Compiling Llvm bytecode for preprocessed Project {proj}')
			os.system(f'make -C {path}/{proj} pre_bc -s')    
		return


	def mkdir(self, path):
		os.makedirs(path, exist_ok=True)
		return


	def build_command(self, proj_name, proj_path, out, flags):
		if self.original:
			bytecode = f'{proj_path}/{proj_name}.bc'
		else:
			bytecode = f'{proj_path}/preprocessed/{proj_name}.bc'
		command = ['klee', f'-output-dir={out}'] + flags + [f'{bytecode}', '-sym-stdin 10']
		return command



	def run(self):

		os.system(f'make -C {self.path} clean -s')
		for proj in self.projects:
			self.compile(self.path, proj, self.original)

		time_string = ctime()
		time_string = time_string.replace(' ', '_')
		self.mkdir(self.results_dir)
		self.mkdir(f'{self.results_dir}/{time_string}')

		commands = []
		for proj in self.projects:
			
			proj_path = f'{self.path}/{proj}'
			out = f'{self.results_dir}/{time_string}/Project_{proj}'
			
			command = self.build_command(proj, proj_path, out, self.flags)
			commands.append(command)
		
		run_commands = RunCommands(self.threads)
		run_commands.run(commands)	
		return
		



class GetProjects():
	def __init__(self, path):
		self.path = path
		self.ignore = ['Makefile', 'symbolic']


	def proj_filter(self, entry):
		if not os.path.isdir(f'{self.path}/{entry}'):
			return False	
		
		for ignore in self.ignore:
			if ignore in entry:
				return False

		return True

	def get_all(self):
		projects = os.listdir(self.path)
		projects =  list(filter(self.proj_filter, projects))
		projects.sort(key=lambda dir : int(dir) if dir.isnumeric() else dir)
		return projects



class Preprocess():
	def __init__(self, path, projects):
		
		self.path = path
		self.projects = projects
		self.scanf = 'scanf'


	def contains_scanf(self, file):
		with open(file, 'r') as f:
			data = f.read()
			if self.scanf in data:
				return True
			else:
				return False


	def Cfilter(self, file):
		if file.endswith('.c'):
			return True
		elif file.endswith('.h') and self.contains_scanf(file):
			return True
		else:
			return False
  
	def get_files(self, project):
		files = list(os.listdir(project))
		files = [f'{project}/{f}' for f in files]
		files = filter(self.Cfilter, files)
		return files


	def run(self):
		for p in self.projects:

			print(f'Preprocessing Project {p}')
			
			project = f'{self.path}/{p}'
			preprocessed_dir = f'{project}/preprocessed'

			files = self.get_files(project)
			
			if not os.path.isdir(preprocessed_dir):
				os.mkdir(preprocessed_dir)

			for file in files:            
				filename = file.split('/')[-1]
				preprocessor = PreProcessor(file, f'{preprocessed_dir}/{filename}',
				 							io = True, include = project, arraylimit = 10)
				out = preprocessor.gen()

				if not out:
					sys.exit(f'Error in Project {p}')



if __name__ == "__main__":

	args = cmd_args()
	project = f'Projects/{args.project}'
	projs = args.projs
	preprocess_only = args.preprocess_only
	tool_name = args.tool
	orginal = args.original
	timeout = args.timeout
	threads = args.threads

	if tool_name is None and not preprocess_only:
		sys.exit('Tool not specified')

	if not projs:
		finder = GetProjects(project) 
		projs = finder.get_all()

	if not orginal:
		preprocessor = Preprocess(project, projs)
		preprocessor.run()

	if preprocess_only:
		sys.exit()    

	if tool_name == 'klee':
		tool = Klee(project, projs, orginal, timeout, threads)

	tool.run()

	
