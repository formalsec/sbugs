#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

/* Funcao de hashing que transforma um nome numa chave */
unsigned int hash(char * name, int M) {
	unsigned int h, a = A, b = B;

	for (h = 0; *name != '\0'; name++, a=a*b % (M-1))
		h = (a*h + *name) % M;

	return h;
}
