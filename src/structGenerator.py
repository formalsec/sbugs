from pycparser import c_parser, c_ast, parse_file, c_generator
from typeGenerators import InputGenVisitor
import random


#Class responsible for creating symbolic struct fields
class SymbolicFieldGen(c_ast.NodeVisitor):
    def __init__ (self, name, vartype, struct_name, field):

        if isinstance(name, str):
            name = c_ast.ID(name=name)

        self.arraysize = c_ast.ID('ARRAY_SIZE')
        self.fuel = c_ast.ID('FUEL')

        self.argname = name 
        self.vartype = vartype
        self.struct_name = struct_name
        self.field = field
    


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


#Struct inside Struct
class StructFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype, struct_name, field)


    #Recursive struct 
    # if(fuel > 0) struct->field = create_this_struct(fuel-1)
    # else struct->field = NULL
    def recursiveStruct(self, name, lvalue, fname):   
        
        #(fuel > 0)
        cond = c_ast.BinaryOp(op='>', left=c_ast.ID('fuel'), right=c_ast.Constant('int', str(0)))

        #(fuel-1)
        fuel = c_ast.BinaryOp(op='-', left=c_ast.ID('fuel'), right=c_ast.Constant('int', str(1)))
        
        #create_this_struct(fuel-1)
        rvalue = c_ast.FuncCall(c_ast.ID(f'create_{fname}'),c_ast.ExprList([fuel]) )
        
        #Assemble If
        if_decl = c_ast.Decl(name, [], [], [], [], lvalue, rvalue, None)
        else_decl = c_ast.Decl(name, [], [], [], [], lvalue, c_ast.ID('NULL'), None)
        if_fuel = c_ast.If(cond, c_ast.Compound([if_decl]), c_ast.Compound([else_decl]))

        return [if_fuel]

    
    #struct->field = create_struct(fuel)
    def gen(self):
        code = []
        name = f'struct_{self.struct_name}_instance' 

        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = c_ast.StructRef(name = c_ast.ID(f'{name}'), type='->', field=c_ast.ID(f'{self.field}'))

        #Recursive struct
        if f'struct_{self.struct_name}' == fname:
            code += self.recursiveStruct(name, lvalue, fname)
        
        #Other struct
        else:
            rvalue = c_ast.FuncCall(c_ast.ID(f'create_{fname}'),c_ast.ExprList([self.fuel]) )
            decl = c_ast.Decl(name, [], [], [], [], lvalue, rvalue, None)
            code.append(decl)   
        
        return code



#Primitive type struct field
class PrimitiveFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype, struct_name, field)


    #E.g: struct->field = summ_new_sym_var(32)
    def gen(self):
        
        name = f'struct_{self.struct_name}_instance' 

        #Make symbolic type
        rvalue = self.symbolic_rvalue(self.vartype)

        #struct->field
        lvalue = c_ast.StructRef(name = c_ast.ID(f'{name}'), type='->', field=c_ast.ID(f'{self.field}'))

        #Assemble declaration
        decl = c_ast.Decl(name, [], [], [], [], lvalue, rvalue, None)
        return [decl]




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
        lvalue = c_ast.ArrayRef(self.argname, subscript=c_ast.ID(index))                                                              

        #Loop for N array dimensions array[][]...
        for i in range(2, self.dimension+1):
            
            index = f'{name}_index_{i}'
            lvalue = c_ast.ArrayRef(lvalue, subscript=c_ast.ID(index))  

        #struct_instance->Array[i][j]
        sname = f'struct_{self.struct_name}_instance'   
        lvalue = c_ast.StructRef(name = c_ast.ID(f'{sname}'), type='->', field=lvalue)
        
        #Return assignment
        if self.struct:
            rvalue = self.init_struct_rvalue(self.vartype)
        else:
            rvalue = self.symbolic_rvalue(self.vartype)
        
        return c_ast.Assignment(op='=', lvalue=lvalue, rvalue=rvalue)             



    #Create 'for' loop to fill array
    def For_ast(self, index, size, stmt):

        ##For-init
        typedecl = c_ast.TypeDecl(index, [], None, c_ast.IdentifierType(names=['int']))
        decl = c_ast.Decl(index, [], [], [], [], typedecl, c_ast.Constant('int', str(0)), None)
        init  = c_ast.DeclList(decls=[decl])
        
        ##For-condition
        cond = c_ast.BinaryOp(op='<', left=c_ast.ID(index), right=c_ast.Constant('int', str(size)))
        
        ##For-next
        nxt = c_ast.UnaryOp(op='p++', expr=c_ast.ID(index))

        ##Create the For node
        return c_ast.For(init, cond, nxt, stmt)
        

    #Fill array field
    def gen(self):     
        code = []
        name = self.argname.name
                          
        stmt = c_ast.Compound([self.gen_array_init()])

        sizes = self.sizes

        index = f'{name}_index_{self.dimension}' 
        for_ast_code = self.For_ast(index, sizes.pop(0), stmt)

        for i in range(self.dimension-1, 0 ,-1):
            index = f'{name}_index_{i}'
            for_ast_code = self.For_ast(index, sizes.pop(0), c_ast.Compound([for_ast_code])) 

        code.append(for_ast_code)
        return code


class StructFieldGenVisitor(c_ast.NodeVisitor):

    def __init__ (self, struct_name, field, structs, aliases):

        self.structs = structs
        self.aliases = aliases

        self.struct_name = struct_name
        self.field = field
        
        #c_ast.ID object
        self.argname = None 
        self.argtype = None

        #Array properties
        self.arrayDim = 0
        self.sizes = []

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

        if self.arrayDim == 0:
            if self.struct:
                generator = StructFieldGen(self.argname, self.argtype,
                self.struct_name, self.field)
                self.code = generator.gen()
                return
            else:
                generator = PrimitiveFieldGen(self.argname, self.argtype,
                self.struct_name, self.field)
                self.code = generator.gen()
                return    

        else:
            generator = ArrayFieldGen(self.argname, self.argtype, self.struct_name,
            self.field, self.arrayDim, self.sizes, self.struct)
            self.code = generator.gen()
            return   

    #ArrayDecl
    def visit_ArrayDecl(self, node):
        self.sizes.append(int(node.dim.value))
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






#Generates the functions to init symbolic structs
class StructGen(c_ast.NodeVisitor):
    def __init__ (self, structs, aliases):

        self.aliases = aliases
        self.structs = structs

    #Arguments of init function
    # only 'fuel' arg so far
    # create_struct_X(fuel)  
    
    def init_args(self):
        args = []
        
        typedecl = c_ast.TypeDecl('fuel', [], None, c_ast.IdentifierType(names=['int']))
        decl = c_ast.Decl('fuel', [], [], [], [], typedecl, None, None)

        args.append(decl)
        return args

    
    #Allocate memory for struct
    #malloc(sizeof(struct))
    def malloc_struct(self, struct_name):

        typ = f'struct {struct_name}'
        name = f'struct_{struct_name}_instance' 

        lvalue = c_ast.TypeDecl(name, [], None, c_ast.IdentifierType(names=[typ]))
        rvalue = c_ast.FuncCall(c_ast.ID('malloc'),c_ast.ExprList([c_ast.FuncCall(c_ast.ID('sizeof'),\
        c_ast.ExprList([c_ast.ID(typ)]))]) )

        #Assemble declaration
        decl = c_ast.Decl(name, [], [], [], [], c_ast.PtrDecl([], lvalue), rvalue, None)

        return decl


    def init_function(self, struct_name, fields, structs, aliases):
        
        #Code generator
        gen = c_generator.CGenerator()

        #Create return of type struct
        typedecl = c_ast.TypeDecl(f'create_struct_{struct_name}', [], None, c_ast.IdentifierType(names=[f'struct {struct_name}']))

        #Fuel parameter
        paramlist = c_ast.ParamList(self.init_args())

        #Create a function declaration with name 'create_<struct_name>'
        funcdecl = c_ast.FuncDecl(paramlist, typedecl)
        decl = c_ast.Decl(f'create_{struct_name}', [], [], [], [], funcdecl, None, None)

        code = []

        code.append(self.malloc_struct(struct_name))

        
        #Visit fields 
        for field in fields:

            vis = StructFieldGenVisitor(struct_name, field.name, structs, aliases)   
            vis.visit(field)

            code += vis.code

        
        #Return struct
        code.append(c_ast.Return(c_ast.ExprList([c_ast.ID(f'struct_{struct_name}_instance')])))

        #Create a block containg the function code
        block = c_ast.Compound(code)

        #Place the block inside a function definition
        n_func_def_ast = c_ast.FuncDef(decl, None, block, None)

        #Generate the final string with the test
        str_ast = gen.visit(n_func_def_ast)
        return str_ast

    
    #Create functions do instantiate all structs
    def symbolic_structs(self):
        return [s for s in map(lambda x : self.init_function(x, self.structs[x],
        self.structs, self.aliases), self.structs) if s is not None] 