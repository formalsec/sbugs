from pycparser.c_ast import *

from SummValidation.APIGen.APIGen import API_Gen
from SummValidation.ArgGen.Symbolic_Args import Symbolic_Args
from SummValidation.Utils.utils import returnValue

class TestGen:
    def __init__(self, args, ret, cncrt_name, summ_name, memory):   
        self.args = args
        self.ret = ret
        self.memory = memory
        self.cncrt_name = cncrt_name
        self.summ_name = summ_name
    
    def createTest(self, name, size_macro):

        #Helper objects
        sym_args_gen = Symbolic_Args(self.args, size_macro)
        api_gen = API_Gen()

        #Create symbolic args
        args_code = sym_args_gen.create_symbolic_args()
        
        #Get ordered arg names
        args_names = sym_args_gen.get_all_args()

        #Body contains the test code
        body = [
            *args_code,
            api_gen.save_current_state('initial_state'),
        ]

        if self.memory:
            ptr_names = sym_args_gen.get_ptr_args()
            for ptr in ptr_names:
                body.append(api_gen.summ_mem_addr(ptr, size_macro))

        body +=[
            sym_args_gen.call_function(self.cncrt_name, args_names, 'ret1', self.ret),
            api_gen.get_cnstr('cnstr1', 'ret1', self.ret),
            api_gen.add_expr('cnctr', 'cnstr1'),
            
            api_gen.halt_all('initial_state'),

            sym_args_gen.call_function(self.summ_name, args_names, 'ret2', self.ret),			
            api_gen.get_cnstr('cnstr2', 'ret2', self.ret),
            api_gen.add_expr('summ', 'cnstr2'),

            api_gen.check_implications('result', 'cnctr', 'summ'),
            api_gen.print_counterexamples('result'),

            #Return
            returnValue(Constant('int', str(0)))
        ]

        #Create main function ast
        block = Compound(body)

        typedecl = TypeDecl(name, [], IdentifierType(names=[self.ret]))
        funcdecl = FuncDecl(None, typedecl)
        decl = Decl(name, [], [], [], funcdecl, None, None)
        
        
        return FuncDef(decl, None, block, None)
