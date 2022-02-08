from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from .SymbolicField import SymbolicFieldGen
import CProcessor.TestGeneration.utils as utils

#Primitive type struct field
class PrimitiveFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype, struct_name, field)


    #E.g: struct->field = new_sym_var(32)
    def gen(self):
        
        name = f'struct_{self.struct_name}_instance' 

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #struct->field
        lvalue = StructRef(name = ID(f'{name}'), type='->', field=ID(f'{self.field}'))

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
        return [decl]
