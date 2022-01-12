#!/usr/bin/env python3

import argparse
import sys, os
import re

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from ScopeStack import ScopeStack
from pycparser import c_parser, parse_file, c_generator
from pycparser.c_ast import *


def symbolic_rvalue(vartype):
		
	#Multiply sizeof by 8bits
	multiply = BinaryOp(op='*', left=FuncCall(ID('sizeof'),\
	ExprList([ID(vartype)])), right=Constant('int', str(8)))

	#Create Rvalue
	sizeof = ExprList([multiply])
	rvalue = FuncCall(ID('new_sym_var'), sizeof)

	return rvalue


def genArray(name, vartype, size):
	
	index = f'{name}_index'
	lvalue = ArrayRef(ID(name), subscript=ID(index))
	rvalue = symbolic_rvalue(vartype)

	stmt = Assignment(op='=', lvalue=lvalue, rvalue=rvalue)  
	block = Compound([stmt])

	##For-init
	typedecl = TypeDecl(index, [], IdentifierType(names=['int']))
	decl = Decl(index, [], [], [], typedecl, Constant('int', str(0)), None)
	init  = DeclList(decls=[decl])
	
	##For-condition
	cond = BinaryOp(op='<', left=ID(index), right=Constant('int', str(size)))
	
	##For-next
	nxt = UnaryOp(op='p++', expr=ID(index))
	return For(init, cond, nxt, block)      






class ArgTypeVisitor(NodeVisitor):

	def __init__(self, name, stack):
		self.name = name
		self.stack = stack

	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_TypeDecl(self, node):
		
		#Store variable type and id
		vartype = node.type.names[0]
		self.stack.addVar(self.name, vartype)		
		return 

	def visit_ArrayDecl(self, node):

		#Store variable type and id (and array = True)
		vartype = node.type.type.names[0]
		self.stack.addVar(self.name, vartype, array = node.dim.value)
		return	



class ArgGenVisitor(NodeVisitor):

	def __init__(self, stack):
		self.stack = stack


	def gen(self, name):
		argtype = self.stack.findType(name)
		
		vartype = argtype.getType()
		arraysize = argtype.arraySize()

		if arraysize:
			code = genArray(name, vartype, arraysize)

		else:
			lvalue = TypeDecl(name, [], IdentifierType(names=[vartype]))
			rvalue = symbolic_rvalue(vartype)			
			code = Decl(name, [], [], [], lvalue, rvalue, None)

		return code


	def visit(self, node): 
		if node is not None: 
			return NodeVisitor.visit(self, node)

	def visit_UnaryOp(self, node):
		name = node.expr.name
		code = self.gen(name)
		return code

	def visit_ID(self, node):
		name = node.name
		code = self.gen(name)
		return code


class PreProcessVisitor(NodeVisitor):

	def __init__ (self): 
		self.stack = ScopeStack()


	def create_symvars(self, args):
		code = []		#Code to generate symbolic variables
		args = args[1:] #Remove format string

		genvisitor = ArgGenVisitor(self.stack)	
		for arg in args:
			code.append(genvisitor.visit(arg))
		return code
	
	
	def visit(self, node):
		if node is not None: 
			return NodeVisitor.visit(self, node)


	#Generic visit
	def generic_visit(self, node):
		return node 


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
	def visit_Decl(self, node):

		name = node.name
		argv = ArgTypeVisitor(name, self.stack)
		argv.visit(node.type)
		return node


	#Visit function definitions
	def visit_FuncDef(self, node):
		new_body = self.visit(node.body)
		return FuncDef(node.decl, node.param_decls, new_body)



	#Visit function calls
	def visit_FuncCall(self, node):
		if node.name.name == 'scanf':
			return self.create_symvars(node.args.exprs)
		return node


def get_cmd_args():
	parser = argparse.ArgumentParser(description='Generate Symbolic Tests')

	parser.add_argument('-o', metavar='name', type=str, required=False, default='out.c',
						help='Output name')
	parser.add_argument('targetFile', metavar='file', type=str,
						help='The name of the target C file')
	return parser.parse_args()



if __name__ == "__main__":

	#Command line arguments
	args = get_cmd_args()
	inputFile = args.targetFile
	outFile = args.o


	ast = parse_file(args.targetFile, use_cpp=True,
		cpp_path='gcc',
		cpp_args=['-E', '-Iloglib/fake_libc_include'])

	vis = PreProcessVisitor()
	new_ast = vis.visit(ast)

	#print(new_ast)

	#Generate string from ast
	gen = c_generator.CGenerator()

	str_ast = gen.visit(new_ast)

	#Write to actual file
	file = open(outFile, "w")
	file.write(str_ast)
