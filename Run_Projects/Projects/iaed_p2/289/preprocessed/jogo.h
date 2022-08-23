#ifndef JOGO_H
#define JOGO_H

#include "abstract.h"
#include "equipa.h"

struct jogo
{
    char *nome;
    ptr_equipa equipa1, equipa2;
    unsigned int score1, score2;
};

typedef struct jogo *ptr_jogo;

/* Liberta a memoria alocada para um Jogo */
void freeJogo(ptr_jogo a);

/* Cria um novo Jogo */
ptr_jogo newJogo(char *nome, ptr_equipa equipa1, ptr_equipa equipa2, int score1, int score2);

#endif