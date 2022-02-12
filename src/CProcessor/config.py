#Declare arrays in the heap (uses malloc)
HEAP = True

#Store an object containing all global variables
global_vars = None

#After preprocessing store the max array size
max_array_size = 0



#Constrain global vars
GLOBAL_MIN = -9999
GLOBAL_MAX =  9999

CONSTRAIN_UPPER = True
CONSTRAIN_LOWER = False

CONSTRAIN_MAX_ARRAY = True



#Stubs
new_sym_var_DECL = 'void *new_sym_var(unsigned int length){return 0;}\n'
_assume_leq = 'void _assume_leq(void* sym_var, int val){return;}\n'
_assume_geq = 'void _assume_geq(void* sym_var, int val){return;}\n'

stubs = [new_sym_var_DECL, _assume_leq, _assume_geq]