#ifndef _JOGO_
#define _JOGO_

#include "equipa.h"

/* ESTRUTURA */

/* definicao da estrutura jogo: ADT */
struct str_jogo
{
    char * nome; /* ponteiro para uma string - nome */
    equipa e1, e2; /* equipas - participantes */
    int s1, s2; /* inteiros - score de cada equipa */
};

typedef struct str_jogo * jogo; /* ponteiro para o jogo */

/* ABSTRACOES */

#define EQ_1(j) (j->e1) /* equipa 1 de um jogo */
#define EQ_2(j) (j->e2) /* equipa 2 de um jogo */
#define CHAVE_JG(a) (a->nome) /* chave de um jogo - o seu nome */
#define JOGO(A) ((jogo) A) /* cast de um ponteiro qualquer para jogo */
#define NO_JG (NULL) /* jogo nulo (ponteiro NULL) */
#define JG_CERTO(a, b) (strcmp(a,b->nome) == 0) /* jogo certo (mesmo nome) */


/* PROTOTIPOS DAS FUNCOES */

/* criacao de um jogo */
jogo cria_jogo(char * nome, equipa e1, equipa e2, int s1, int s2); 
/* eliminacao de um jogo */
void apaga_jogo(jogo j); 
/* altera o score de um jogo */
void altera_score(jogo j, int s1, int s2); 
/* equipa vencedora de um jogo */
equipa obtem_vencedora(jogo j); 
/* escreve um jogo no stdout */
void escreve_jogo(int nL, jogo j);

#endif
