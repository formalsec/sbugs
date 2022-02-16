import subprocess as sp

class CCompiler():
    def __init__(self, inputfile, outputfile):
        self.inputfile = inputfile
        self.outputfile = self.binary_name(outputfile)

        self.gcc_args = ['-Wno-int-conversion']


    def binary_name(self, file):
        if file[-2:] == '.c':
            return file[:-2]
        return file

    
    def compile(self):

        gcc_cmd =  ['gcc'] + self.gcc_args
        gcc_cmd += [self.inputfile]
        gcc_cmd += ['-o', self.outputfile]

        print(' '.join(gcc_cmd))  

        t = sp.Popen(gcc_cmd, stdout=sp.PIPE, stderr=sp.PIPE)
        t.communicate() 
