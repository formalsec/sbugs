#ifndef _AUX_
#define _AUX_

#include <string.h>
#include <stdlib.h>

#define A 127 /*Used in the hash function*/

char *StringDup(char *string);
int HashU(char *string, int M);

#endif