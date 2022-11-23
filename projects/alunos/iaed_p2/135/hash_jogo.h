#ifndef HASH_JOGO_H
#define HASH_JOGO_H

#include <stdio.h>
#include "lista_jogo.h"

/* Definicao de estruturas */
/* Estrutura de um elemento da hash dos jogos */
typedef struct node_jogo{
    el_lista_jogo * el;
    struct node_jogo *next;
}node_jogo;

typedef node_jogo * link_jogo;

/* Estrutura da Hashtable dos jogos */
typedef struct hashtable{
    link_jogo * heads;
    int M;
}hashtable_jogo;

/* Prototipos das Funcoes sobre a hash dos jogos */
hashtable_jogo* cria_hash_jogo(int m);
void insereHash_jogo(hashtable_jogo* ht, el_lista_jogo* el);
el_lista_jogo* procuraHash_jogo(hashtable_jogo* ht, char *v);
void apagaHash_jogo(hashtable_jogo* ht, char *v);
void FREEhash_jogo(hashtable_jogo* ht);

#endif

