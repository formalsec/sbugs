from pycparser.c_ast import *

from CProcessor.PreProcessing.utils import *

class ArgGenVisitor(NodeVisitor):

	def __init__(self, stack, arraylimit=None):
		self.stack = stack
		self.arraylimit = arraylimit
		self.node = None
		self.fields = []
		self.dim = 0

		self.count_dim = True

	def calc_size(self, size):
		limit = Constant('int', str(self.arraylimit))
		
		if not size:
			return limit
		
		if isinstance(size, Constant):
			size_int = int(size.value)
			if self.arraylimit is not None:
				if self.arraylimit > 0 and self.arraylimit < size_int:
					return limit
		return size

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_UnaryOp(self, node):
		return self.visit(node.expr)

	def visit_ArrayRef(self, node):
		if self.count_dim:
			self.dim += 1

		if isinstance(node.name, StructRef):
			self.count_dim = False

		if not self.node:
			self.node = node
		return self.visit(node.name)

	def visit_StructRef(self, node):
		self.count_dim = False
		if not self.node:
			self.node = node		
		self.fields.insert(0, node.field.name)
		return self.visit(node.name)
		

	def visit_ID(self, node):
		if not self.node:
			self.node = node
		name = node.name
		code = self.gen(name)
		return code

	def gen(self, name):

		argtype = self.stack.findType(name)
		vartype = argtype.getType()
		arraysize = argtype.arraySize()

		if self.stack.isAlias(vartype):
			vartype = self.stack.getStruct(vartype)

		for field in self.fields:
			
			structFieldType = self.stack.fieldType(vartype, field)
			vartype = structFieldType.getType()
			arraysize = structFieldType.arraySize()
			
			if self.stack.isAlias(vartype):
				vartype = self.stack.getStruct(vartype)


		code = []
		if arraysize:
			size = arraysize[-1]
			size = self.calc_size(size)
			dim = len(arraysize)

			diff = abs(self.dim - dim)

			if diff >= 2 or diff == 1 and vartype == 'char':
				code += genArray(name, self.node, vartype, size)
				return code
	
		lvalue = self.node
		rvalue = symbolic_rvalue(vartype)
		code.append(Decl(name, [], [], [], lvalue, rvalue, None))			
		return code
