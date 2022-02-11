from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from .SymbolicField import SymbolicFieldGen
import CProcessor.TestGeneration.utils as utils



#N-dimension pointer struct field
class PtrFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field, dimension, sizes, struct=False):
        super().__init__(name, vartype, struct_name, field) 

        self.struct = struct
        self.dimension = dimension
        self.sizes = sizes



    def recursiveStruct(self, name, lvalue, ptr, fname):   
        code = []

        cond = BinaryOp(op='>', left=self.fuel, right=Constant('int', str(0)))

        fuel = BinaryOp(op='-', left=self.fuel, right=Constant('int', str(1)))
        rvalue = FuncCall(ID(f'create_{fname}'),ExprList([fuel]) )
        ifdecl = Decl(name, [], [], [], lvalue, rvalue, None)

        elsedecl = Decl(name, [], [], [], ptr, ID('NULL'), None)

        iffuel = If(cond, Compound([ifdecl]), Compound([elsedecl]))

        code.append(iffuel)
        return code    



    def _size(self, val):
        if val is None:
            return self.default_size
        else:
            return Constant('int', val)



    def gen_ptr_decl(self):
        name = self.argname.name
        typedecl = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        code = []

        #sizeof(int *)
        typtr = PtrDecl([], TypeDecl(name, [], IdentifierType([self.vartype])))
        for _ in range(1, self.dimension-1):
            typtr = PtrDecl([], typtr)
        sizeof = FuncCall(ID('sizeof'), ExprList([typtr]))
 
        #(sizeof(int *) * 10
        size = BinaryOp('*', sizeof, self._size(self.sizes[0]))

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
            
            binop = BinaryOp('*', sizeof, self._size(self.sizes[-1]))
            stmt = Assignment('=', arrayref, FuncCall(ID('malloc'),ExprList([binop])))
            decls = self.For_ast(index, self._size(self.sizes[-2]), Compound([stmt]))

            typtr = PtrDecl([], TypeDecl(name, [], typtr))

            #For 3+ dimensions (e.g array[0][1][2])
            for i in range(self.dimension-2, 0,-1):

                index = f'malloc_idx_1'
                arrayref = ArrayRef(ID(name), ID(index))
                for j in range(2, i+1):
                    index = f'malloc_idx_{j}'
                    arrayref = ArrayRef(arrayref, ID(index))

                
                sizeof = FuncCall(ID('sizeof'), ExprList([typtr]))
                binop = BinaryOp('*', sizeof, self._size(self.sizes[i]))
                stmt = Assignment('=', arrayref, FuncCall(ID('malloc'),ExprList([binop])))
                decls = self.For_ast(index, self._size(self.sizes[i-1]), Compound([stmt,decls]))

                typtr = PtrDecl([], typtr)

            code.append(decls)

        return code


    #struct->ptr[i][j] = symbolic();
    def gen_ptr_init(self):
        name = self.argname.name


        #array[index]
        index = f'{name}_index_1'
        lvalue = ArrayRef(self.argname, subscript=ID(index))                                                              

        #Loop for N array dimensions array[][]...
        for i in range(2, self.dimension+1):
            
            index = f'{name}_index_{i}'
            lvalue = ArrayRef(lvalue, subscript=ID(index))  

        #struct_instance->Array[i][j]
        sname = f'struct_{self.struct_name}_instance'   
        lvalue = StructRef(name = ID(f'{sname}'), type='->', field=lvalue)

        ptr = StructRef(name = ID(f'{sname}'), type='->', field=self.argname)
        
        fname = self.vartype.replace(' ', '_')

        #Return assignment
        if self.struct:
            
            #Recursive struct
            if f'struct_{self.struct_name}' == fname:
                return self.recursiveStruct(name, lvalue, ptr, fname)

            #Other struct
            else:
                rvalue = self.init_struct_rvalue(self.vartype)
        else:
            rvalue = self.symbolic_rvalue(self.vartype)
        
        return [Assignment(op='=', lvalue=lvalue, rvalue=rvalue)]             



    #Create 'for' loop to fill array
    def For_ast(self, index, size, stmt):

        ##For-init
        typedecl = TypeDecl(index, [], IdentifierType(names=['int']))
        decl = Decl(index, [], [], [], typedecl, Constant('int', str(0)), None)
        init  = DeclList(decls=[decl])
        
        ##For-condition
        if isinstance(size, int):
            size = Constant('int', str(size))

        elif isinstance(size, str):
            size = ID(size)
        
        cond = BinaryOp(op='<', left=ID(index), right=size)
        
        ##For-next
        nxt = UnaryOp(op='p++', expr=ID(index))

        ##Create the For node
        return For(init, cond, nxt, stmt)
        

    #Fill array field
    def gen(self):     
        code = []
        name = self.argname.name

        code += self.gen_ptr_decl()
                          
        stmt = Compound(self.gen_ptr_init())
        sizes = self.sizes

        index = f'{name}_index_{self.dimension}' 
        for_ast_code = self.For_ast(index, sizes.pop(0), stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, sizes.pop(0), Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code
