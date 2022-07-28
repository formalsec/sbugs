from pycparser.c_ast import *

from . StructGen import StructGenVisitor 
from CProcessor.PreProcessing.utils import *

class ArgGenVisitor(NodeVisitor):

	def __init__(self, stack, arraysize=None):
		self.stack = stack
		self.arraysize = arraysize

	def calc_size(self, size):
		if isinstance(size, Constant):
			size_int = int(size.value)
			if self.arraysize is not None:
				if self.arraysize > 0 and self.arraysize < size_int:
					return Constant('int', str(self.arraysize))
		return size

	def gen(self, name):
		argtype = self.stack.findType(name)
		
		vartype = argtype.getType()
		arraysize = argtype.arraySize()

		code = []
		if arraysize:
			arraysize = self.calc_size(arraysize)
			code += genArray(name, ID(name), vartype, arraysize)

		else:
			lvalue = ID(name)
			rvalue = symbolic_rvalue(vartype)
			code.append(Decl(name, [], [], [], lvalue, rvalue, None))			

		return code


	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_UnaryOp(self, node):
		return self.visit(node.expr)

	def visit_ID(self, node):
		name = node.name
		code = self.gen(name)
		return code

	def visit_StructRef(self, node):
		struct_vis = StructGenVisitor(node, self.stack, self.arraysize)
		code = struct_vis.gen()
		return code