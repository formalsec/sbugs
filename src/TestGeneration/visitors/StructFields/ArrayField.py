from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from TestGeneration.visitors.InputGen import InputGenVisitor
from .SymbolicField import SymbolicFieldGen
import TestGeneration.utils as utils


#N-dimension array struct field
class ArrayFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field, dimension, sizes, struct=False):
        super().__init__(name, vartype, struct_name, field) 

        self.struct = struct
        self.dimension = dimension
        self.sizes = sizes
        self.sizes.reverse()


    #struct->Array[i][j] = symbolic();
    def gen_array_init(self):
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
        
        fname = self.vartype.replace(' ', '_')

        #Return assignment
        if self.struct:
            
            #Recursive struct
            if f'struct_{self.struct_name}' == fname:
                return self.recursiveStruct(name, lvalue, fname)

            #Other struct
            else:
                rvalue = self.init_struct_rvalue(self.vartype)
        else:
            rvalue = self.symbolic_rvalue(self.vartype)
        
        return Assignment(op='=', lvalue=lvalue, rvalue=rvalue)             



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
                          
        stmt = Compound([self.gen_array_init()])
        sizes = self.sizes

        index = f'{name}_index_{self.dimension}' 
        for_ast_code = self.For_ast(index, sizes.pop(0), stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, sizes.pop(0), Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code
