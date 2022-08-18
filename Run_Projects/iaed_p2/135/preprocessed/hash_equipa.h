#ifndef HASH_EQUIPA_H
#define HASH_EQUIPA_H

#include <stdio.h>
#include "auxiliar.h"

/* Definicao de estruturas*/
/* Estrutura Equipa*/
typedef struct equipa{
    char *nome;
    int n_ganhos;
}equipa;

typedef equipa * pEquipa;

/* Estrutura de um elemento da hash das equipas */
typedef struct node_equipa{
    pEquipa e;
    struct node_equipa *next;
}node_equipa;

typedef node_equipa * link_equipa;

/* Estrutura da Hashtable das equipas */
typedef struct hashtable_equipa{
    link_equipa * heads;
    int M;
}hashtable_equipa;

/* Prototipos das Funcoes sobre a hash das equipas */
hashtable_equipa* cria_hash_equipa(int m);
void insereHash_equipa(hashtable_equipa* ht, pEquipa e);
pEquipa procuraHash_equipa(hashtable_equipa* ht, char *v);
void FREEhash_equipa(hashtable_equipa* ht);
void maior_ganhos(hashtable_equipa* ht, int* max, int* n_equipas);
void nome_equipas_maior_ganhos(hashtable_equipa* ht, const int max,
                             const int n_equipas, const int n_comando);
                             
#endif
