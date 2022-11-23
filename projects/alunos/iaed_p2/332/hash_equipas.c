#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "hash_equipas.h"

/* funcao de dispersao a partir do nome */
unsigned int hash(char *v) {
	int h, a = 31415, b = 27183, M = MAX_TABELA_EQ;
	for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
		h = (a*h + *v) % M;
	}
	return h;
}

/* inicializa a hash table das equipas */
equipa * init_tab_equipas() {
	int i, M = MAX_TABELA_EQ;
	equipa * ht = can_fail_malloc(M * sizeof(equipa));
	for (i = 0; i < M; i++) {
		ht[i] = NULL;
	}
	return ht;
}

/* insere uma equipa na hash table */
void tab_insert_eq(equipa eq, equipa * ht) {
	char * key = eq->nome_equipa;
	int i = 0, M = MAX_TABELA_EQ, h = hash(key);
	while (ht[(h + i)%M] != NULL) {
		i += 1;
	}
	ht[(h + i)%M] = eq;
}

/* procura uma equipa na hash table e caso exista indica em que posicao esta */
int procura_equipa(char * key, equipa * ht) {
	int i = 0, M = MAX_TABELA_EQ, h = hash(key);
	while (ht[(h + i)%M] != NULL) {
		if (strcmp(ht[(h+i)%M]->nome_equipa, key) == 0) {
			return (h+i)%M;
		}
		i += 1;
	}
	if (ht[(h + i)%M] != NULL && strcmp(ht[(h+i)%M]->nome_equipa, key) == 0) {
		return (h+i)%M;
	}
	return -1;
}

/* liberta a memoria reservada para a hash table das equipas */
void free_tabela_eq(equipa * ht) {
	int i;
	for (i = 0; i < MAX_TABELA_EQ; i++) {
		if (ht[i] != NULL) {
			free_equipa(ht[i]);
		}
	}
}