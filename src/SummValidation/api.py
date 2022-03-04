type_defs = [
    'define NULL ((void*)0)'
    'typedef void* symbolic;',
    'typedef unsigned int size_t;',
    'typedef unsigned int cnstr_t;',
    'typedef unsigned int state_t;',
    'typedef unsigned int result_t;',
]

validation_api = {
    'save_current_state':    'state_t save_current_state() {return 0;}',
    'get_cnstr':             'cnstr_t get_cnstr(symbolic var, size_t size) {return 0;}',
    'add_expr':              'void add_expr(char* name, cnstr_t constraint) {return;}',
    'halt_all':              'void halt_all(state_t state) {return;}',
    'check_implications':    'result_t check_implications(char* constraint1, char* constraint2) {return 0;}',
    'print_counterexamples': 'void print_counterexamples(result_t result) {return;}'
}

standard_api = {
    'error':            'void error(char *fname) {return;}',
    'new_sym_var':      'symbolic _new_sym_var(size_t size) {return 0;}',
    'assume':           'void assume(cnstr_t cnstr) {return;}',
    'is_symbolic':      'int is_symbolic(symbolic sym_var, size_t) {return 0;}',
    'print_byte':       'void print_byte(char byte) {return;}',
    'maximize':         'void* maximize(symbolic sym_var, size_t length) {return NULL;}',
    'is_sat':           'int is_sat(cnstr_t cnstr) {return 0;}'

}

memory_api = {
    'mem_alloc':    'void* mem_alloc(void* size) {return NULL;}',
    'mem_addr':     'void mem_addr(void* addr, void* n, size_t length) {return;}',
    'mem_bytes':    'size_t* mem_bytes(void* ptr) {return -1;}',
    'mem_free':     'void summ_mem_free(void* ptr) {return;}',
}


sym_vars_api = {
    '_solver_Concat':   'symbolic _solver_Concat(symbolic sym_var, symbolic sym_var2, size_t length1, size_t length2) {return NULL;}', 
    '_solver_Extract':  'symbolic _solver_Extract(symbolic sym_var, size_t start, size_t end, size_t length) {return NULL;}',
    '_solver_ZeroExt':  'symbolic _solver_ZeroExt(symbolic sym_var, size_t to_extend, size_t length) {return NULL;}',
    '_solver_SignExt':  'symbolic _solver_SignExt(symbolic sym_var, size_t to_extend, size_t length) {return NULL;}'
}

constraints_api = {
    '_solver_NOT':  'cnstr_t _solver_NOT(cnstr_t cnstr1){return 0;}',
    '_solver_Or':   'cnstr_t _solver_Or(cnstr_t cnstr1, cnstr_t cnstr2) {return 0;}',
    '_solver_And':  'cnstr_t _solver_And(cnstr_t cnstr1, cnstr_t cnstr2) {return 0;}',
    '_solver_EQ':   'cnstr_t _solver_EQ(symbolic sym_var, symbolic sym_var2, size_t length) {return 0;}',
    '_solver_NEQ':  'cnstr_t _solver_NEQ(symbolic sym_var, symbolic sym_var2, size_t length) {return 0;}',
    '_solver_LT':   'cnstr_t _solver_LT(symbolic sym_var, symbolic sym_var2, size_t length) {return 0;}',
    '_solver_LE':   'cnstr_t _solver_LE(symbolic sym_var, symbolic sym_var2, size_t length) {summ_error("_solver_LE");return 0;}',
    '_solver_SLT':  'cnstr_t _solver_SLT(symbolic sym_var, symbolic sym_var2, size_t length) {summ_error("_solver_SLT");return 0;}',
    '_solver_SLE':  'cnstr_t _solver_SLE(symbolic sym_var, symbolic sym_var2, size_t length) {summ_error("_solver_SLE");return 0;}',
    '_solver_IF':   'cnstr_t _solver_IF(cnstr_t cond, cnstr_t cnstr1, cnstr_t cnstr2) {return 0;}'
}




