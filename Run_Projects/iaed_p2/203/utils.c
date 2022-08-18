#include "utils.h"

char* toLower(char* s) {
	char *p;
  	for(p = s; *p; p++) *p = tolower(*p);
  	return s;
}