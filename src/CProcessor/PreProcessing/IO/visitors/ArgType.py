from pycparser.c_ast import *


class ArgTypeVisitor(NodeVisitor):

	def __init__(self, name, stack, struct):
		self.name = name
		self.stack = stack
		self.struct = struct
		self.dim = []

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_Struct(self, node):
		
		#Store variable type and id
		vartype = node.name
		if self.struct:
			self.stack.addField(self.struct, self.name, vartype, array = self.dim)
		else:
			self.stack.addVar(self.name, vartype, array = self.dim)		
		return 

	
	def visit_IdentifierType(self, node):
		
		#Store variable type and id
		vartype = ''
		for token in node.names:
			vartype += f'{token} '
		vartype = vartype.strip()
		
		if self.struct:
			self.stack.addField(self.struct, self.name, vartype, array = self.dim)
		else:
			self.stack.addVar(self.name, vartype, array = self.dim)		
		return 


	def visit_TypeDecl(self, node):
		self.visit(node.type)
		return 


	def visit_PtrDecl(self, node):
		self.visit(node.type)
		return 		


	def visit_ArrayDecl(self, node):
		
		self.dim.append(node.dim)
		#Store array dimension and visit type
		self.visit(node.type)
		return

	def visit_FuncDecl(self, node):
		return	
