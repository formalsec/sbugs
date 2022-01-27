from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import TestGeneration.utils as utils

# Create a primitive symbolic var
# e.g, int a = summ_new_sym_var(sizeof(int))
class SymbolicTypeGen(NodeVisitor):
    def __init__ (self, name, vartype):

        self.fuel = ID(utils.FUEL_MACRO)

        if isinstance(name, str):
            name = ID(name=name)

        self.argname = name 
        self.vartype = vartype

    
    def init_struct_rvalue(self, vartype):

        vartype = self.vartype.replace(' ', '_')
        rvalue = FuncCall(ID(f'create_{vartype}'), ExprList([self.fuel]))
        return rvalue

    def symbolic_rvalue(self, vartype):
        
        #Multiply sizeof by 8bits
        multiply = BinaryOp(op='*', left=FuncCall(ID('sizeof'),\
        ExprList([ID(vartype)])), right=Constant('int', str(8)))

        #Create Rvalue
        sizeof = ExprList([multiply])
        rvalue = FuncCall(ID('new_sym_var'), sizeof)

        return rvalue