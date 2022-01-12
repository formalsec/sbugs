from collections import deque

class ArgType():
	def __init__(self, typ, arr):
		self._type = typ
		self._arr = arr
	
	def getType(self):
		return self._type
	
	def arraySize(self):
		return self._arr



class ScopeStack():

	def __init__(self):
		self.stack = deque()
		self.push()

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
		return str(self.stack)

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