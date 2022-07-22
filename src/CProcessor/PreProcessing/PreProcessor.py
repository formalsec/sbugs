import sys, os, traceback

from pycparser import parse_file, c_generator

from .Global.GlobalVisitor import Global_Visitor
from .IO.visitors.IOVisitor import IO_Visitor
from CProcessor.C_Generator import C_FileGenerator

class PreProcessor(C_FileGenerator):

	def __init__(self, inputfile, outputfile, io, global_vars=None, include=None, save_ast=False):
		super().__init__(inputfile, outputfile, include ,save_ast)
		
		self.io = io 
		self.global_vars = global_vars


	def gen(self):
		
		try:
			#PreProcess inputfile
			includes = self._preprocess_file(self.inputfile, self.tmpfile)

			cpp_args=['-E', f'-I{self.fakelib}']
			if self.include:
				cpp_args.append(f'-I{self.include}')

			#Parse new file
			ast = parse_file(self.tmpfile, use_cpp=True, cpp_path='gcc', cpp_args=cpp_args)


			if self.io:
				io_visitor = IO_Visitor()
				ast = io_visitor.visit(ast)

			if self.global_vars:
				global_visitor = Global_Visitor()
				ast = global_visitor.visit(ast)

			generator = c_generator.CGenerator()
			generated_string = generator.visit(ast)

			#Write ast to temporary file
			tmpfile = open(self.tmpfile, "w")
			tmpfile.write(generated_string)
			tmpfile.flush()

			#PostProcess temporary file
			final_code = self._postprocess_file(self.tmpfile, includes,
						 generator=os.path.basename(__file__))

			self._remove_files(self.tmpfile)

			#Write final output file
			outfile = open(self.outputfile, "w")
			outfile.writelines(final_code)

			return self.outputfile
			

		except Exception as e:
			self._remove_files(self.tmpfile)
			print(traceback.format_exc())
