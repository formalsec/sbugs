#include <stdio.h>

#include "function_hashtable.h"

int hash(char *name, int size) {

	int h = 0, a = 127;;

	for (; *name != '\0'; name++) {
		h = ((a * h + *name) % size);
	}

	return h;
}