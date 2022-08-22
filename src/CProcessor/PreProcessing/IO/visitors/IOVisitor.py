from ..ScopeStack import ScopeStack
from pycparser.c_ast import *

from . ArgGen import ArgGenVisitor
from . ArgType import ArgTypeVisitor
from . TypeDef import TypeDefVisitor
from . CondVis import CondVisitor

from CProcessor.PreProcessing.utils import *


class IO_Visitor(NodeVisitor):

	def __init__ (self, arraylimit=None): 
		self.arraylimit = arraylimit
		self.stack = ScopeStack()
		self.struct = None #If inside a struct store name

		self.lastAlias = None	

		self.fundef = False #Used to ignore function headers with no definition
		
		self.scanfs = ['scanf', 'sscanf', 'fscanf']
		self.scanf_ret = False #Scanfs in decls, if/whiles int n = scanf(...)

		self.scanf_extra = None #Extra scanf code for ifs, whiles, ...

	def create_symvars(self, fname, args):
		code = []		#Code to generate symbolic variables
		
		if fname == 'scanf':
			args = args[1:] #Remove format string

		elif fname == 'sscanf':
			args = args[2:] #Remove format string and buffer

		elif fname == 'fscanf':
			args = args[2:] #Remove format string and buffer

		for arg in args:
			genvisitor = ArgGenVisitor(self.stack, self.arraylimit)
			code += genvisitor.visit(arg)

				
		if self.scanf_ret:
			nargs = len(args)
			nargs_node = Constant('int', str(nargs))
			self.scanf_extra = code
			return nargs_node

	
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
	#Includes struct fields
	#This can also be a struct definition
	def visit_Decl(self, node):
		name = node.name
		init = node.init
		if name is not None:
			argv = ArgTypeVisitor(name, self.stack, self.struct)
			argv.visit(node.type)	
		
		self.visit(node.type)

		if init is not None:
			self.scanf_ret = True
			new_node = self.visit(init)
			self.scanf_ret = False

			if self.scanf_extra:
				extra_code = self.scanf_extra
				self.scanf_extra = None
				node.init = new_node
				return [node, *extra_code]		
		
		return node


	def visit_Assignment(self, node):
		self.scanf_ret = True
		new_assign = self.visit(node.rvalue)
		self.scanf_ret = False
		
		if self.scanf_extra:
			extra_code = self.scanf_extra
			self.scanf_extra = None
			node.rvalue = new_assign
			return [node, *extra_code]		

		return node

	def visit_TypeDecl(self, node):
		self.visit(node.type)
		return node

	def visit_ArrayDecl(self, node):
		self.visit(node.type)
		return node

	def visit_PtrDecl(self, node):
		self.visit(node.type)
		return node

	#Function declarations
	#Visit to push arg types into scope
	def visit_FuncDecl(self, node):
		if self.fundef:
			args = node.args
			if args is not None:
				for decl in args.params:
					self.visit(decl)
		return node


	#Visit function definitions
	def visit_FuncDef(self, node):
		self.fundef = True
		self.stack.push()
		self.visit(node.decl.type) #--> visit_FuncDecl
		new_body = self.visit(node.body) #--> visit_Compound
		self.stack.pop()
		self.fundef = False
		return FuncDef(node.decl, node.param_decls, new_body)


	#Visit function calls
	#Create symvars for 'scanf' call
	def visit_FuncCall(self, node):
		if type(node.name) is ID:
			fname = node.name.name
		else:
			return node
		
		if fname in self.scanfs:
			return self.create_symvars(fname, node.args.exprs)
		return node


	#Visit Typedef (store aliases)
	def visit_Typedef(self, node):

		vis = TypeDefVisitor()
		struct = vis.visit(node)

		if struct:
			name = struct.name
			if name is None:
				name = node.name

			self.lastAlias = node.name
			self.stack.addAlias(node.name, name)
			
			self.visit(struct)
		return node


	#Visit Struct
	#Store new struct and visit its fields
	def visit_Struct(self, node):
		if self.struct:
			return node

		if node.name is None:
			self.struct = self.lastAlias
		else:
			self.struct = node.name
		
		if node.decls is not None:
			self.stack.addStruct(self.struct)
			for decl in node.decls:
				self.visit(decl)

		self.struct = None
		return node
	

	def visit_If(self, node):
		iftrue = self.visit(node.iftrue)
		iffalse = self.visit(node.iffalse)
		
		if isinstance(iftrue, list):
			iftrue = Compound(iftrue)
		else:
			iftrue = Compound([iftrue])

		if isinstance(iffalse, list): 
			iffalse = Compound(iffalse)
		else:
			iffalse = Compound([iffalse])

		self.scanf_ret = True
		new_cond = self.visit(node.cond)
		self.scanf_ret = False
		
		if self.scanf_extra:

			extra_code = self.scanf_extra
			self.scanf_extra = None
			
			v = CondVisitor()
			in_if = v.visit(node.cond)
			node.cond = new_cond
			
			if in_if:
				block = iftrue.block_items
				iftrue.block_items = extra_code + block	
			else:
				block = iffalse.block_items
				iffalse.block_items = extra_code + block	

		return If(node.cond, iftrue, iffalse)
	

	def visit_While(self, node):
		new_stmt = self.visit(node.stmt)

		self.scanf_ret = True
		new_cond = self.visit(node.cond)
		self.scanf_ret = False

		if self.scanf_extra:
			extra_code = self.scanf_extra
			self.scanf_extra = None
			node.cond = new_cond

			if type(new_stmt) is Compound:
				block = new_stmt.block_items
				new_stmt.block_items = extra_code + block
			else:
				new_stmt = Compound([*extra_code, new_stmt])


		return While(node.cond, new_stmt)

	
	def visit_DoWhile(self, node):
		new_stmt = self.visit(node.stmt)

		self.scanf_ret = True
		new_cond = self.visit(node.cond)
		self.scanf_ret = False

		if self.scanf_extra:
			extra_code = self.scanf_extra
			self.scanf_extra = None
			node.cond = new_cond

			if type(new_stmt) is Compound:
				block = new_stmt.block_items
				new_stmt.block_items = extra_code + block
			else:
				new_stmt = Compound([*extra_code, new_stmt])

		return DoWhile(node.cond, new_stmt)

	def visit_For(self, node):
		self.stack.push()
		new_init = self.visit(node.init)
		new_stmt = self.visit(node.stmt)

		if isinstance(new_stmt, list):
			new_stmt = Compound(new_stmt)

		self.stack.pop()
		
		return For(new_init, node.cond, node.next, new_stmt)


	def visit_Switch(self, node):
		new_stmt = self.visit(node.stmt)
		return Switch(node.cond, new_stmt)

	def visit_Case(self, node):
		new_stmts = []
		if node.stmts is not None:
			for stmt in node.stmts:
				new_stmt = self.visit(stmt)
				if type(new_stmt) is list:
					new_stmts += new_stmt
				else:
					new_stmts.append(new_stmt)
		
		return Case(node.expr, new_stmts)


	def visit_BinaryOp(self, node):
		new_left = self.visit(node.left)
		new_right = self.visit(node.right)
		return BinaryOp(node.op, new_left, new_right)


	def visit_TernaryOp(self, node):
		new_iftrue = self.visit(node.iftrue)
		new_iffalse = self.visit(node.iffalse)
		return TernaryOp(node.cond, new_iftrue, new_iffalse)

  