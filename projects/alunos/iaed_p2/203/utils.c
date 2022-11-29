#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "utils.h"

char* toLower(char* s) {
	char *p;
  	for(p = s; *p; p++) *p = tolower(*p);
  	return s;
}