from pycparser.c_ast import *
from .IO.ScopeStack import ScopeStack


def symbolic_rvalue(vartype):
		
	#Multiply sizeof by 8bits
	multiply = BinaryOp(op='*', left=FuncCall(ID('sizeof'),\
	ExprList([ID(vartype)])), right=Constant('int', str(8)))

	#Create Rvalue
	sizeof = ExprList([multiply])
	rvalue = FuncCall(ID('new_sym_var'), sizeof)

	return rvalue


def terminate_string(lvalue, size):
	arr_lvalue = ArrayRef(lvalue, subscript=BinaryOp(op='-', left=size, right=Constant('int', '1')))
	assign = Assignment(op='=', lvalue=arr_lvalue, rvalue=Constant('char', '\'\\0\''))
	return assign   

def genArray(name, lvalue, vartype, size):
	code = []
	index = f'{name}_index'
	rvalue = symbolic_rvalue(vartype)
	arr_lvalue = ArrayRef(lvalue, subscript=ID(index))    

	stmt = Assignment(op='=', lvalue=arr_lvalue, rvalue=rvalue)  
	block = Compound([stmt])

	##For-init
	typedecl = TypeDecl(index, [], IdentifierType(names=['int']))
	decl = Decl(index, [], [], [], typedecl, Constant('int', str(0)), None)
	init  = DeclList(decls=[decl])
	
	##For-condition
	cond = BinaryOp(op='<', left=ID(index), right=size)
	
	##For-next
	nxt = UnaryOp(op='p++', expr=ID(index))

	code.append(For(init, cond, nxt, block))

	if vartype == 'char':
		code.append(terminate_string(lvalue,size))

	return code       

