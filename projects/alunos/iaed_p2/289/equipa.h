#ifndef EQUIPA_H
#define EQUIPA_H

#include "abstract.h"

/* Estrutura que representa uma equipa */
struct equipa
{
    char *nome;
    unsigned int jogos_ganhos;
};

/* Estrutura que representa um ponteiro para equipa */
typedef struct equipa *ptr_equipa;

/* Estrutura que representa uma hash key para a Hash equipas */
typedef char *Key_equipa;

/* Define a key equipa */
#define key_equipa(a) (a->nome)

/* Liberta memoria alocada para a equipa */
void freeEquipa(ptr_equipa a);

/* Cria uma nova equipa */
ptr_equipa newEquipa(char *nome, int jogos_ganhos);

#endif