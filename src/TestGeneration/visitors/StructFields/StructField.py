from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from TestGeneration.visitors.InputGen import InputGenVisitor
from .SymbolicField import SymbolicFieldGen
import TestGeneration.utils as utils

#Struct inside Struct
class StructFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype, struct_name, field)


    #struct->field = create_struct(fuel)
    def gen(self):
        code = []
        name = f'struct_{self.struct_name}_instance' 

        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = StructRef(name = ID(f'{name}'), type='->', field=ID(f'{self.field}'))

        #Recursive struct
        if f'struct_{self.struct_name}' == fname:
            code.append(self.recursiveStruct(name, lvalue, fname))
        
        #Other struct
        else:
            rvalue = self.init_struct_rvalue(self.vartype)
            decl = Decl(name, [], [], [], lvalue, rvalue, None)
            code.append(decl)   
        
        return code
