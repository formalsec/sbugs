#ifndef LISTJ_H
#define LISTJ_H
#include "hashtablejogo.h"

/*estrutura dos nos da listaj*/
typedef struct str_nodej {
    struct str_nodej* next, * previous;
    jogo* j;
} nodej;

/*estrutura da lista de jogos*/
typedef struct {
    nodej* head, * last;
} listj;

listj* mk_listj(); /* cria nova lista vazia */
void free_listj(listj* l); /* liberta toda a memoria associada a lista */
void apaga_nodej(listj* l, nodej* n); /*apaga um nodej dado*/
void adiciona_j(listj* l, jogo* n); /*adiciona um novo jogo a lista*/


#endif