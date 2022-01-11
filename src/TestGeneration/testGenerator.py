#!/usr/bin/env python3

from __future__ import print_function
import argparse
import sys, os
import re

from shutil import copyfile

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file, c_generator
from typeGenerators import InputGenVisitor
from structGenerator import StructGen
from utils import defineMacro, mainFunction


#Visit the ASt to separate each elemenet of interest
#function definitions; defined structs; and Typedefs 
class InitialVisitor(c_ast.NodeVisitor):

    def __init__ (self): 
        self.fun_dict = {}
        self.var_glob_dict = {}
        self.structs = {}

        #Typedefed structs
        self.aliases = {}

    
    def visit(self, node):
        c_ast.NodeVisitor.visit(self, node)

    def visit_FuncDef(self, node):
        self.fun_dict[node.decl.name] = node.decl.type.args.params\
        if node.decl.type.args else None


    def visit_Struct(self, node):
        self.structs[node.name] = node.decls


    def visit_Typedef(self, node):
        self.aliases[node.name] = node.type.type.name
        self.visit(node.type)





#Create a single test
def create_test(fname, args, structs, aliases):

    #Ignore 'main' function
    if fname == 'main':
        return ('main', None)

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

        vis = InputGenVisitor(structs,aliases)   
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

    return (f'test_{fname}', str_ast)


#Create tests for all functions
def create_tests(f_decls, structs, aliases):
    return {k: v for k, v in map(lambda x :\
    create_test(x, f_decls[x], structs, aliases), f_decls) if v is not None} 




def get_cmd_args():
    parser = argparse.ArgumentParser(description='Generate Symbolic Tests')

    parser.add_argument('-o', metavar='name', type=str, required=False, default='out.c',
                        help='Output name')

    parser.add_argument('--fuel', metavar='value', type=int, required=False, default=5,
                        help='Define \'Fuel\' value (default:5)')

    parser.add_argument('--arraySize', metavar='value', type=int, required=False, default=10,
                        help='Define array size (default:10)')

    parser.add_argument('targetFile', metavar='file', type=str,
                        help='The name of the target C file')

    return parser.parse_args()



if __name__ == "__main__":

    #Command line arguments
    args = get_cmd_args()
    inputFile = args.targetFile
    outFile = args.o
    fuel = args.fuel
    arraySize = args.arraySize

    ast = parse_file(args.targetFile, use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', '-Iloglib/fake_libc_include'])

    #Initial visitor to get all relevant elements
    vis = InitialVisitor()
    vis.visit(ast)

    fun_decls = vis.fun_dict
    structs = vis.structs
    aliases = vis.aliases

    
    #Final list of strings to be written to file
    codeList = []

    #Add Macros for size (array size and fuel)
    codeList.append(defineMacro('FUEL', fuel))
    codeList.append(defineMacro('ARRAY_SIZE', arraySize)+'\n')

    #Generate functions responsible to create symbolic structs
    struct_generator = StructGen(structs, aliases)
    codeList +=  struct_generator.symbolic_structs()

    #Create actual tests
    testsDict = create_tests(fun_decls, structs, aliases) 
    codeList += testsDict.values()

    #Create main function and call tests
    codeList.append(mainFunction(testsDict.keys()))

    #Write to actual file
    file = open(outFile, "w")
    for c in codeList:
        file.write(f'{c}\n')


