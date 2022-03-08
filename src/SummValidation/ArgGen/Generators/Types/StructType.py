from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import SummValidation.Utils.utils as utils


from ..DefaultGen import DefaultGen

#Create a symbolic struct (call respective function)
class StructTypeGen(DefaultGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):

        name = self.argname.name
        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        rvalue = FuncCall(ID(f'create_{fname}'),ExprList([self.fuel]) )

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)

        return [decl]
