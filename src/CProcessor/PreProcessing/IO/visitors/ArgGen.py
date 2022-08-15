from pycparser.c_ast import *

from . StructGen import StructGenVisitor 
from CProcessor.PreProcessing.utils import *

class ArgGenVisitor(NodeVisitor):

	def __init__(self, stack, arraylimit=None):
		self.stack = stack
		self.arraylimit = arraylimit
		self.arraynode = None
		self.dim = 0

	def calc_size(self, size):
		if isinstance(size, Constant):
			size_int = int(size.value)
			if self.arraylimit is not None:
				if self.arraylimit > 0 and self.arraylimit < size_int:
					return Constant('int', str(self.arraylimit))
		return size

	def gen(self, name):

		argtype = self.stack.findType(name)
		vartype = argtype.getType()
		arraysize = argtype.arraySize()

		code = []
		if arraysize:
			size = arraysize[-1]
			size = self.calc_size(size)
			dim = len(arraysize)

			if self.dim != dim:
				code += genArray(name, self.arraynode, vartype, size)
				return code
	
		lvalue = self.arraynode
		rvalue = symbolic_rvalue(vartype)
		code.append(Decl(name, [], [], [], lvalue, rvalue, None))			

		return code


	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_UnaryOp(self, node):
		return self.visit(node.expr)

	def visit_ArrayRef(self, node):
		self.dim += 1
		if not self.arraynode:
			self.arraynode = node
		return self.visit(node.name)

	def visit_ID(self, node):
		if not self.arraynode:
			self.arraynode = node
		name = node.name
		code = self.gen(name)
		return code

	def visit_StructRef(self, node):
		struct_vis = StructGenVisitor(node, self.stack, self.arraylimit)
		code = struct_vis.gen()
		return code