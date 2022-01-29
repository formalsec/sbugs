import sys, os, traceback

from pycparser import parse_file, c_generator

from .visitors.PreProcessVisitor import PreProcessVisitor
from CProcessor.C_Generator import C_FileGenerator

class PreProcessor(C_FileGenerator):

	def __init__(self, inputfile, outputfile, fakelib=None, save_ast=False):
		super().__init__(inputfile, outputfile, fakelib ,save_ast)
	


	def gen(self):
		
		try:
			#PreProcess inputfile
			includes = self._preprocess_file(self.inputfile, self.tmpfile)

			#Parse new file
			ast = parse_file(self.tmpfile, use_cpp=True,
				cpp_path='gcc',
				cpp_args=['-E', f'-I{self.fakelib}/fake_libc_include'])

			#Visit the ast
			visitor = PreProcessVisitor()
			generated_ast = visitor.visit(ast) 

			generator = c_generator.CGenerator()
			generated_string = generator.visit(generated_ast)

			#Write ast to temporary file
			tmpfile = open(self.tmpfile, "w")
			tmpfile.write(generated_string)
			tmpfile.flush()

			#PostPreProcess temporary file
			final_code = self._postprocess_file(self.tmpfile, includes, generator=os.path.basename(__file__))

			self._remove_files(self.tmpfile)

			#Write final output file
			outfile = open(self.outputfile, "w")
			outfile.writelines(final_code)

			return self.outputfile
			

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())
