from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from TestGeneration.visitors.InputGen import InputGenVisitor
import TestGeneration.utils as utils

from .StructFields.ArrayField import ArrayFieldGen
from .StructFields.PrimitiveField import PrimitiveFieldGen
from .StructFields.StructField import StructFieldGen

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
class StructGenVisitor(NodeVisitor):
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
        
        if fields is None:
            return
        
        #Code generator
        gen = c_generator.CGenerator()

        #Fuel parameter
        paramlist = ParamList(self.init_args())

        #Create a function declaration with name 'create_<struct_name>'
        decl = utils.createFunction(name=f'create_struct_{struct_name}',\
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
        code.append(utils.returnValue(ID(f'struct_{struct_name}_instance'),'*'))


        #Create a block containg the function code
        block = Compound(code)

        #Place the block inside a function definition
        n_func_def_ast = FuncDef(decl, None, block, None)
        
        return n_func_def_ast

    
    #Create functions do instantiate all structs
    def symbolic_structs(self):
        return [s for s in map(lambda x : self.init_function(x, self.structs[x],
        self.structs, self.aliases), self.structs) if s is not None] 