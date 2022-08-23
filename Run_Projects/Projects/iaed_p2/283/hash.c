#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"


/*funcao hash que gera o numero hash na hash table */


int hash(char *v) {
	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a*b % (HASH_SIZE-1)){
		h = (a*h + *v) % HASH_SIZE;
	}
return h;
}