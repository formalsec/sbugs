#ifndef EQUIPA_H
#define EQUIPA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicao da estrutura equipa. */
typedef struct equipa
{
    char *n_eq;
    int wins;
}*pEquipa; /* pEquipa eh um ponteiro para uma struct equipa. */


/*Prototipos de funcoes*/

pEquipa cria_equipa(char *n_eq);

void print_eq(pEquipa eq);

void free_eq(pEquipa eq);

#endif
