from __future__ import print_function
import random
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


    def visit_Decl(self, node):
        self.var_glob_dict[node.name] = node


class InputGenVisitor(c_ast.NodeVisitor):

    def __init__ (self):

        #c_ast.ID object
        self.argname = None 

        self.argtype = None

        #Final line(s) of code 
        self.code = []


    #Create a symbolic array (uses a 'For' loop to fill array)
    def create_sym_array(self, argname, vartype, size):
        code = []

        bits = str(self.nbits(vartype))
        name = argname.name

        #Declare array
        dim = c_ast.Constant('int', str(size))
        typedecl = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[vartype]))
        array = c_ast.ArrayDecl(typedecl, dim, None)
        decl = c_ast.Decl(name, [], [], [], array, None, None)
        code.append(decl)


        #Create 'for' loop to fill array
        index = f'index_{name}'
        
        #For-init
        typedecl = c_ast.TypeDecl(index, [], c_ast.IdentifierType(names=['int']))
        decl = c_ast.Decl(name, [], [], [], typedecl, c_ast.Constant('int', str(0)), None)
        init  = c_ast.DeclList(decls=[decl])
        
        #For-condition
        cond = c_ast.BinaryOp(op='<', left=c_ast.ID(index), right=c_ast.Constant('int', str(size)))
        
        #For-next
        nxt = c_ast.UnaryOp(op='p++', expr=c_ast.ID(index))
        
        #For-statement
        lvalue = c_ast.ArrayRef(argname, subscript=c_ast.ID(index))
        exprlist = c_ast.ExprList( [c_ast.FuncCall(c_ast.ID('sizeof'), c_ast.ExprList([c_ast.ID(vartype)]))] )
        rvalue = c_ast.FuncCall(c_ast.ID('summ_new_sym_var'), exprlist)
        assignment = c_ast.Assignment(op='=', lvalue=lvalue, rvalue=rvalue)                                                                                  
        stmt = c_ast.Compound([assignment])

        
        for_ast_code = c_ast.For(init, cond, nxt, stmt)
        code.append(for_ast_code)

        self.code += code
        return



    #Create a primitive symbolic var  e.g, int a = summ_new_sym_var(sizeof(int))
    def create_symvar(self, argname, vartype):
        bits = str(self.nbits(vartype))
        name = argname.name

        #Create Rvalue
        exprlist = c_ast.ExprList( [c_ast.FuncCall(c_ast.ID('sizeof'), c_ast.ExprList([c_ast.ID(vartype)]))] )
        rvalue = c_ast.FuncCall(c_ast.ID('summ_new_sym_var'), exprlist)
        
        #Declare Variable
        typedecl = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[vartype]))
        decl = c_ast.Decl(name, [], [], [], typedecl, rvalue, None)
        
        self.code = [decl]
        return
            

    #Visitors
    def visit(self, node):
        return c_ast.NodeVisitor.visit(self, node)
    
    #Entry Node
    def visit_Decl(self, node):
        self.argname = c_ast.ID(name=node.name)
        self.visit(node.type)                                                                    
        return

    #Primitive Type
    def visit_TypeDecl(self, node):
        self.visit(node.type)
        self.create_symvar(self.argname, self.argtype)
        return  

    #Array Type
    def visit_ArrayDecl(self, node):
        self.visit(node.type.type)
        self.create_sym_array(self.argname, self.argtype, random.randint(2,10))
        return

    #Final Node
    def visit_IdentifierType(self, node):
        self.argtype = node.names[0]
        return



#Create a single test
def create_test(fname, args):

    #Function receives no args
    if args is None:
        return

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
        ast = vis.visit(arg)
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
    print(str_ast)

    return str_ast


#Create tests for all functions
def create_tests (f_decls):
    symb_args = list(map(lambda x : create_test(x, f_decls[x]), f_decls))
    return 



if __name__ == "__main__":

    ast = parse_file("example42.c", use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', '-Iloglib/fake_libc_include'])
    
    
    #Visitor to get all func defs
    vis = FunDeclVisitor()
    vis.visit(ast)
    fun_decls = vis.fun_dict;
    
    #Create tests
    create_tests(fun_decls)

