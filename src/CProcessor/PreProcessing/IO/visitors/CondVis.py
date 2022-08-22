from pycparser.c_ast import *

class CondVisitor(NodeVisitor):

	def __init__ (self): 
		self.scanfs = ['scanf', 'sscanf', 'fscanf']
		self.eof = 'EOF'


	#Safe visit wrapper
	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)


	#Generic visit
	def generic_visit(self, node):
		return node 


	def visit_FuncCall(self, node):
		if type(node.name) is ID:
			fname = node.name.name
			if fname in self.scanfs:
				return True
		return False

	def visit_Constant(self, node):
		return int(node.value)

	def visit_ID(self, node):
		return node.name

	def visit_BinaryOp(self, node):
		op = node.op
		zero = False
		eof = False
		
		if isinstance(node.left, Constant):
			if self.visit(node.left) == 0:
				zero = True

		if isinstance(node.right, Constant):
			if self.visit(node.right) == 0:
				zero = True

		if isinstance(node.right, ID):
			if self.visit(node.right) == self.eof:
				eof = True

		if isinstance(node.left, ID):
			if self.visit(node.left) == self.eof:
				eof = True

		if zero or eof and op == '==':
			return False

		elif zero or eof and op == '!=':
			return True

		elif not (zero or eof) and op == '==':
			return True

		elif not (zero or eof) and op == '!=':
			return False
