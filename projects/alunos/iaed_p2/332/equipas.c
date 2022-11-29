#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "hash_equipas.h"

/* duplica uma string, alocando memoria dinamicamente */
char *strdup(const char *src) {
	char *dst = can_fail_malloc((strlen(src) + 1) * sizeof(char));
	if (dst == NULL) {
		return NULL;
	}
	strcpy(dst, src);
	return dst;
}


/* liberta a memoria reservada para uma equipa */
void free_equipa(equipa x) {
	free(x->nome_equipa);
	free(x);
}

/* cria uma equipa com o nome dado */
equipa cria_equipa(char * nome) {
	equipa nova = (equipa)can_fail_malloc(sizeof(struct equipa));
	nova->nome_equipa = strdup(nome);
	nova->vitorias = 0;
	return nova;
}

/* adiciona uma equipa ao sistema apos fazer as verificacoes necessarias */
void adiciona_equipa(int nl, equipa * ht) {
	char * nome = can_fail_malloc(MAX_NOME * sizeof(char));
	int verif;
	equipa nova;
	scanf(" %[^:\n]", nome);
	nova = cria_equipa(nome);
	verif = procura_equipa(nova->nome_equipa, ht);
	if (verif >= 0) {
		printf("%d Equipa existente.\n", nl);
		free_equipa(nova);
	}
	else {
		tab_insert_eq(nova, ht);
	}
	free(nome);
}

/* encontra uma equipa a partir do nome e indica as suas caracteristicas */
void encontra_equipa(int nl, equipa * ht) {
	char * nome = can_fail_malloc(MAX_NOME * sizeof(char));
	int indice;
	scanf(" %[^:\n]", nome);
	indice = procura_equipa(nome, ht);
	if (indice == -1) {
		printf("%d Equipa inexistente.\n", nl);
	}
	else {
		printf("%d %s %d\n", nl, ht[indice]->nome_equipa, ht[indice]->vitorias);
	}
	free(nome);
}


/* funcao auxiliar do qsort com o criterio de comparacao entre strings */
int compara_palavras(const void * a, const void * b) {
	const char **str1 = (const char **)a;
	const char **str2 = (const char **)b;
	return(strcmp(*str1, *str2));
}


/* lista as equipas com maior numero de vitorias por ordem alfabetica, indicando esse valor */
void melhores_equipas(int nl, equipa * ht) {
	int best = 0, contador = 0, i, indice = 0;
	char ** nomes;
	for (i = 0; i < MAX_TABELA_EQ; i++) {
		if (ht[i] != NULL) {
			if (ht[i]->vitorias > best) {
				best = ht[i]->vitorias;
				contador = 1;
			}
			else if (ht[i]->vitorias == best) {
				contador += 1;
			}
		}
	}
	if (contador > 0) {
		nomes = can_fail_malloc(contador * sizeof(char *));
		for (i = 0; i < MAX_TABELA_EQ; i++) {
			if (ht[i] != NULL) {
				if (ht[i]->vitorias == best) {
					nomes[indice] = ht[i]->nome_equipa;
					indice += 1;
				}
			}
		}
		qsort(nomes, contador, sizeof(char *), compara_palavras);
		printf("%d Melhores %d\n", nl, best);
		for (i = 0; i < contador; i++) {
			printf("%d * %s\n", nl, nomes[i]);
		}
		free(nomes);
	}
}