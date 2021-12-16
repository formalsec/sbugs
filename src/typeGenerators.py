from pycparser import c_parser, c_ast, parse_file, c_generator
import random


# Create a primitive symbolic var
# e.g, int a = summ_new_sym_var(sizeof(int))
class SymbolicTypeGen(c_ast.NodeVisitor):
    def __init__ (self, name, vartype):

        self.arraysize = c_ast.ID('ARRAY_SIZE')
        self.fuel = c_ast.ID('FUEL')

        if isinstance(name, str):
            name = c_ast.ID(name=name)

        self.argname = name 
        self.vartype = vartype

    

    def init_struct_rvalue(self, vartype):

        vartype = self.vartype.replace(' ', '_')
        rvalue = c_ast.FuncCall(c_ast.ID(f'create_{vartype}'), c_ast.ExprList([self.fuel]))
        return rvalue

    def symbolic_rvalue(self, vartype):
        
        #Multiply sizeof by 8bits
        multiply = c_ast.BinaryOp(op='*', left=c_ast.FuncCall(c_ast.ID('sizeof'),\
        c_ast.ExprList([c_ast.ID(vartype)])), right=c_ast.Constant('int', str(8)))

        #Create Rvalue
        sizeof = c_ast.ExprList([multiply])
        rvalue = c_ast.FuncCall(c_ast.ID('summ_new_sym_var'), sizeof)

        return rvalue


#Create a symbolic struct (call respective function)
class StructTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):

        name = self.argname.name
        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[self.vartype]))
        rvalue = c_ast.FuncCall(c_ast.ID(f'create_{fname}'),c_ast.ExprList([self.fuel]) )

        #Assemble declaration
        decl = c_ast.Decl(name, [], [], [], lvalue, rvalue, None)

        return [decl]




class PrimitiveTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype):
        super().__init__(name, vartype)


    def gen(self):
        
        name = self.argname.name

        #Declare Variable
        lvalue = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[self.vartype]))

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #Assemble declaration
        decl = c_ast.Decl(name, [], [], [], lvalue, rvalue, None)
        
        return [decl]




#Create a symbolic N-dimension array
class ArrayTypeGen(SymbolicTypeGen):
    def __init__ (self, name, vartype, dimension, struct=False):
        super().__init__(name, vartype) 

        self.struct = struct
        self.dimension = dimension


    #Declare N-dimension array
    #Array[10][5];
    def gen_array_decl(self):
        name = self.argname.name

        typedecl = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[self.vartype]))
        array = c_ast.ArrayDecl(typedecl, self.arraysize, None)

        for i in range(1, self.dimension):
            array =  c_ast.ArrayDecl(array, self.arraysize, None)

        return c_ast.Decl(name, [], [], [], array, None, None)
    

    #Array[i][j] = symbolic();
    def gen_array_init(self):
        name = self.argname.name

        index = f'{name}_index_1'
        lvalue = c_ast.ArrayRef(self.argname, subscript=c_ast.ID(index))                                                              

        for i in range(2, self.dimension+1):
            
            index = f'{name}_index_{i}'
            lvalue = c_ast.ArrayRef(lvalue, subscript=c_ast.ID(index))  
        
        if self.struct:
            rvalue = self.init_struct_rvalue(self.vartype)
        else:
            rvalue = self.symbolic_rvalue(self.vartype)
        
        return c_ast.Assignment(op='=', lvalue=lvalue, rvalue=rvalue)             



    #Standard 'for' loop to fill array
    def For_ast(self, index, size, stmt):

        ##For-init
        typedecl = c_ast.TypeDecl(index, [], c_ast.IdentifierType(names=['int']))
        decl = c_ast.Decl(index, [], [], [], typedecl, c_ast.Constant('int', str(0)), None)
        init  = c_ast.DeclList(decls=[decl])
        
        ##For-condition
        cond = c_ast.BinaryOp(op='<', left=c_ast.ID(index), right=size)
        
        ##For-next
        nxt = c_ast.UnaryOp(op='p++', expr=c_ast.ID(index))

        ##Create the For node
        return c_ast.For(init, cond, nxt, stmt)
        

    #Declare array and fill
    def gen(self):     
        code = []
        name = self.argname.name
        
        #Declare array
        code.append(self.gen_array_decl())
                                                            
        stmt = c_ast.Compound([self.gen_array_init()])

        index = f'{name}_index_{self.dimension}' 
        for_ast_code = self.For_ast(index, self.arraysize, stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, self.arraysize, c_ast.Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code





class InputGenVisitor(c_ast.NodeVisitor):

    def __init__ (self, structs, aliases):


        self.structs = structs
        self.aliases = aliases

        #c_ast.ID object
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
        return c_ast.NodeVisitor.visit(self, node)
    
    #Entry Node
    def visit_Decl(self, node):
        self.argname = c_ast.ID(name=node.name)
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
        #Array 
        else:
            generator = ArrayTypeGen(self.argname, self.argtype,
            self.arrayDim, self.struct)
            self.code = generator.gen()
            return  
    

    #ArrayDecl
    def visit_ArrayDecl(self, node):
        self.arrayDim += 1
        self.visit(node.type)
        return

    
    #Struct Pype
    def visit_Struct(self, node):
        self.argtype = f'struct {node.name}'
        self.struct = True
        return


    #IdentifierType (Common and last node)
    def visit_IdentifierType(self, node):
        typ = node.names[0]
        if len(node.names):
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

