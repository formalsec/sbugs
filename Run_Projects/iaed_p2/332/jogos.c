#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "hash_jogos.h"
#include "equipas.h"
#include "hash_equipas.h"

/* liberta a memoria reservada para um jogo */
void free_jogo(jogo x) {
	free(x->nome_jogo);
	free(x->nome_eq1);
	free(x->nome_eq2);
	free(x);
}

/* cria um jogo, dado um nome, nomes das equipas e pontos */
jogo cria_jogo(char * nome, char * eq1, char * eq2, int score1, int score2) {
	jogo novo = (jogo)malloc(sizeof(struct jogo));
	novo->nome_jogo = strdup(nome);
	novo->nome_eq1 = strdup(eq1);
	novo->nome_eq2 = strdup(eq2);
	novo->score_eq1 = score1;
	novo->score_eq2 = score2;
	return novo;
}

/* adiciona um novo jogo apos fazer as verificacoes necessarias */
void adiciona_jogo(int nl, jogo * ht_jg, equipa * ht_eq) {
	char game[MAX_NOME], team1[MAX_NOME], team2[MAX_NOME];
	char *nome_jogo, *nome_eq1, *nome_eq2;
	int score1, score2, verif, verif_eq1, verif_eq2;
	jogo novo, aux_jg;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game, team1, team2, &score1, &score2);
	nome_jogo = malloc((strlen(game) + 1) * sizeof(char));
	nome_eq1 = malloc((strlen(team1) + 1) * sizeof(char));
	nome_eq2 = malloc((strlen(team2) + 1) * sizeof(char));
	strcpy(nome_jogo, game);
	strcpy(nome_eq1, team1);
	strcpy(nome_eq2, team2);
	novo = cria_jogo(nome_jogo, nome_eq1, nome_eq2, score1, score2);
	verif = procura_jogo(nome_jogo, ht_jg);
	verif_eq1 = procura_equipa(nome_eq1, ht_eq);
	verif_eq2 = procura_equipa(nome_eq2, ht_eq);
	if (ht_jg[0] != NULL) {
		if (strcmp(ht_jg[0]->nome_jogo, novo->nome_jogo) == 0) {
			printf("%d Jogo existente.\n", nl);
			free_jogo(novo);
		}
		else if (verif > 0) {
			printf("%d Jogo existente.\n", nl);
			free_jogo(novo);
		}
		else if (verif_eq1 == -1 || verif_eq2 == -1) {
			printf("%d Equipa inexistente.\n", nl);
			free_jogo(novo);
		}
		else {
			if (score1 > score2) {
				ht_eq[verif_eq1]->vitorias += 1;
			}
			else if (score2 > score1) {
				ht_eq[verif_eq2]->vitorias += 1;
			}
			novo->next = ht_jg[0];
			novo->prev = NULL;
			ht_jg[0]->prev = novo;
			aux_jg = ht_jg[0];
			ht_jg[0] = novo;
			tab_insert_jg(aux_jg, ht_jg);
		}
	}
	else {
		if(verif_eq1 == -1 || verif_eq2 == -1) {
			printf("%d Equipa inexistente.\n", nl);
			free_jogo(novo);
		}
		else {
			if (score1 > score2) {
				ht_eq[verif_eq1]->vitorias += 1;
			}
			else if (score2 > score1) {
				ht_eq[verif_eq2]->vitorias += 1;
			}
			novo->next = NULL;
			novo->prev = NULL;
			ht_jg[0] = novo;
		}
	}
	free(nome_jogo);
	free(nome_eq1);
	free(nome_eq2);
}

/* encontra um jogo, dado o nome, e indica as suas caracteristicas */
void encontra_jogo(int nl, jogo * ht_jg) {
	char * nome = malloc(MAX_NOME * sizeof(char));
	int indice;
	scanf(" %[^:\n]", nome);
	indice = procura_jogo(nome, ht_jg);
	if (ht_jg[0] != NULL) {
		if (strcmp(ht_jg[0]->nome_jogo, nome) == 0) {
			printf("%d %s %s %s %d %d\n", nl, ht_jg[0]->nome_jogo, ht_jg[0]->nome_eq1, ht_jg[0]->nome_eq2, ht_jg[0]->score_eq1, ht_jg[0]->score_eq2);
		}
		else if (indice > 0) {
			printf("%d %s %s %s %d %d\n", nl, ht_jg[indice]->nome_jogo, ht_jg[indice]->nome_eq1, ht_jg[indice]->nome_eq2, ht_jg[indice]->score_eq1, ht_jg[indice]->score_eq2);
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

/* altera a pontuacao de um jogo para a indicada */
void altera_score(int nl, jogo * ht_jg, equipa * ht_eq) {
	char * nome = malloc(MAX_NOME * sizeof(char));
	int eq1, eq2, novo_score1, novo_score2, indice;
	scanf(" %[^:\n]:%d:%d", nome, &novo_score1, &novo_score2);
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
			ht_jg[0]->score_eq1 = novo_score1;
			ht_jg[0]->score_eq2 = novo_score2;
			if (novo_score1 > novo_score2) {
				ht_eq[eq1]->vitorias += 1;
			}
			else if (novo_score2 > novo_score1) {
				ht_eq[eq2]->vitorias +=1;
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
			ht_jg[indice]->score_eq1 = novo_score1;
			ht_jg[indice]->score_eq2 = novo_score2;
			if (novo_score1 > novo_score2) {
				ht_eq[eq1]->vitorias += 1;
			}
			else if (novo_score2 > novo_score1) {
				ht_eq[eq2]->vitorias +=1;
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

/* lista todos os jogos no sistema pela ordem em que foram inseridos */
void lista_jogos(int nl, jogo * ht_jg) {
	jogo aux;
	if (ht_jg[0] != NULL) {
		aux = ht_jg[0];
		while (aux->next != NULL) {
			aux = aux->next;
		}
		while (aux->prev != NULL) {
			printf("%d %s %s %s %d %d\n", nl, aux->nome_jogo, aux->nome_eq1, aux->nome_eq2, aux->score_eq1, aux->score_eq2);
			aux = aux->prev;
		}
		printf("%d %s %s %s %d %d\n", nl, ht_jg[0]->nome_jogo, ht_jg[0]->nome_eq1, ht_jg[0]->nome_eq2, ht_jg[0]->score_eq1, ht_jg[0]->score_eq2);
	}
}