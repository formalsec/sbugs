from collections import deque

class ArgType():
	def __init__(self, typ, arr):
		self._type = typ
		self._arr = arr
	
	def getType(self):
		return self._type
	
	def arraySize(self):
		return self._arr

	def __repr__(self):
		return f'(type:{self._type}, dim:{self._arr})'


#Store variable types, struct fields
# and typedef aliases
class ScopeStack():

	def __init__(self):
		self.aliases = {}
		self.structs = {}
		self.stack = deque()
		
		#Push global scope
		self.push()

	

	#Aliases
	def addAlias(self, alias, struct):
		self.aliases[alias] = struct

	def isAlias(self, alias):
		return alias in self.aliases

	def getStruct(self, alias):
		return self.aliases[alias]

	
	#Struct fields
	def addStruct(self, name):
		self.structs[name] = {}

	def addField(self, name, field, typ, array=None):
		self.structs[name][field] = ArgType(typ, array)

	def fieldType(self, name, field):
		return self.structs[name][field]

	
	#Scope context variables

	#Increase scope depth by 1
	def push(self):
		d = dict()
		self.stack.append(d)

	#Decrease scope depth by 1
	def pop(self):
		self.stack.pop()


	#Store a variable type in the current scope
	def addVar(self, name, vartype, array=None):
		top = self.stack[-1]
		top[name] = ArgType(vartype, array)

	#Find the type of a variable
	def findType(self, name):
		dup_stack = self.stack.copy()
		while dup_stack:
			scope = dup_stack.pop()
			if name in scope:
				return scope[name]
		return None

	

	def __repr__(self):
		string = ''
		dup_stack = self.stack.copy()
		while dup_stack:
			string += str(dup_stack.pop())
			string += '\n'
			string += str(self.structs)
		return string

'''
if __name__ == "__main__":
	stack = ScopeStack()
	stack.addVar('i', 'int')
	stack.push()
	stack.addVar('c', 'char')
	print(stack)
	
	stack.addVar('l', 'long')
	print(stack)
	print(stack.findType('i'))

	stack.pop()
	print(stack)
'''