#ifndef JOGOS_H
#define JOGOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Estrutura da equipa */
typedef struct equipa{
	char *des;
	int vitorias;
} eq;

/* Estrutura do jogo */
typedef struct jogo{
	eq *eq1, *eq2;
	char *nome;
	int scr1, scr2;
} jg;

#endif