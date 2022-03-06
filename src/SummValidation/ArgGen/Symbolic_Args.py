from SummValidation.ArgGen.Visitors.FunctionArgs import ArgVisitor
from pycparser.c_ast import *

class Symbolic_Args():
    def __init__(self):
        pass

    def create_symbolic_args(self, args):

        block = []     #Test code to be generated
        call_args = []  #Arguments to call the function		

        #Function has no arguments
        if args is None:
            args = []
        
        #Visit arguments 
        for arg in args:

            vis = ArgVisitor()   
            vis.visit(arg)
            code = vis.gen_code()
            call_args.append(vis.argname)
            
            block += code

        return block, call_args

    def call_function(self, fname, call_args, ret_name, ret_type):
        
        lvalue = TypeDecl(ret_name, [], IdentifierType(names=[ret_type]))

        rvalue = FuncCall(ID(fname), ExprList([a for a in map(lambda x: ID(x), call_args)]))
        
        return Decl(ret_name, [], [], [], lvalue, rvalue, None)

    
    def get_types(self, args):
        
        #Function has no arguments
        if args is None:
            return []
        
        types_list = []
        for arg in args:

            vis = ArgVisitor()   
            vis.visit(arg)
            typ = vis.get_type()
            types_list.append(typ)

        return types_list

