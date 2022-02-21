from pycparser import c_parser, parse_file, c_generator
from pycparser.c_ast import *

FUEL_MACRO = 'FUEL'
ARRAY_SIZE_MACRO = 'ARRAY_SIZE'
POINTER_SIZE_MACRO = 'POINTER_SIZE'


#Stubs
new_sym_var_DECL = 'void *new_sym_var(unsigned int length){return 0;}\n'
stubs = [new_sym_var_DECL]



class TypeDefVisitor(NodeVisitor):
	def __init__ (self): 
		self.ptr = False

	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_PtrDecl(self, node):
		self.ptr = True
		return self.visit(node.type)

	def visit_TypeDecl(self, node):
		return self.visit(node.type)

	def visit_Struct(self, node):
		return (node.name, self.ptr)

	def visit_IdentifierType(self, node):
		return (node.names[0], self.ptr)	



#Visit the ASt to separate each elemenet of interest
#function definitions; defined structs; and Typedefs 
class InitialVisitor(NodeVisitor):

	def __init__ (self, ast):

		self.ast = ast

		self._functions = {}
		self._function_args = {}

	def function_defs(self):
		if not self._functions:
			self.visit(self.ast)

		return list(self._functions.values())

	
	def function_names(self):
		if not self._functions:
			self.visit(self.ast)
		
		return list(self._functions.keys())
	

	def function_args(self):
		if not self._function_args:
			self.visit(self.ast)
		
		return list(self._function_args.values())


	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_FuncDef(self, node):
		self._functions[node.decl.name] = node
		self._function_args[node.decl.name] = node.decl.type.args.params\
		if node.decl.type.args else None




def defineMacro(label, value):
	return f'#define {label} {value}\n'

def defineInclude(name):
	return f'#include <{name}>\n'


def returnValue(val, operator=None):
	if operator:
		val = UnaryOp(operator, val)
	expr = ExprList([val])
	return Return(expr)


def createFunction(name, args, returnType):
	typedecl = TypeDecl(name, [], IdentifierType(names=[returnType]))
	funcdecl = FuncDecl(args, typedecl)
	decl = Decl(name, [], [], [], funcdecl, None, None)
	return decl


def mainFunction(calls):
	calls_ast = [c for c in map(lambda x : FuncCall(ID(x), ExprList([])), calls)]
	calls_ast.append(returnValue(Constant('int', str(0))))
	block = Compound(calls_ast)
	return block


def terminate_string(lvalue, size):
	arr_lvalue = ArrayRef(lvalue, subscript=size)
	assign = Assignment(op='=', lvalue=arr_lvalue, rvalue=Constant('char', '\'\\0\''))
	return assign   

