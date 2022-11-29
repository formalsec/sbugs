#ifndef hash
#define hash

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listasEQ.h"

typedef Link* HLink;

HLink inicializaHash(int m);
int hashEQ(char* v, int m);
void addHash(HLink head, Equipa* equipa,int m);
Equipa* procuraEqHash(HLink head, int m, char* nome);
HLink limpaHash(HLink head,int m);

#endif