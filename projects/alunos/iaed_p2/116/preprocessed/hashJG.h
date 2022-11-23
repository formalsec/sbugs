#ifndef hash_
#define hash_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listasJG.h"

typedef Link_* HLink_;

HLink_ inicializaHash_(int m);
int hashJG(char* v, int m);
void addHash_(HLink_ head, Jogo* jogo,int m);
Jogo* procuraJgHash(HLink_ head, int m, char* nome);
void remHash_(HLink_ head,char* nome,int m);
HLink_ limpaHash_(HLink_ head,int m);
void remHash_caso(HLink_ head,char* nome,int m);

#endif