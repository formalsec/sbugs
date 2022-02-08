from pycparser.c_ast import *


class GlobalArgVisitor(NodeVisitor):

	def __init__(self, name, global_vars):
		self.name = name
		self.global_vars = global_vars
		self.dim = []

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_IdentifierType(self, node):
		
		#Store variable type and id
		vartype = node.names[0]
		
		if len(node.names) > 1:
			for t in node.names[1:]:
				vartype += f' {t}' 
		
		self.global_vars.addVar(self.name, vartype, array = self.dim)       
		return 


	def visit_TypeDecl(self, node):
		self.visit(node.type)
		return 


	def visit_PtrDecl(self, node):
		self.visit(node.type)
		return      


	def visit_ArrayDecl(self, node):
		if node.dim is not None:
			self.dim.append(node.dim.value)
		else:
			self.dim.append(None)

		#Store array dimension and visit type
		self.visit(node.type)
		return

	def visit_FuncDecl(self, node):
		return  
