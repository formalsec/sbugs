from PreProcessing.ScopeStack import ScopeStack
from pycparser.c_ast import *

from PreProcessing.utils import *



class StructGenVisitor(NodeVisitor):
	def __init__(self, node, stack):

		self.node = node
		self.stack = stack
		
		self.var = None
		self.field = None

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_ID(self, node):
		self.var = node.name
		return

	def visit_ArrayRef(self, node):
		self.visit(node.name)
		return

	def visit_StructRef(self, node):
		self.field = node.field.name
		self.visit(node.name)
		return

	def gen(self):
		self.visit(self.node)
		struct = self.stack.findType(self.var)
		structType = struct.getType()

		if self.stack.isAlias(structType):
			structType = self.stack.getStruct(structType)

		structFieldType = self.stack.fieldType(structType, self.field)

		vartype = structFieldType.getType()
		arraysize = structFieldType.arraySize()

		code = []
		if arraysize:
			code += genArray(self.field, self.node, vartype, arraysize)

		else:
			rvalue = symbolic_rvalue(vartype)			
			code.append(Decl(self.field, [], [], [], self.node, rvalue, None))

		return code
