from ..ScopeStack import ScopeStack
from pycparser.c_ast import *

from . ArgGen import ArgGenVisitor
from . ArgType import ArgTypeVisitor

from CProcessor.PreProcessing.utils import *


class PreProcessVisitor(NodeVisitor):

	def __init__ (self): 
		self.stack = ScopeStack()
		self.struct = None #If inside a struct store name

	
	def create_symvars(self, args):
		code = []		#Code to generate symbolic variables
		args = args[1:] #Remove format string

		genvisitor = ArgGenVisitor(self.stack)	
		for arg in args:
			code += genvisitor.visit(arg)
		return code
	

	#Safe visit wrapper
	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)


	#Generic visit
	def generic_visit(self, node):
		return node 

	
	#Entry node, generate a new ast by
	#visiting all stmts
	def visit_FileAST(self, node):
		decls = []
		for decl in node.ext:
			stmt = self.visit(decl)
			if type(stmt) is list:
				decls += stmt
			else:
				decls.append(stmt)

		ast = FileAST(decls)
		return ast


	#Visit Compound (Block)
	def visit_Compound(self, node):
		stms = []

		#Enter a block -> push new scope to stack
		self.stack.push()

		block = node.block_items
		if block is not None:
			for stmt in node.block_items:
				new_stmt = self.visit(stmt)
				if type(new_stmt) is list:
					stms += new_stmt
				else:
					stms.append(new_stmt)

		#Leave a block -> pop scope from stack
		self.stack.pop()
		return Compound(stms)



	#Visit variable declarations
	#This includes struct fields
	def visit_Decl(self, node):
		name = node.name
		argv = ArgTypeVisitor(name, self.stack, self.struct)
		argv.visit(node.type)
		return node


	#Function declarations
	#Visit to push arg types into scope
	def visit_FuncDecl(self, node):
		args = node.args
		if args is not None:
			for decl in args.params:
				self.visit(decl)
		return node


	#Visit function definitions
	def visit_FuncDef(self, node):
		self.stack.push()
		self.visit(node.decl.type) #--> visit_FuncDecl
		new_body = self.visit(node.body) #--> visit_Compound
		self.stack.pop()
		return FuncDef(node.decl, node.param_decls, new_body)


	#Visit function calls
	#Create symvars for 'scanf' call
	def visit_FuncCall(self, node):
		if node.name.name == 'scanf':
			return self.create_symvars(node.args.exprs)
		return node


	#Visit Typedef (store aliases)
	def visit_Typedef(self, node):
		obj = node.type.type
		if isinstance(obj,Struct):
			self.stack.addAlias(node.name, obj.name)
			self.visit(obj)
		return node


	#Visit Struct
	#Store new struct and visit its fields
	def visit_Struct(self, node):
		self.struct = node.name
		
		if node.decls is not None:
			self.stack.addStruct(node.name)
			for decl in node.decls:
				self.visit(decl)

		self.struct = None
		return node
	

	def visit_If(self, node):
		iftrue = self.visit(node.iftrue)
		iffalse = self.visit(node.iffalse)
		return If(node.cond, iftrue, iffalse)
	

	def visit_While(self, node):
		new_stmt = self.visit(node.stmt)
		return While(node.cond, new_stmt)

	def visit_For(self, node):

		self.stack.push()
		new_init = self.visit(node.init)
		new_stmt = self.visit(node.stmt)
		self.stack.pop()
		
		return For(new_init, node.cond, node.next, new_stmt)