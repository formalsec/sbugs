from pycparser.c_ast import *

class TypeDefVisitor(NodeVisitor):
	def __init__ (self):
		self.struct = False

	#Safe visit wrapper
	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)

	#Generic visit
	def generic_visit(self, node):
		return None 

	def visit_PtrDecl(self, node):
		return self.visit(node.type)

	def visit_TypeDecl(self, node):
		return self.visit(node.type)

	def visit_Struct(self, node):
		self.struct = True
		return node

	def visit_IdentifierType(self, node):
		names = node.names
		name = ' '.join(names)
		return name

	def visit_Typedef(self, node):
		name = self.visit(node.type)
		if self.struct:
			return (True, name)
		return (False, name)