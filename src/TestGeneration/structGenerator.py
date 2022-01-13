from pycparser import c_parser, parse_file, c_generator
from pycparser.c_ast import *
from typeGenerators import InputGenVisitor
import utils

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
        rvalue = FuncCall(ID('summ_new_sym_var'), sizeof)

        return rvalue



    #Recursive struct 
    # if(fuel > 0) struct->field = create_this_struct(fuel-1)
    # else struct->field = NULL
    def recursiveStruct(self, name, lvalue, fname):   
        
        #(fuel > 0)
        cond = BinaryOp(op='>', left=ID('fuel'), right=Constant('int', str(0)))

        #(fuel-1)
        fuel = BinaryOp(op='-', left=ID('fuel'), right=Constant('int', str(1)))
        
        #create_this_struct(fuel-1)
        rvalue = FuncCall(ID(f'create_{fname}'),ExprList([fuel]) )
        
        #Assemble If
        if_decl = Decl(name, [], [], [], lvalue, rvalue, None)
        else_decl = Decl(name, [], [], [], lvalue, ID('NULL'), None)
        if_fuel = If(cond, Compound([if_decl]), Compound([else_decl]))

        return if_fuel    


#Struct inside Struct
class StructFieldGen(SymbolicFieldGen):
    def __init__ (self, name, vartype, struct_name, field):
        super().__init__(name, vartype, struct_name, field)


    #struct->field = create_struct(fuel)
    def gen(self):
        code = []
        name = f'struct_{self.struct_name}_instance' 

        fname = self.vartype.replace(' ', '_')

        #Declare Variable
        lvalue = StructRef(name = ID(f'{name}'), type='->', field=ID(f'{self.field}'))

        #Recursive struct
        if f'struct_{self.struct_name}' == fname:
            code.append(self.recursiveStruct(name, lvalue, fname))
        
        #Other struct
        else:
            rvalue = self.init_struct_rvalue(self.vartype)
            decl = Decl(name, [], [], [], lvalue, rvalue, None)
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
        lvalue = StructRef(name = ID(f'{name}'), type='->', field=ID(f'{self.field}'))

        #Assemble declaration
        decl = Decl(name, [], [], [], lvalue, rvalue, None)
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


class StructFieldGenVisitor(NodeVisitor):

    def __init__ (self, struct_name, field, structs, aliases):

        self.structs = structs
        self.aliases = aliases

        self.struct_name = struct_name
        self.field = field
        
        #ID object
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
        return NodeVisitor.visit(self, node)
    
    #Entry Node
    def visit_Decl(self, node):
        self.argname = ID(name=node.name)
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

    #Pointer
    def visit_PtrDecl(self, node):
        self.sizes.append(utils.POINTER_SIZE_MACRO)
        self.arrayDim += 1
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
class StructGen(NodeVisitor):
    def __init__ (self, structs, aliases):

        self.aliases = aliases
        self.structs = structs

    #Arguments of init function
    # only 'fuel' arg so far
    # create_struct_X(fuel)  
    
    def init_args(self):
        args = []
        
        typedecl = TypeDecl('fuel', [], IdentifierType(names=['int']))
        decl = Decl('fuel', [], [], [], typedecl, None, None)

        args.append(decl)
        return args

    
    #Allocate memory for struct
    #malloc(sizeof(struct))
    def malloc_struct(self, struct_name):

        typ = f'struct {struct_name}'
        name = f'struct_{struct_name}_instance' 

        lvalue = TypeDecl(name, [], IdentifierType(names=[typ]))
        rvalue = FuncCall(ID('malloc'),ExprList([FuncCall(ID('sizeof'),\
        ExprList([ID(typ)]))]) )

        #Assemble declaration
        decl = Decl(name, [], [], [], PtrDecl([], lvalue), rvalue, None)

        return decl


    def init_function(self, struct_name, fields, structs, aliases):
        
        #Code generator
        gen = c_generator.CGenerator()

        #Fuel parameter
        paramlist = ParamList(self.init_args())

        #Create a function declaration with name 'create_<struct_name>'
        decl = utils.createFunction(name=f'create_{struct_name}',\
               args=paramlist,\
               returnType=f'struct {struct_name}')

        code = []
        code.append(self.malloc_struct(struct_name))
        
        #Visit fields 
        for field in fields:

            vis = StructFieldGenVisitor(struct_name, field.name, structs, aliases)   
            vis.visit(field)

            code += vis.code
        
        #Return struct
        code.append(utils.returnValue(ID(f'struct_{struct_name}_instance')))


        #Create a block containg the function code
        block = Compound(code)

        #Place the block inside a function definition
        n_func_def_ast = FuncDef(decl, None, block, None)

        #Generate the final string with the test
        str_ast = gen.visit(n_func_def_ast)
        return str_ast

    
    #Create functions do instantiate all structs
    def symbolic_structs(self):
        return [s for s in map(lambda x : self.init_function(x, self.structs[x],
        self.structs, self.aliases), self.structs) if s is not None] 