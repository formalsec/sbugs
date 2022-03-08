from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import SummValidation.Utils.utils as utils

from ..DefaultGen import DefaultGen


# Create a primitive symbolic var

class PrimitiveTypeGen(DefaultGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    # e.g, int a = summ_new_sym_var(sizeof(int))
    
    def gen(self):

        name = self.argname.name

        #Declare Variable
        lvalue = TypeDecl(name, [], IdentifierType(names=[self.vartype]))

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
        
        return [decl]