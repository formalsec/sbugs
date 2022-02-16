import sys, os

from pycparser import c_parser, parse_file, c_generator
from pycparser.c_ast import *

class C_FileGenerator:
	def __init__(self, outputfile, fakelib=None):

		self.outputfile = outputfile

		tmpname = self.outputfile.split('/')[-1]
		self.tmpfile = f'tmp_{tmpname}'
		
		self.fakelib = 'Fake_libc'
		if fakelib is not None:
			self.fakelib = fakelib



	
	def _remove_files(self, *files):
		for f in files:
			if os.path.exists(f):
	  			os.remove(f)


	#Store 'includes' of inputfile
	def _get_includes(self, inputfile):
		includes = []
		with open(inputfile, 'r') as inp:
			for line in inp:
				if line.startswith('#include'):
					includes.append(line)

		return includes


	#Removes typedefs from fake_libc
	#Prepends the correct includes
	#Add our macros for symbolic tests
	def	_postprocess_file(self, inputfile, includes, generator=None, stubs=[]):
		if generator is None:
			generator= os.path.basename(__file__)

		start = False
		file = []
		with open(inputfile, 'r') as inp:
			for line in inp:
				if start:
						file.append(line)

				if line.startswith('void __start();'):
					start = True
					file.append(f'/*File generated by {generator}*/\n\n')
					file += includes
					file.append('\n')
					file += stubs
					file.append('\n')


		return file


	def _write_to_file(self, code, includes, generator=None, stubs=[]):

		headers = [f'/*File generated by {generator}*/\n\n']
		headers += includes
		headers.append('\n')
		headers += stubs
		headers.append('\n')

		outfile = open(self.outputfile, "w")
		outfile.writelines(headers)
		outfile.write(code)
		outfile.flush()

	def gen(self):
		pass