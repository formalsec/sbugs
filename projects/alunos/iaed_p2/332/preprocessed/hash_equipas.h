#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef HASH_EQUIPAS_H
#define HASH_EQUIPAS_H

#include "equipas.h"

/* numero maximo de equipas na hash table */
#define MAX_TABELA_EQ 32911

/* funcoes relacionadas com a hash table das equipas */
unsigned int hash(char * v);
equipa * init_tab_equipas();
void tab_insert_eq(equipa eq, equipa * ht);
int procura_equipa(char * key, equipa * ht);
void free_tabela_eq(equipa * ht);

#endif