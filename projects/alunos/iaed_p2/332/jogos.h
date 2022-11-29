#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef JOGOS_H
#define JOGOS_H

#include "equipas.h"

/* tamanho maximo do nome de um jogo */
#define MAX_NOME 1023

/* estrutura dos jogos */
typedef struct jogo {
	char * nome_jogo;
	char * nome_eq1;
	char * nome_eq2;
	int score_eq1;
	int score_eq2;
	struct jogo *next;
	struct jogo *prev;
} * jogo;

/* funcoes relacionadas com os jogos */
void adiciona_jogo(int nl, jogo * ht_jg, equipa * ht_eq);
void free_jogo(jogo x);
jogo cria_jogo(char * nome, char * eq1, char * eq2, int score1, int score2);
void encontra_jogo(int nl, jogo * ht_jg);
void altera_score(int nl, jogo * ht_jg, equipa * ht_eq);
void lista_jogos(int nl, jogo * ht_jg);

#endif