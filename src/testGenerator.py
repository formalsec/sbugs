from __future__ import print_function
import sys, os
import re

from shutil import copyfile

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file, c_generator
from typeGenerators import InputGenVisitor
from structGenerator import StructGen

class FunDeclVisitor(c_ast.NodeVisitor):

    def __init__ (self): 
        self.fun_dict = {}
        self.var_glob_dict = {}
        self.structs = {}

        #Typedefed structs
        self.aliases ={}

    
    def visit(self, node):
        c_ast.NodeVisitor.visit(self, node)

    def visit_FuncDef(self, node):
        self.fun_dict[node.decl.name] = node.decl.type.args.params\
        if node.decl.type.args else None


    def visit_Decl(self, node):
        self.visit(node.type)


    def visit_Struct(self, node):
        self.structs[node.name] = node.decls


    def visit_Typedef(self, node):
        self.aliases[node.name] = node.type.type.name
        self.visit(node.type)




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

    #Return
    code.append(c_ast.Return(c_ast.ExprList([])))

    #Create a block containg the function code
    block = c_ast.Compound(code)

    #Place the block inside a function definition
    func_def_ast = c_ast.FuncDef(decl, None, block, None)

    #Generate the final string with the test
    str_ast = gen.visit(func_def_ast)

    return str_ast




#Create tests for all functions
def create_tests(f_decls):
    return [t for t in map(lambda x : create_test(x, f_decls[x]), f_decls) if t is not None] 


if __name__ == "__main__":

    ast = parse_file(sys.argv[1], use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', '-Iloglib/fake_libc_include'])
    
    
    #Visitor to get all func defs
    vis = FunDeclVisitor()
    vis.visit(ast)

    fun_decls = vis.fun_dict;
    structs = vis.structs

    #Generate functions responsible to create symbolic structs
    struct_generator = StructGen(structs)
    init_functions = struct_generator.symbolic_structs()

    #Create tests
    tests = create_tests(fun_decls)
    for t in tests:
        print(t)

