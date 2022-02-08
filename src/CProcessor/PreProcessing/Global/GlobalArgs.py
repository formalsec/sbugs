from CProcessor import config


class ArgType():
	def __init__(self, typ, arr, value):
		self._type = typ
		self._arr = arr
		self._value = value
	
	def getType(self):
		return self._type
	
	def arraySize(self):
		return self._arr

	def __repr__(self):
		return f'(type:{self._type}, dim:{self._arr})'



class GlobalArgs():

	def __init__(self):
		self.vars = {}
		self.number_names = ['int', 'long', 'unsigned int', 'unsigned long']

	def numbers(self):
		numbers = []
		for k in self.var_names():
			typ = self.findType(k)
			if typ._type in self.number_names and len(typ._arr) == 0:	
				numbers.append(k)
		
		return numbers


	#Store global variable
	def addVar(self, name, vartype, array=None, value=None):
		self.vars[name] = ArgType(vartype, array, value)

		#Store Max array size found
		if array is not None:
			int_array = [v for v in map(lambda x : int(x), array)]
			if len(int_array) > 0:
				_max = max(int_array)
				if _max > config.max_array_size:
					config.max_array_size = _max


	#Find the type of a variable
	def findType(self, name):
		return self.vars[name]

	def var_names(self):
		return self.vars.keys()

	
