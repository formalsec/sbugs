#ifndef JOGO_H
#define JOGO_H

/* Definicao das Estruturas */

typedef struct jogo {
    char *nome;
    ptrEquipa equipa1;
    ptrEquipa equipa2;
    int golos1;
    int golos2;
} *ptrJogo; /* ptrJogo e' um ponteiro para um jogo */

/* Necessario incluir listas.h para utilizar o tipo linkEquipa.
   Este include tem de ser feito no meio do codigo uma vez que em
   listas.h e' utilizado o tipo ptrJogo, logo este tem de ser
   definido antes. */
#include "listas.h"

/* Prototipos das Funcoes */

/* Cria um novo jogo, devolvendo um ponteiro para o mesmo */
ptrJogo criar_jogo(char *nome, linkEquipa equipa1, linkEquipa equipa2, int golos1, int golos2);
/* Recebe um jogo e liberta a memoria a ele associada */
void eliminar_jogo(ptrJogo jogo);

#endif