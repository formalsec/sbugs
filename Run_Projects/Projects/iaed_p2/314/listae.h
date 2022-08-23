#ifndef LIST_H
#define LIST_H
#include "hashtableequipas.h"

typedef struct str_nodee {
    struct str_nodee* next, * previous;
    equipa* e;
} nodee;

typedef struct {
    nodee* head, * last;
} liste;

liste* mk_liste(); /* cria nova lista vazia */
void free_liste(liste* l);  /* liberta toda a memoria associada a lista */
void apaga_nodee(liste* l, nodee* n);  /*apaga um nodee dado*/
void adiciona_e(liste* l, equipa* n); /*adiciona uma nova equipa a lista*/

#endif