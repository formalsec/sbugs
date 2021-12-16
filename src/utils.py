from pycparser import c_parser, c_ast, parse_file, c_generator

def defineMacro(label, value):
	return f'#define {label} {value}'


def returnValue(val):
   return c_ast.Return(c_ast.ExprList([val]))


def mainFunction(calls):
	gen = c_generator.CGenerator()

	typedecl = c_ast.TypeDecl(f'main', [], c_ast.IdentifierType(names=['int']))
	funcdecl = c_ast.FuncDecl(None, typedecl)
	decl = c_ast.Decl(f'main', [], [], [], funcdecl, None, None)

	calls_ast = [c for c in map(lambda x : c_ast.FuncCall(c_ast.ID(x), c_ast.ExprList([])), calls)]
	calls_ast.append(returnValue(c_ast.Constant('int', str(0))))

	block = c_ast.Compound(calls_ast)
	main = c_ast.FuncDef(decl, None, block, None) 

	return gen.visit(main)
	

