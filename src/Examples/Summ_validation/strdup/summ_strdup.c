char* summ_strdup(char *s){
	int i = 0;
	char zero = '\0';

	while(1){
		if(is_symbolic(&s[i],8)){
			
			if(!is_sat(_solver_NEQ(&s[i], &zero, 8))){
				break;
			}
			
			else{
				assume(_solver_NEQ(&s[i], &zero, 8));
			}
		}
		else if(s[i] == '\0'){
			break;
		}
		
		i++;
	}
    
    int size = i;
    
    char* dest = mem_alloc(size);
    char* save = dest;

    while (*s){
	   *dest++ = *s++;
	}

	*dest = '\0';
	return save;
}
