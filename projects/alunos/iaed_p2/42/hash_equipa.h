#ifndef HASH_EQUIPA_H
#define HASH_EQUIPA_H

#include "equipa.h"

/* 
estrutura nodeE
no de uma lista ligada caracterizado por
- ponteiro para uma equipa
- ponteiro para o no seguinte
 */
typedef struct nodeE{
    pEquipa equipa;
    struct nodeE *next;
}*linkE; /* linkE eh um ponteiro para um nodeE*/

/* inicializa uma hashtable de equipas */
linkE* InitEquipa(int M);
/* insere uma equipa no inicio de uma lista */
linkE InsertEquipa(char *nome,linkE head);
/* procura uma equipa */
pEquipa SearchEquipa(char *nome,linkE head);
/* liberta uma hashtable de equipas */
void FreeHashEquipa(int M,linkE *heads);

#endif