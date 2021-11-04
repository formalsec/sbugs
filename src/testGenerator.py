from __future__ import print_function
import sys, os
import re

from shutil import copyfile

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file, c_generator


class FunDeclVisitor(c_ast.NodeVisitor):

    def __init__ (self): 
        self.fun_dict = {}
        self.var_glob_dict = {}

    def visit_FuncDef(self, node):
        self.fun_dict[node.decl.name] = node.decl.type.args.params if node.decl.type.args else None
        #print(node)

    def visit_Decl(self, node):
        self.var_glob_dict[node.name] = node.type

def create_symb_arg ():
    # chama o argumento 

def create_tests (f_decls):
    # ...
    symb_args = list(map(create_symb_arg, f_decl))
    return 0


if __name__ == "__main__":

    ast = parse_file("example42.c", use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', '-Iloglib/fake_libc_include'])
    
    vis = FunDeclVisitor() 
    vis.visit(ast)

    fun_decls = vis.fun_dict; 

    print(vis.fun_dict)

    print(vis.var_glob_dict)

    #print(ast)

