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


#Create a symbolic struct (call respective function)
class StructTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):

        name = self.argname.name
        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = TypeDecl(name, [], IdentifierType(names=[self.vartype]))
        rvalue = FuncCall(ID(f'create_{fname}'),ExprList([self.fuel]) )

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)

        return [decl]




class PrimitiveTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):
        
        name = self.argname.name

        #Declare Variable
        lvalue = TypeDecl(name, [], IdentifierType(names=[self.vartype]))

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
        
        return [decl]




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





class InputGenVisitor(NodeVisitor):

    def __init__ (self, structs, aliases):

        self.sizeMacro = None

        self.structs = structs
        self.aliases = aliases

        #ID object
        self.argname = None 
        self.argtype = None

        #Array properties
        self.arrayDim = 0

        #Struct properties
        self.struct = False

        #Final line(s) of code 
        self.code = []

    #Visitors
    def visit(self, node):
        return NodeVisitor.visit(self, node)
    
    #Entry Node
    def visit_Decl(self, node):
        self.argname = ID(name=node.name)
        self.visit(node.type)                                                                    
        return

    #TypeDecl (Common node)
    def visit_TypeDecl(self, node):
        self.visit(node.type)

        #Single
        if self.arrayDim == 0:
            
            #Struct
            if self.struct:
                generator = StructTypeGen(self.argname, self.argtype)
                self.code = generator.gen()
                return
            
            #Primitive Type
            else:
                generator = PrimitiveTypeGen(self.argname, self.argtype)
                self.code = generator.gen()
                return
        
        #Array or pointer
        else:
            generator = ArrayTypeGen(self.argname, self.argtype,
            self.arrayDim, self.sizeMacro, self.struct)
            self.code = generator.gen()
            return  
    

    #ArrayDecl
    def visit_ArrayDecl(self, node):
        self.arrayDim += 1
        self.sizeMacro = utils.ARRAY_SIZE_MACRO
        self.visit(node.type)
        return


    #Pointer
    def visit_PtrDecl(self, node):
        if isinstance(node.type, FuncDecl):
            self.code = None
            return

        self.arrayDim += 1
        self.sizeMacro = utils.POINTER_SIZE_MACRO
        self.visit(node.type)
        return

    
    #Struct Type
    def visit_Struct(self, node):
        self.argtype = f'struct {node.name}'
        self.struct = True
        return


    #IdentifierType (Common and last node)
    def visit_IdentifierType(self, node):
        typ = node.names[0]
        if len(node.names) > 1:
            for t in node.names[1:]:
                typ += f' {t}' 
        
        #Type is a typedef alias
        if typ in self.aliases.keys():
            typ = self.aliases[typ]
            
            #Typedef struct
            if typ in self.structs.keys():
                typ = f'struct {typ}'
                self.struct = True

        self.argtype = typ
        return

