from pycparser import parse_file, c_generator
from pycparser.c_ast import *

import CProcessor.TestGeneration.utils as utils
from CProcessor import config

from .TypeGen import SymbolicTypeGen


#Create a symbolic N-dimension array
class ArrayTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype, array, default, struct=False):
        super().__init__(name, vartype) 

        self.default_size = ID(default) 

        self.arraysize = array
        self.dimension = len(array)
        
        self.struct = struct


    def _size(self, val):
        if val is None:
            return self.default_size
        else:
            return Constant('int', val)


    #Declare N-dimension array
    #Stack -> array[10][5];
    #Heap -> *array = malloc(sizeof(int *) * 10);
    
    def gen_array_decl(self, heap=config.HEAP):
        name = self.argname.name
        typedecl = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        code = []

        #Stack
        if not heap:

            array = ArrayDecl(typedecl, self._size(self.arraysize[-1]), [])

            for i in range(self.dimension-2, -1, -1):
                array = ArrayDecl(array,  self._size(self.arraysize[i]), [])

            code.append(Decl(name, [], [], [], array, None, None))
            return code  
        
        #Heap
        else:

            #sizeof(int *)
            typtr = PtrDecl([], TypeDecl(name, [], IdentifierType([self.vartype])))
            for _ in range(1, self.dimension-1):
                typtr = PtrDecl([], typtr)
            sizeof = FuncCall(ID('sizeof'), ExprList([typtr]))
     
            #(sizeof(int *) * 10
            size = BinaryOp('*', sizeof, self._size(self.arraysize[0]))

            #malloc(sizeof(int *) * 10);
            rvalue = FuncCall(ID('malloc'),ExprList([size]) )
            
            #int **array
            arrptr = PtrDecl([], typedecl)
            for _ in range(1, self.dimension):
                arrptr = PtrDecl([], arrptr)

            #int **array = malloc(sizeof(int) * 10);
            code.append(Decl(name, [], [], [], arrptr, rvalue, None))
            
            #For 2+ dimensions (e.g array[][])
            if self.dimension > 1:

                typtr = IdentifierType([self.vartype])
                sizeof = FuncCall(ID('sizeof'), ExprList([typtr]))
                
                index = f'malloc_idx_1'
                arrayref = ArrayRef(ID(name), ID(index))
                for i in range(2, self.dimension):
                    index = f'malloc_idx_{i}'
                    arrayref = ArrayRef(arrayref, ID(index))
                
                binop = BinaryOp('*', sizeof, self._size(self.arraysize[-1]))
                stmt = Assignment('=', arrayref, FuncCall(ID('malloc'),ExprList([binop])))
                decls = self.For_ast(index, self._size(self.arraysize[-2]), Compound([stmt]))

                typtr = PtrDecl([], TypeDecl(name, [], typtr))

                #For 3+ dimensions (e.g array[0][1][2])
                for i in range(self.dimension-2, 0,-1):

                    index = f'malloc_idx_1'
                    arrayref = ArrayRef(ID(name), ID(index))
                    for j in range(2, i+1):
                        index = f'malloc_idx_{j}'
                        arrayref = ArrayRef(arrayref, ID(index))

                    
                    sizeof = FuncCall(ID('sizeof'), ExprList([typtr]))
                    binop = BinaryOp('*', sizeof, self._size(self.arraysize[i]))
                    stmt = Assignment('=', arrayref, FuncCall(ID('malloc'),ExprList([binop])))
                    decls = self.For_ast(index, self._size(self.arraysize[i-1]), Compound([stmt,decls]))

                    typtr = PtrDecl([], typtr)

                code.append(decls)

            return code

    

    #Array[i][j] = symbolic();
    def gen_array_init(self):
        name = self.argname.name

        index = f'{name}_idx_1'
        lvalue = ArrayRef(self.argname, subscript=ID(index))                                                              

        for i in range(2, self.dimension+1):
            
            index = f'{name}_idx_{i}'
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
        code += self.gen_array_decl()
                                                            
        stmt = Compound([self.gen_array_init()])

        index = f'{name}_idx_{self.dimension}' 
        for_ast_code = self.For_ast(index, self._size(self.arraysize[-1]), stmt)

        for i in range(self.dimension-2, -1 ,-1):
            index = f'{name}_idx_{i+1}'
            for_ast_code = self.For_ast(index, self._size(self.arraysize[i]), Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code
