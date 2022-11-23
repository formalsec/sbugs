#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Funcao auxiliar que efetua o strdup. */
char* strdup(const char*s)
{
	char * dup = can_fail_malloc(strlen(s)+1);
	
	if(dup != NULL) strcpy(dup, s);
	return dup;
}

/* Funcao que recebe um nome e gera um indice da hash onde o item vai ser guardado. */
unsigned long hash_chave(int M, char *chave)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *chave++))
        hash = ((hash << 5) + hash) + c;

    return hash % M;
}
