from pycparser import c_parser, parse_file, c_generator
from pycparser.c_ast import *

def defineMacro(label, value):
	return f'#define {label} {value}'


def returnValue(val):
   return Return(ExprList([val]))


def mainFunction(calls):
	gen = c_generator.CGenerator()

	typedecl = TypeDecl(f'main', [], IdentifierType(names=['int']))
	funcdecl = FuncDecl(None, typedecl)
	decl = Decl(f'main', [], [], [], funcdecl, None, None)

	calls_ast = [c for c in map(lambda x : FuncCall(ID(x), ExprList([])), calls)]
	calls_ast.append(returnValue(Constant('int', str(0))))

	block = Compound(calls_ast)
	main = FuncDef(decl, None, block, None) 

	return gen.visit(main)
	

