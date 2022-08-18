#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "hash_jogos.h"
#include "equipas.h"
#include "hash_equipas.h"

/* inicializa a hash table dos jogos */
jogo * init_tab_jogos() {
	int i, M = MAX_TABELA_JG;
	jogo * ht = malloc(M * sizeof(jogo));
	for (i = 0; i < M; i++) {
		ht[i] = NULL;
	}
	return ht;
}

/* insere um jogo na hash table */
void tab_insert_jg(jogo jg, jogo * ht) {
	char * key = jg->nome_jogo;
	int i = 0, M = MAX_TABELA_JG, h = hash(key);
	while (ht[(h + i)%M] != NULL) {
		i += 1;
	}
	ht[(h + i)%M] = jg;
}

/* encontra um jogo na hash table dado o nome */
int procura_jogo(char * key, jogo * ht) {
	int i = 0, M = MAX_TABELA_JG, h = hash(key);
	while (ht[(h + i)%M] != NULL) {
		if (strcmp(ht[(h+i)%M]->nome_jogo, key) == 0) {
			return (h+i)%M;
		}
		i += 1;
	}
	if (ht[(h + i)%M] != NULL && strcmp(ht[(h+i)%M]->nome_jogo, key) == 0) {
		return (h+i)%M;
	}
	return -1;
}

/* liberta a memoria reservada para a hash table dos jogos */
void free_tabela_jg(jogo * ht) {
	int i;
	for (i = 0; i < MAX_TABELA_EQ; i++) {
		if (ht[i] != NULL) {
			free_jogo(ht[i]);
		}
	}
}

/* apaga um jogo da hash table reinserindo os seguintes na procura linear */
void tab_delete_jg(jogo jg, jogo * ht_jg) {
	char * key = jg->nome_jogo;
	int j, i = 0, M = MAX_TABELA_JG, h = hash(key);
	jogo reposicionar;
	while (ht_jg[(h + i)%M] != NULL) {
		if (strcmp(ht_jg[(h+i)%M]->nome_jogo, key) == 0) {
			break;
		}
		else {
			i += 1;
		}
	}
	if (ht_jg[(h+i)%M] != NULL && strcmp(ht_jg[(h+i)%M]->nome_jogo, key) == 0) {
		free_jogo(ht_jg[(h+i)%M]);
		ht_jg[(h+i)%M] = NULL;
	}
	else if (strcmp(ht_jg[0]->nome_jogo, key) == 0) {
		free_jogo(ht_jg[0]);
		ht_jg[0] = NULL;
	}
	i += 1;
	for (j = (h+i)%M; ht_jg[j] != NULL; j = (j+1)%M) {
		reposicionar = ht_jg[j];
		ht_jg[j] = NULL;
		tab_insert_jg(reposicionar, ht_jg);
	}
}

/* reposiciona os jogos na hash table para procura linear */
void reposicionar(jogo jg, jogo * ht_jg) {
	char * key = jg->nome_jogo;
	int j, i = 0, M = MAX_TABELA_JG, h = hash(key);
	jogo reposicionar;
	while (ht_jg[(h + i)%M] != NULL) {
		if (strcmp(ht_jg[(h+i)%M]->nome_jogo, key) == 0) {
			break;
		}
		else {
			i += 1;
		}
	}
	if ((h+i)%M != 0 && ht_jg[(h+i)%M] != NULL && strcmp(ht_jg[(h+i)%M]->nome_jogo, key) == 0) {
		ht_jg[(h+i)%M] = NULL;
	}
	i += 1;
	for (j = (h+i)%M; ht_jg[j] != NULL; j = (j+1)%M) {
		reposicionar = ht_jg[j];
		ht_jg[j] = NULL;
		tab_insert_jg(reposicionar, ht_jg);
	}
}

/* apaga um jogo da hash table e do sistema */
void apaga_jogo(int nl, jogo * ht_jg, equipa * ht_eq) {
	char * nome = malloc(MAX_NOME * sizeof(char));
	int indice, eq1, eq2;
	jogo aux_free;
	scanf(" %[^:\n]", nome);
	indice = procura_jogo(nome, ht_jg);
	if (ht_jg[0] != NULL) {
		if (strcmp(ht_jg[0]->nome_jogo, nome) == 0) {
			eq1 = procura_equipa(ht_jg[0]->nome_eq1, ht_eq);
			eq2 = procura_equipa(ht_jg[0]->nome_eq2, ht_eq);
			if (ht_jg[0]->score_eq1 > ht_jg[0]->score_eq2) {
				ht_eq[eq1]->vitorias -= 1;
			}
			else if (ht_jg[0]->score_eq2 > ht_jg[0]->score_eq1) {
				ht_eq[eq2]->vitorias -= 1;
			}
			if (ht_jg[0]->next == NULL) {
				free_jogo(ht_jg[0]);
				ht_jg[0] = NULL;
			}
			else {
				aux_free = ht_jg[0];
				ht_jg[0] = aux_free->next;
				ht_jg[0]->prev = NULL;
				reposicionar(aux_free->next, ht_jg);
				free_jogo(aux_free);
			}
		}
		else if (indice > 0) {
			eq1 = procura_equipa(ht_jg[indice]->nome_eq1, ht_eq);
			eq2 = procura_equipa(ht_jg[indice]->nome_eq2, ht_eq);
			if (ht_jg[indice]->score_eq1 > ht_jg[indice]->score_eq2) {
				ht_eq[eq1]->vitorias -= 1;
			}
			else if (ht_jg[indice]->score_eq2 > ht_jg[indice]->score_eq1) {
				ht_eq[eq2]->vitorias -= 1;
			}
			if (ht_jg[indice]->next == NULL) {
				ht_jg[indice]->prev->next = NULL;
				tab_delete_jg(ht_jg[indice], ht_jg);
			}
			else if (ht_jg[indice]->prev == NULL) {
				ht_jg[indice]->next->prev = NULL;
				tab_delete_jg(ht_jg[indice], ht_jg);
			}
			else {
				ht_jg[indice]->next->prev = ht_jg[indice]->prev;
				ht_jg[indice]->prev->next = ht_jg[indice]->next;
				tab_delete_jg(ht_jg[indice], ht_jg);
			}
		}
		else {
			printf("%d Jogo inexistente.\n", nl);
		}
	}
	else {
		printf("%d Jogo inexistente.\n", nl);
	}
	free(nome);
}
