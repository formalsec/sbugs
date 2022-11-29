#ifndef HASH_J_H
#define HASH_J_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_j.h"
#include "jogo.h"

/* Definicao da estrutura no para os produtos
 que vai ser utilizada na hashtable. */
typedef struct node_j
{
    pJogo j;
    struct node_j *next;
}*link_j; /* link_j eh um ponteiro para uma struct node_j. */


/* Definicao da estrutura hashtable para os produtos. */
typedef struct hash_j
{
    link_j *heads;
    int M;
}*hash_j; /* hash_j eh um ponteiro para uma struct hash_j. */


/*Prototipos de funcoes*/


hash_j init_hash_jogo(int m);

link_j insert_jogo(link_j head, pJogo j);

void STinsert_jogo(hash_j hash, pJogo j);

pJogo search_jogo(link_j head, char *n_jogo);

pJogo STsearch_jogo(hash_j hash, char *n_jogo);

void free_link_j(link_j node);

link_j delete_jogo(link_j head, char *n_jogo);

void STdelete_jogo(hash_j hash, char *n_jogo);

void freeHash_j(hash_j hash);


#endif
