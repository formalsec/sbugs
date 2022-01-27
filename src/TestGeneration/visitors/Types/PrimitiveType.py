from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import TestGeneration.utils as utils
from .TypeGen import SymbolicTypeGen


class PrimitiveTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):
        
        name = self.argname.name

        #Declare Variable
        lvalue = TypeDecl(name, [], IdentifierType(names=[self.vartype]))

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
        
        return [decl]