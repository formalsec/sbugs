from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import CProcessor.TestGeneration.utils as utils
from .TypeGen import SymbolicTypeGen


#Create a symbolic N-dimension array
class ArrayTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype, array, default, struct=False):
        super().__init__(name, vartype) 

        self.default_size = ID(default) 

        self.arraysize = array
        self.dimension = len(array)
        
        self.struct = struct


    def _dimension(self, val):
        if val is None:
            return self.default_size
        else:
            return Constant('int', val)


    #Declare N-dimension array
    #Array[10][5];
    def gen_array_decl(self):
        name = self.argname.name

        typedecl = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        array = ArrayDecl(typedecl, self._dimension(self.arraysize[-1]), [])

        for i in range(self.dimension-2, -1, -1):
            array = ArrayDecl(array,  self._dimension(self.arraysize[i]), [])

        return  Decl(name, [], [], [], array, None, None)
    
    

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
        for_ast_code = self.For_ast(index, self._dimension(self.arraysize[-1]), stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, self._dimension(self.arraysize[i-1]), Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code
