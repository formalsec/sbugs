#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STRUCT.h"

#define HASHSIZE       1009
#define EQUIPAHASHMAX   503

unsigned int hash(char* str);

equipaHash** criaEquipaHash();

void freeEquipaHash(equipaHash** equipaTable);

equipaHash* encontraEquipa(equipaHash** equipaTable, char* chave);

void AddEquipa(equipaHash** equipaTable, char* chave);

int jogosGanhos(equipaHash** equipaTable, char* chave);

void adicionaVitoria(equipaHash** equipaTable, char* chave);

void removeVitoria(equipaHash** equipaTable, char* chave);

int equipasMaisJogos(equipaHash** equipaTable, char* tab_final[EQUIPAHASHMAX]);

#endif