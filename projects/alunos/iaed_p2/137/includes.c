#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "includes.h"

char* novastring(char* s){
	char* nova_s = can_fail_malloc((strlen(s) + 1) * sizeof(char));
	strcpy(nova_s, s);

	return nova_s;
}