from __future__ import print_function
import sys, os
import re

from shutil import copyfile

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file, c_generator
from typeGenerators import PrimitiveTypeGen, ArrayTypeGen


class FunDeclVisitor(c_ast.NodeVisitor):

    def __init__ (self): 
        self.fun_dict = {}
        self.var_glob_dict = {}    

    def visit_FuncDef(self, node):
        self.fun_dict[node.decl.name] = node.decl.type.args.params if node.decl.type.args else None


    def visit_Decl(self, node):
        self.var_glob_dict[node.name] = node




class InputGenVisitor(c_ast.NodeVisitor):

    def __init__ (self):

        #c_ast.ID object
        self.argname = None 
        self.argtype = None

        #Array properties
        self.arrayDim = 0

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

    #TypeDecl
    def visit_TypeDecl(self, node):
        self.visit(node.type)

        if self.arrayDim == 0:
            generator = PrimitiveTypeGen(self.argname, self.argtype)
            self.code = generator.gen()
            return

        elif self.arrayDim > 0:
            generator = ArrayTypeGen(self.argname, self.argtype, self.arrayDim)
            self.code = generator.gen()
            return 
    

    #ArrayDecl
    def visit_ArrayDecl(self, node):
        self.arrayDim += 1
        self.visit(node.type)
        return

    #Final Node
    def visit_IdentifierType(self, node):
        self.argtype = node.names[0]
        return



#Create a single test
def create_test(fname, args):

    #Ignore 'main' function
    if fname == 'main':
        return

    #Function has no arguments
    if args is None:
        args = []

    #Code generator
    gen = c_generator.CGenerator()


    #Create a void return type
    typedecl = c_ast.TypeDecl(f'test_{fname}', [], c_ast.IdentifierType(names=['void']))
    
    #Create a function declaration with name 'test_<fname>'
    funcdecl = c_ast.FuncDecl(None, typedecl)
    decl = c_ast.Decl(f'test_{fname}', [], [], [], funcdecl, None, None)
    
    #Arguments to call the function
    call_args = []
    
    #Ast code to be generated
    code = []

    #Visit arguments 
    for arg in args:
        
        vis = InputGenVisitor()   
        vis.visit(arg)
        
        call_args.append(vis.argname) 
        code += vis.code

   
    #Add the function call to the Ast
    code.append(c_ast.FuncCall(c_ast.ID(fname), c_ast.ExprList(call_args)))

    #Create a block containg the function code
    block = c_ast.Compound(code)

    #Place the block inside a function definition
    n_func_def_ast = c_ast.FuncDef(decl, None, block, None)

    #Generate the final string with the test
    str_ast = gen.visit(n_func_def_ast)

    return str_ast




#Create tests for all functions
def create_tests (f_decls):
    return [t for t in map(lambda x : create_test(x, f_decls[x]), f_decls) if t is not None] 


if __name__ == "__main__":

    ast = parse_file(sys.argv[1], use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', '-Iloglib/fake_libc_include'])
    
    
    #Visitor to get all func defs
    vis = FunDeclVisitor()
    vis.visit(ast)
    fun_decls = vis.fun_dict;

    #Create tests
    tests = create_tests(fun_decls)
    for t in tests:
        print(t)

