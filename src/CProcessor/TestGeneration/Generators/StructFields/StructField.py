from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from ..DefaultGen import DefaultGen


import CProcessor.TestGeneration.utils as utils

#Struct inside Struct
class StructFieldGen(DefaultGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype)

        self.struct_name = struct_name
        self.field = field


    #struct->field = create_struct(fuel)
    def gen(self):
        code = []
        name = f'struct_{self.struct_name}_instance' 

        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = StructRef(name = ID(f'{name}'), type='->', field=ID(f'{self.field}'))
    
        rvalue = self.init_struct_rvalue(self.vartype)
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
        code.append(decl)   
    
        return code
