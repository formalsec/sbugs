#ifndef __EQUIPA__
#define __EQUIPA__

#include <stdlib.h>
#include <string.h>

#define NULLequipa NULL

typedef struct stru_equipa {
    char *nome;
    int vitorias;
} *equipa;

/* cria */
equipa nova_equipa(char *nome, int jogos);

/* liberta memoria */
void liberta_equipa(void *e);

/* testa nome da equipa com string */
int equipa_nome_igual(void *e, void *string);

#endif



