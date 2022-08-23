#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include "auxiliar.h"

/* Definicao de estruturas */
/* Estrutura Jogo */
typedef struct jogo{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
    char *vencedora;
}jogo;

typedef jogo * pJogo;

/* Prototipos das Funcoes sobre a Estrutura Jogo */
pJogo cria_jogo(const char * nome, const char * e1,
                const char * e2, const int s1, const int s2);
void altera_score_jogo(pJogo j, const int s1, const int s2);
void FREEjogo(pJogo j);

#endif
