from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import SummValidation.Utils.utils as utils



class DefaultGen(NodeVisitor):
    def __init__ (self, name, vartype):

        #Size Macros
        self.sizeMacros = {
        'array':ID(utils.ARRAY_SIZE_MACRO),
        'ptr':ID(utils.POINTER_SIZE_MACRO)
        }

        #Fuel Macro
        self.fuel = ID(utils.FUEL_MACRO)

        self.argname = name #ID node
        self.vartype = vartype #String

    
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