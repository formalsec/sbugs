import subprocess as sp
from sys import stderr

class CCompiler():
    def __init__(self, inputfile, outputfile, libs):
        self.inputfile = inputfile
        self.outputfile = self.binary_name(outputfile)

        self.gcc_args = ['-Wno-int-conversion']

        if not libs:
            libs = []
        self.libs = libs 

    def binary_name(self, file):
        if file[-2:] == '.c':
            return file[:-2]
        return file

    
    def compile(self):
        gcc_cmd = [
            'gcc',
            *self.gcc_args,
            self.inputfile,
            '-o', self.outputfile,
            *self.libs
        ]

        print(' '.join(gcc_cmd))  

        t = sp.Popen(gcc_cmd, stdout=sp.PIPE, stderr=sp.PIPE)
        stdout, stderr = t.communicate()
        out = stdout.decode()
        err = stderr.decode()

        print(out,end='')
        print(err,end='')
