from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from TestGeneration.visitors.InputGen import InputGenVisitor
import TestGeneration.utils as utils


#Class responsible for creating symbolic struct fields
class SymbolicFieldGen(NodeVisitor):
    def __init__ (self, name, vartype, struct_name, field):

        if isinstance(name, str):
            name = ID(name=name)

        self.fuel = ID('fuel')

        self.argname = name 
        self.vartype = vartype
        self.struct_name = struct_name
        self.field = field
    


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