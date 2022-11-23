#ifndef __JOGO__
#define __JOGO__

#include <stdlib.h>
#include <string.h>
#include "equipa.h"

#define NULLjogo NULL

typedef struct stru_jogo {
    char *nome;
    equipa e1, e2;
    int score_e1, score_e2;
    struct stru_jogo *ant, *prox;
} *jogo;

/* cria */
jogo novo_jogo(char *nome, equipa e1, equipa e2, int score_e1, int score_e2, jogo ultimo_jogo);

/* liberta memoria */
void liberta_jogo(void* jogo);

/* testa nome do jogo com string */
int jogo_nome_igual(void *jogo, void *nome);

#endif

