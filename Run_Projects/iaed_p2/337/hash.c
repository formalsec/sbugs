#include "hash.h"
#include "teams.h"
#include "games.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Esta e a funcao de hashing que devolve o index correspondente ao slot na hashtable. */

int hash(char * name, int h_cap){
	int h = 0, a_const = N_ASCIIS;

	for ( ; *name != '\0' ; name++)
		h = (h * a_const + *name) % h_cap;

	return h;
}

/* Esta funcao e responsavel por ver se um numero e ou nao primo. */

int eh_primo(int num){
	int i;
	int eh_primo = 1;
	if (num <= 2) return 0;

	for (i = 2; i < num; i++)
		if (num % i == 0) eh_primo = 0;

	return eh_primo;
}

