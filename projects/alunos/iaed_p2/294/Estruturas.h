#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define STR_LEN 1023
#define HASH_LEN 1999

typedef struct jogo{
	char *nome;
	char *equipa1;
	char *equipa2;
	int pontuacao1, pontuacao2;
	struct jogo *proximo;
	struct jogo *anterior;
} Jogo;

typedef struct equipas{
	char *nome;
	int vitorias;
	struct equipas *proximo;
} Equipas;

typedef struct noJOGO{
	Jogo *ptrJOGO;
	struct noJOGO *proximo;
	struct noJOGO *anterior;
} cabeca_JOGO;

typedef struct noEQUIPA{
	Equipas *ptrEQUIPA;
	struct noEQUIPA *proximo;
} cabeca_EQUIPA;

typedef struct hashtable_JOGO{
	cabeca_JOGO **gaveta_JOGO;
} Hash_Jogo;

typedef struct hashtable_EQUIPAS{
	cabeca_EQUIPA **gaveta_EQUIPA;
} Hash_Equipa;

typedef struct{
	Equipas* topo;
} Lista_Equipas;

typedef struct{
	Jogo* topo;
	Jogo* fim;
} Lista_Jogos;

#endif