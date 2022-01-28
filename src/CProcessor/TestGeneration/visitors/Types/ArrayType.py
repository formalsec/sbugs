from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import CProcessor.TestGeneration.utils as utils
from .TypeGen import SymbolicTypeGen


#Create a symbolic N-dimension array
class ArrayTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype, dimension, array, struct=False):
        super().__init__(name, vartype) 

        self.arraysize = ID(array)
        self.struct = struct
        self.dimension = dimension


    #Declare N-dimension array
    #Array[10][5];
    def gen_array_decl(self):
        name = self.argname.name

        typedecl = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        array = ArrayDecl(typedecl, self.arraysize, None)

        for i in range(1, self.dimension):
            array =  ArrayDecl(array, self.arraysize, None)

        return Decl(name, [], [], [], array, None, None)
    

    #Array[i][j] = symbolic();
    def gen_array_init(self):
        name = self.argname.name

        index = f'{name}_index_1'
        lvalue = ArrayRef(self.argname, subscript=ID(index))                                                              

        for i in range(2, self.dimension+1):
            
            index = f'{name}_index_{i}'
            lvalue = ArrayRef(lvalue, subscript=ID(index))  
        
        if self.struct:
            rvalue = self.init_struct_rvalue(self.vartype)
        else:
            rvalue = self.symbolic_rvalue(self.vartype)
        
        return Assignment(op='=', lvalue=lvalue, rvalue=rvalue)             



    #Standard 'for' loop to fill array
    def For_ast(self, index, size, stmt):

        ##For-init
        typedecl = TypeDecl(index, [], IdentifierType(names=['int']))
        decl = Decl(index, [], [], [], typedecl, Constant('int', str(0)), None)
        init  = DeclList(decls=[decl])
        
        ##For-condition
        cond = BinaryOp(op='<', left=ID(index), right=size)
        
        ##For-next
        nxt = UnaryOp(op='p++', expr=ID(index))

        ##Create the For node
        return For(init, cond, nxt, stmt)
        

    #Declare array and fill
    def gen(self):     
        code = []
        name = self.argname.name
        
        #Declare array
        code.append(self.gen_array_decl())
                                                            
        stmt = Compound([self.gen_array_init()])

        index = f'{name}_index_{self.dimension}' 
        for_ast_code = self.For_ast(index, self.arraysize, stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, self.arraysize, Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code
