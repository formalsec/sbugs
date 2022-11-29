#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Definicao da estrutura jogo. */
typedef struct jogo
{
    struct jogo *next, *previous;
    char *n_jogo;
    char *eq1;
    char *eq2;
    int sc1;
    int sc2;
    char *vencedora;
}*pJogo; /* pJogo eh um ponteiro para uma struct jogo. */


/* Definicao da estrutura lista duplamente ligada para jogos. */
typedef struct list
{
    struct jogo *head, *last;
}*list; /* list eh um ponteiro para uma struct list. */


/*Prototipos de funcoes*/

list new_list();

pJogo cria_jogo(char *n_jogo, char *eq1, char *eq2, int sc1, int sc2, list ls);

void print_j(pJogo j);

void free_jogo(pJogo j);

void altera_score_aux(pJogo j, int sc1, int sc2);

void remove_el(list ls, pJogo j);

void print_list(list ls, int NL);

void free_list(list ls);


#endif
