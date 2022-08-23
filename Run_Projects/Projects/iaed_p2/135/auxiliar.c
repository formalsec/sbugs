#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"


/* Aloca memoria suficiente para fazer copia da string que recebe e copia-a */
char* strdup(const char*s){
	char * dup = malloc(strlen(s)+1);
	
	if(dup != NULL) strcpy(dup, s);
	return dup;
}

/* Funcao de dispersao para strings */
int hash(char * v, int M){
    int h = 0, a = 31415, b = 27183;

    for(h = 0; *v != '\0'; v++, a = a*b%(M-1)){
        h = (a+h + *v) % M;
    }

    return h;
}
