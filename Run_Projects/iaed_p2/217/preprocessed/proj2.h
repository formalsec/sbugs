#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NOME 1024
#define MAX_INPUT 1605
#define MAX_RESULT 3

/*Estruturas referentes as equipas e aos jogos criados*/

typedef struct node_jogos{

    char nome[MAX_NOME];
	char equipa1[MAX_NOME];
	char equipa2[MAX_NOME];
	char score1[3];
	char score2[3];
	struct node_jogos* next;
} *Jogo;
Jogo jogo, jogoatual, novojogo, jogoanterior, tmpjogo;

typedef struct node_equipas{

    char nome[MAX_NOME];
    int vitorias;
	struct node_equipas* next;
} *Equipa;
Equipa equipa, equipaatual, novaequipa, equipaanterior;

