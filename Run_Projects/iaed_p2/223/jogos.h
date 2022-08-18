#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"

#ifndef JOGOS_H
#define JOGOS_H
typedef struct game {
	char *nome;
	Equipa equipa1;
	Equipa equipa2;
	int score1;
	int score2;
} *Jogo;

Jogo novoJogo(char *nome, Equipa e1, Equipa e2, int s1, int s2);
void libertaJogo(Jogo j);
void imprimeJogo(Jogo j);
void alteraPont(Jogo j, int s1, int s2);
int obtemPont(Jogo j, int p);
Equipa obtemEquipa(Jogo j, int e);
char * obtemNomeJogo(Jogo j);
#endif