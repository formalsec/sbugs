from pycparser import parse_file, c_generator
from pycparser.c_ast import *

from .Types.ArrayType import ArrayTypeGen
from .Types.PrimitiveType import PrimitiveTypeGen
from .Types.StructType import StructTypeGen
import CProcessor.TestGeneration.utils as utils
from CProcessor import config



class InputGenVisitor(NodeVisitor):

    def __init__ (self, structs, aliases):

        #Store argument node (Decl)
        self.node = None

        self.sizeMacro = None

        self.structs = structs
        self.aliases = aliases

        #ID object
        self.argname = None 
        self.argtype = None

        #Array properties
        self.arrayDim = []

        #Struct properties
        self.struct = False

        #Final line(s) of code 
        self.code = []


    #Return generated code
    #If HEAP=true, change declaration of
    #arrays (dim: 2+) in function headers
    def gen_code(self):   
        if len(self.arrayDim) > 1 and config.HEAP:
            ptr = PtrDecl([], TypeDecl(self.argname, [], IdentifierType([self.argtype])))
            for _ in range(1, len(self.arrayDim)):
                ptr = PtrDecl([], ptr)

            self.node.type = ptr
        
        return self.code

    #Visitors
    def visit(self, node):
        
        #Store top 'Decl' node
        if isinstance(node,Decl):
            self.node = node
        
        return NodeVisitor.visit(self, node)
    
    #Entry Node
    def visit_Decl(self, node):
        self.argname = node.name
        self.visit(node.type)                                                                    
        return

    #TypeDecl (Common node)
    def visit_TypeDecl(self, node):
        self.visit(node.type)
        argname = ID(self.argname)

        #Single
        if len(self.arrayDim) == 0:
            
            #Struct
            if self.struct:
                generator = StructTypeGen(argname, self.argtype)
                self.code = generator.gen()
                return
            
            #Primitive Type
            else:
                generator = PrimitiveTypeGen(argname, self.argtype)
                self.code = generator.gen()
                return
        
        #Array or pointer
        else:
            generator = ArrayTypeGen(argname, self.argtype,
            self.arrayDim, self.sizeMacro, self.struct)
            self.code = generator.gen()
            return  
    

    #ArrayDecl
    def visit_ArrayDecl(self, node):
        if node.dim is not None:
            self.arrayDim.append(node.dim.value)

        else:
            self.arrayDim.append(None)
        self.sizeMacro = utils.ARRAY_SIZE_MACRO
        self.visit(node.type)

        return


    #Pointer
    def visit_PtrDecl(self, node):
        if isinstance(node.type, FuncDecl):
            self.code = None
            return

        self.arrayDim.append(None)

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

