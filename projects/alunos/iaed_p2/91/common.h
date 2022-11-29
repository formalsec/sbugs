#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 1024

/* Funcao de hash utilizada pelas tabelas */
int hash(char *key, int capacidade);
/* Cria uma copia de uma string */
char *copiar_texto(char *input);

#endif
