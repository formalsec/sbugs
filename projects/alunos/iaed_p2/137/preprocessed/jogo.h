#ifndef _JOGO_H
#define _JOGO_H

#define MAX_STRING 1023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_jogo {
	int id;
	char* nome;
	char* equipa1;
	char* equipa2;
	int score1;
	int score2;
} Jogo;

/* Devolve uma variavel Jogo com os argumentos dados */
Jogo novoJogo(char* nome, char* eq1, char* eq2, int sc1, int sc2, int id);

/* Liberta toda a memoria reservada por j */
void destroiJogo(Jogo j);

#endif