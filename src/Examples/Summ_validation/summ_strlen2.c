
//Summary implementation to be compared with
size_t summ_strlen(char* s){
	int i = 0;
	char zero = '\0';

	while(1){
		if(is_symbolic(&s[i],CHAR_SIZE)){
			
			if(!is_sat(_solver_NEQ(&s[i], &zero, CHAR_SIZE))){
				break;				
			}
			
			else{
				
				symbolic val = new_sym_var(INT_SIZE);
				cnstr_t r = _solver_SGE(&val, &i, INT_SIZE);
				assume(r);

				return val;
			}
		}
		else if(s[i] == '\0'){
			break;
		}
		
		i++;
	}

	return i;
}