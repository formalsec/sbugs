char* concrete_strdup(char *s){
	int size = 0; 
    while(*s != '\0'){
        s++;
        size++;
    }

    char* dest = (char*) malloc(size+1);
    char* save = dest;

	while (*s){
	   *dest++ = *s++;
	}

	*dest = '\0';
	return save;


}