#include <stdlib.h>

//Concrete implementation to be compared with
size_t summ_strlen(char* s){
	int i = 0; 
    while(*s != '\0'){
        s++;
        i++;
    }
    return i;
}