#ifndef __JOGO__
#define __JOGO__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Estrutura jogo com todas as informacoes inerentes a um jogo */


typedef struct jogo {
	char *nome_jogo;
	char *equipa_1;
	char *equipa_2;
	int score_1;
	int score_2;
} Jogo;

void free_jogo(Jogo* j);

Jogo *cria_jogo(char nome_jogo[],char equipa_1[],char equipa_2[],int score_1,int score_2);


#endif