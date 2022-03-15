from pycparser.c_ast import *

import SummValidation.Utils.utils as utils

class DefaultGen(NodeVisitor):
    def __init__ (self, name, vartype):

        #Size Macros
        self.sizeMacros = {
        'array':ID(utils.ARRAY_SIZE_MACRO),
        'ptr':ID(utils.POINTER_SIZE_MACRO)
        }

        self.argname = name #ID node
        self.vartype = vartype #String

    
    def symbolic_rvalue(self, name, vartype):
        
        #Multiply sizeof by 8bits
        multiply = BinaryOp(op='*', left=FuncCall(ID('sizeof'),ExprList([ID(vartype)])), right=Constant('int', str(8)))

        #Create Rvalue
        sizeof = ExprList([name, multiply])
        rvalue = FuncCall(ID('new_sym_var'), sizeof)

        return rvalue