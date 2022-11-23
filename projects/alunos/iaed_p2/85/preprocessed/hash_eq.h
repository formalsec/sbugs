#ifndef HASH_EQ_H
#define HASH_EQ_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipa.h"
#include "jogo.h"

/* Definicao da estrutura no para as equipas
que vai ser utilizada na hashtable. */
typedef struct node_eq
{
    pEquipa eq;
    struct node_eq *next;
}*link_eq; /* link_eq eh um ponteiro para uma struct node_eq. */


/* Definicao da estrutura hashtable para as equipas. */
typedef struct hash_eq
{
    link_eq *heads;
    int M;
}*hash_eq; /* hash_eq eh um ponteiro para uma struct hash_eq. */


/*Prototipos de funcoes*/

hash_eq init_hash_eq(int m);

link_eq insert_eq(link_eq head, pEquipa eq);

void STinsert_eq(hash_eq hash, pEquipa eq);

pEquipa search_eq(link_eq head, char *n_eq);

pEquipa STsearch_eq(hash_eq hash, char *n_eq);

void corrige_wins(hash_eq hash_eq, pJogo j, char *old_vencedora);

void calcula_max(hash_eq hash, int *max, int *num_eq);

int comparestr(const void*pa, const void*pb);

void imprime_vencedoras(hash_eq hash, int max, int num_eq, int NL);

void free_link_eq(link_eq node);

void freeHash_eq(hash_eq hash);


#endif
