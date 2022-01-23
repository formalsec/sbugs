from PreProcessing.ScopeStack import ScopeStack

from pycparser.c_ast import *

def symbolic_rvalue(vartype):
		
	#Multiply sizeof by 8bits
	multiply = BinaryOp(op='*', left=FuncCall(ID('sizeof'),\
	ExprList([ID(vartype)])), right=Constant('int', str(8)))

	#Create Rvalue
	sizeof = ExprList([multiply])
	rvalue = FuncCall(ID('new_sym_var'), sizeof)

	return rvalue


def terminate_string(lvalue, size):
	arr_lvalue = ArrayRef(lvalue, subscript=Constant('int', str(int(size)-1)))
	assign = Assignment(op='=', lvalue=arr_lvalue, rvalue=Constant('char', '\'\\0\''))
	return assign   

def genArray(name, lvalue, vartype, size):
	code = []
	index = f'{name}_index'
	rvalue = symbolic_rvalue(vartype)
	arr_lvalue = ArrayRef(lvalue, subscript=ID(index))    

	stmt = Assignment(op='=', lvalue=arr_lvalue, rvalue=rvalue)  
	block = Compound([stmt])

	##For-init
	typedecl = TypeDecl(index, [], IdentifierType(names=['int']))
	decl = Decl(index, [], [], [], typedecl, Constant('int', str(0)), None)
	init  = DeclList(decls=[decl])
	
	##For-condition
	cond = BinaryOp(op='<', left=ID(index), right=Constant('int', str(size)))
	
	##For-next
	nxt = UnaryOp(op='p++', expr=ID(index))

	code.append(For(init, cond, nxt, block))

	if vartype == 'char':
		code.append(terminate_string(lvalue,size))

	return code       


class StructGenVisitor(NodeVisitor):
	def __init__(self, node, stack):

		self.node = node
		self.stack = stack
		
		self.var = None
		self.field = None

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_ID(self, node):
		self.var = node.name
		return

	def visit_ArrayRef(self, node):
		self.visit(node.name)
		return

	def visit_StructRef(self, node):
		self.field = node.field.name
		self.visit(node.name)
		return

	def gen(self):
		self.visit(self.node)
		struct = self.stack.findType(self.var)
		structType = struct.getType()

		if self.stack.isAlias(structType):
			structType = self.stack.getStruct(structType)

		structFieldType = self.stack.fieldType(structType, self.field)

		vartype = structFieldType.getType()
		arraysize = structFieldType.arraySize()

		code = []
		if arraysize:
			code += genArray(self.field, self.node, vartype, arraysize)

		else:
			rvalue = symbolic_rvalue(vartype)			
			code.append(Decl(self.field, [], [], [], self.node, rvalue, None))

		return code




class ArgGenVisitor(NodeVisitor):

	def __init__(self, stack):
		self.stack = stack


	def gen(self, name):
		argtype = self.stack.findType(name)
		
		vartype = argtype.getType()
		arraysize = argtype.arraySize()

		code = []
		if arraysize:
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
		struct_vis = StructGenVisitor(node, self.stack)
		code = struct_vis.gen()
		return code



class ArgTypeVisitor(NodeVisitor):

	def __init__(self, name, stack, struct):
		self.name = name
		self.stack = stack
		self.struct = struct
		self.dim = None

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
		vartype = node.names[0]
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

		if node.dim is not None:
			self.dim = node.dim.value

		#Store array dimension and visit type
		self.visit(node.type)
		return

	def visit_FuncDecl(self, node):
		return	



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