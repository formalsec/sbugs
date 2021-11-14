from pycparser import c_parser, c_ast, parse_file, c_generator
import random

# Create a primitive symbolic var
# e.g, int a = summ_new_sym_var(sizeof(int))    
class PrimitiveTypeGen(c_ast.NodeVisitor):
    def __init__ (self, name, vartype):

        if isinstance(name, str):
            name = c_ast.ID(name=name)

        self.argname = name 
        self.vartype = vartype

     

    def gen(self):
        
        name = self.argname.name
        vartype = self.vartype

        #Multiply sizeof by 8bits
        multiply = c_ast.BinaryOp(op='*', left=c_ast.FuncCall(c_ast.ID('sizeof'),\
        c_ast.ExprList([c_ast.ID(vartype)])), right=c_ast.Constant('int', str(8)))
        
        #Create Rvalue
        sizeof = c_ast.ExprList([multiply])
        rvalue = c_ast.FuncCall(c_ast.ID('summ_new_sym_var'), sizeof)
        
        #Declare Variable
        lvalue = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[vartype]))
        decl = c_ast.Decl(name, [], [], [], lvalue, rvalue, None)
                
        return decl




#Create a symbolic N-dimension array
# (uses a 'For' loop to fill array)
class ArrayTypeGen(c_ast.NodeVisitor):
    def __init__ (self, name, vartype):
        
        if isinstance(name, str):
            name = c_ast.ID(name=name)

        self.argname = name 
        self.vartype = vartype
        self.size = random.randint(2,10)



    def gen(self):
        
        code = []
        name = self.argname.name
        vartype = self.vartype
        size = self.size

        #Declare array
        dim = c_ast.Constant('int', str(size))
        typedecl = c_ast.TypeDecl(name, [], c_ast.IdentifierType(names=[vartype]))
        array = c_ast.ArrayDecl(typedecl, dim, None)
        decl = c_ast.Decl(name, [], [], [], array, None, None)
        code.append(decl)


        #Create 'for' loop to fill array
        index = f'index_{name}'
        
        ##For-init
        typedecl = c_ast.TypeDecl(index, [], c_ast.IdentifierType(names=['int']))
        decl = c_ast.Decl(name, [], [], [], typedecl, c_ast.Constant('int', str(0)), None)
        init  = c_ast.DeclList(decls=[decl])
        
        ##For-condition
        cond = c_ast.BinaryOp(op='<', left=c_ast.ID(index), right=c_ast.Constant('int', str(size)))
        
        ##For-next
        nxt = c_ast.UnaryOp(op='p++', expr=c_ast.ID(index))
        
        ##For-statement
        #Declare array
        lvalue = c_ast.ArrayRef(self.argname, subscript=c_ast.ID(index))
        
        #multiply sizeof by 8bits
        multiply = c_ast.BinaryOp(op='*', left=c_ast.FuncCall(c_ast.ID('sizeof'), c_ast.ExprList([c_ast.ID(vartype)])),\
        right=c_ast.Constant('int', str(8)))
        sizeof = c_ast.ExprList([multiply])
        
        #summ_new_sym_var(sizeof(<type> * 8))
        rvalue = c_ast.FuncCall(c_ast.ID('summ_new_sym_var'), sizeof)
        assignment = c_ast.Assignment(op='=', lvalue=lvalue, rvalue=rvalue)                                                                                  
        
        stmt = c_ast.Compound([assignment])

        ##Create the For node
        for_ast_code = c_ast.For(init, cond, nxt, stmt)
        
        code.append(for_ast_code)
        return code