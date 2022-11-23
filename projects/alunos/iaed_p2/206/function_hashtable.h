#ifndef _FUNCTION_HASHTABLE_
#define _FUNCTION_HASHTABLE_

/* Abstracao da funcao Hash. */
#define HASH(A, B) (hash(A, B))
/* Tamanho inicial da hashtable. */
#define HASHTABLE_STARTING_SIZE 7919
/* Constante para obter o novo tamanho da hashtable. */
#define EXPAND_CONSTANT_VARIABLE 4
/* Tamanho limite ate a hashtable ser expandida. */
#define EXPANDING_SIZE(A) (A->size/2)

int hash(char *name, int size);

#endif