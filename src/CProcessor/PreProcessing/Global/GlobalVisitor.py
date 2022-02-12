from pycparser.c_ast import *

from . visitors.GlobalArgType import GlobalArgVisitor
from . GlobalArgs import GlobalArgs
from CProcessor.PreProcessing.utils import *
from CProcessor import config


class Global_Visitor(NodeVisitor):

	def __init__ (self):

		config.global_vars = GlobalArgs() #Also store in the config
		self.global_vars = config.global_vars
		
		self.current_fvars = None 	#Vars used in function
		self.current_fdecls = None 	#Vars declared in function	

		self.fcalls = {} #Store used global vars for each function


	def create_function_arg(self, name, vartype):

		type_name = vartype.getType()
		array_dim = vartype.arraySize()

		identifiertype = IdentifierType([type_name])
		typedecl = TypeDecl(name, [], identifiertype)

		#Simple Type
		if len(array_dim) == 0:
			return Decl(name, [], [], [], typedecl, None, None)

		#N-dimension array
		else:
			arraydecl = ArrayDecl(typedecl, Constant('int', array_dim[-1]), [])
			for i in range(len(array_dim)-2, -1, -1):
				arraydecl = ArrayDecl(arraydecl, Constant('int', array_dim[i]), [])

			return 	Decl(name, [], [], [], arraydecl, None, None)
		


	def store_global_var(self, decl):
		name = decl.name
		visitor = GlobalArgVisitor(name, self.global_vars)
		visitor.visit(decl.type)



	#Add the needed global variables to the function header
	def add_global_vars_def(self, decl):
		global_vars_names = list(self.global_vars.var_names())

		#Find all undeclared variables
		undeclared = list(set(self.current_fvars) - set(self.current_fdecls))
		
		#Filter undeclared variables with global variables
		used_globals = [var for var in undeclared if var in global_vars_names] 
		used_globals.sort()

		extra_args = []
		for g in used_globals:
			vartype = self.global_vars.findType(g)
			arg_decl = self.create_function_arg(g, vartype)
			extra_args.append(arg_decl)

		if decl.type.args is not None:
			decl.type.args.params += extra_args

		else:
			decl.type.args = ParamList(extra_args)

		return used_globals

	

	def add_global_vars_call(self, name, node):
		if name not in self.fcalls.keys():
			return

		global_args = self.fcalls[name]
		global_args.sort()

		if len(global_args) == 0:
			return 

		extra_args = [ID(arg) for arg in global_args]

		if node.args is not None:
			node.args.exprs += extra_args
		
		else:
			node.args = ExprList(extra_args)

		return




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

			#Global Variable
			if isinstance(decl, Decl):
				self.store_global_var(decl)

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

		block = node.block_items
		if block is not None:
			for stmt in node.block_items:
				new_stmt = self.visit(stmt)
				if type(new_stmt) is list:
					stms += new_stmt
				else:
					stms.append(new_stmt)

		return Compound(stms)



	def visit_Decl(self, node):
		name = node.name
		if self.current_fdecls is not None:
			self.current_fdecls.append(name)

		self.visit(node.init)
		return node


	def visit_FuncDecl(self, node):
		args = node.args
		if args is not None:
			for decl in args.params:
				self.visit(decl)
		return node


	#Visit function definitions
	def visit_FuncDef(self, node):
		self.current_fvars = []
		self.current_fdecls = []
		
		self.visit(node.decl.type) #--> visit_FuncDecl
		new_body = self.visit(node.body) #--> visit_Compound

		fname = node.decl.name
		
		#Ignore main
		if fname != 'main':
			globals_vars = self.add_global_vars_def(node.decl)
			self.fcalls[fname] = globals_vars

		self.current_fvars = None
		self.current_fdecls = None
		
		return FuncDef(node.decl, node.param_decls, new_body)


	def visit_FuncCall(self, node):
		self.add_global_vars_call(node.name.name, node)

		self.visit(node.args)
		return node


	def visit_ExprList(self, node):
		for expr in node.exprs:
			self.visit(expr)
		return node


	def visit_UnaryOp(self, node):
		self.visit(node.expr)
		return node

	def visit_BinaryOp(self, node):
		self.visit(node.left)
		self.visit(node.right)
		return node


	def visit_StructRef(self, node):
		self.visit(node.name)


	def visit_ArrayRef(self, node):
		self.visit(node.name)
		self.visit(node.subscript)


	def visit_Assignment(self, node):
		self.visit(node.lvalue)
		self.visit(node.rvalue)
		return node


	def visit_ID(self, node):
		name = node.name
		if self.current_fvars is not None:
			self.current_fvars.append(name)
		return node


	def visit_If(self, node):
		self.visit(node.cond)
		self.visit(node.iftrue)
		self.visit(node.iffalse)
		return node
	

	def visit_While(self, node):
		self.visit(node.cond)
		self.visit(node.stmt)
		return node

	def visit_For(self, node):
		self.visit(node.init)
		self.visit(node.cond)
		self.visit(node.next)
		self.visit(node.stmt)
		return node

	def visit_Switch(self, node):
		self.visit(node.cond)
		self.visit(node.stmt)

	def visit_Case(self ,node):
		self.visit(node.expr)
		if node.stmts is not None:
			for stmt in node.stmts:
				self.visit(stmt)
