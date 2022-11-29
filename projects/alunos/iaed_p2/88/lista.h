#ifndef __LISTA__
#define __LISTA__

#include <stdlib.h>

/* um no contem dois ponteiros: para um item generico e para o proximo no da lista */
typedef struct stru_no {
    void *item;
    struct stru_no *prox;
} no;

/* constroi */
no *novo_no(void *item);

/* modificadores */
no *insere(no *cabeca, void *item);
no *retira(no *cabeca, void *item, int (*igual)(void* , void*), void (*liberta_item)(void *));

/* liberta memoria */
void liberta_lista(no *cabeca, void (*liberta_item)(void *));

/* procura item */
void *procura(no *cabeca, void *item, int (*igual)(void* , void*));

#endif



