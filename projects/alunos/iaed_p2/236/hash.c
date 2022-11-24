#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"

/*
hashing function
input: name(*char)
output: hash(unsigned int)
*/
unsigned int hash(char *name){
	int i, length;
	unsigned int hash;
	length = strlen(name);
	hash = 0;
	for (i = 0; i < length; ++i){
		hash += name[i];
		hash = (hash*name[i])%TABLE_SIZE;
	}
	return hash;
}
