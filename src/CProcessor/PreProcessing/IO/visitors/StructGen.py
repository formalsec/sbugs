from ..ScopeStack import ScopeStack
from pycparser.c_ast import *

from CProcessor.PreProcessing.utils import *



class StructGenVisitor(NodeVisitor):
	def __init__(self, node, stack, arraysize=None):
		self.arraysize = arraysize

		self.node = node
		self.stack = stack
		
		self.var = None
		self.fields = []

	def calc_size(self, size):
		if isinstance(size, Constant):
			size_int = int(size.value)
			if self.arraysize is not None:
				if self.arraysize > 0 and self.arraysize < size_int:
					return Constant('int', str(self.arraysize))
		return size

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
		self.fields.insert(0, node.field.name)
		self.visit(node.name)
		return


	def gen(self):
		self.visit(self.node)
		struct = self.stack.findType(self.var)
		structType = struct.getType()

		if self.stack.isAlias(structType):
			structType = self.stack.getStruct(structType)

		for field in self.fields:
			
			structFieldType = self.stack.fieldType(structType, field)
			vartype = structFieldType.getType()
			arraysize = structFieldType.arraySize()
			structType = vartype
			
			if self.stack.isAlias(structType):
				structType = self.stack.getStruct(structType)

		code = []
		if arraysize:
			size = arraysize[-1]
			size = self.calc_size(size)

			code += genArray(self.fields[-1], self.node, vartype, size)

		else:
			rvalue = symbolic_rvalue(vartype)			
			code.append(Decl(self.fields[-1], [], [], [], self.node, rvalue, None))

		return code
