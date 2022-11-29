#include "funcoes_aux.h"

/*Numero maximo de caracteres no nome de um jogo (+ '\0').*/
#define NOME_JOGO 1024

/*Estrutura Jogo.*/
typedef struct Jogo
{
	/*Nome do jogo.*/
	char *nome;
	/*Nome da equipa1.*/
	char *equipa1;
	/*Nome da equipa2.*/
	char *equipa2;
	/*Resultado da equipa1 nesse jogo.*/
	int score_equipa1;
	/*Resultado da equipa2 nesse jogo.*/
	int score_equipa2;
	/*Linha de input em que o jogo e criado.*/
	int linha_n;
	/*Ponteiro para o proximo jogo com a mesma chave da hashtable.*/
	struct Jogo *next;
}Jogo;


void freeJogo(Jogo* a);

void printJogo(Jogo* a, int conta_linhas);

void alteraScore(Jogo* a, int score1, int score2);

Jogo* novoJogo(char *nome, char *equipa1, char *equipa2,
				int score1, int score2, int linha_n);
