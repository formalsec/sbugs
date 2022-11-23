#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct jogo
{
    char *nome;
    char *equipa1;
    char *equipa2;
    unsigned int score[2];

} *pJogo; /* pJogo eh um ponteiro para um jogo */


/* prototipos ---------------------------------------------------------------------------------- */

/* cria um jogo e devolve o ponteiro para o jogo */
pJogo cria_jogo(char*, char*, char*,unsigned int[2]);

/* devolve o nome de um jogo */
char* obtem_nome_jogo(pJogo);

/* altera o score de um jogo */
void altera_score_jogo(pJogo, unsigned int[2]);

/* devolve o nome da equipa vencedora do jogo, se for empate devolve NULL */
char* obtem_vencedor_jogo(pJogo jogo);

/* escreve o score, o nome das equipas, e o nome de um jogo */
void print_jogo(pJogo, unsigned int);

/* liberta a memoria alocada a um jogo */
void free_jogo(pJogo);
