from pycparser import c_parser, c_ast, parse_file, c_generator

def defineMacro(label, value):
	return f'#define {label} {value}'
