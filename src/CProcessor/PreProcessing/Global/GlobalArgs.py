
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



class GlobalArgs():

	def __init__(self):
		self.vars = {}

	#Store global variable
	def addVar(self, name, vartype, array=None):
		self.vars[name] = ArgType(vartype, array)

	#Find the type of a variable
	def findType(self, name):
		return self.vars[name]

	def var_names(self):
		return self.vars.keys()

	
