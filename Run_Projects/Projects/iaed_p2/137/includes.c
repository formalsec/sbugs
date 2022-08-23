#include "includes.h"

char* novastring(char* s){
	char* nova_s = malloc((strlen(s) + 1) * sizeof(char));
	strcpy(nova_s, s);

	return nova_s;
}