#ifndef _LISTA_
#define _LISTA_

#include <stdlib.h>
#include "jogo.h"

/*Estrutura dos nos de uma lista duplamente ligada*/
typedef struct lst_node{
    pJogo jogo;
    struct lst_node* next; /*Ponteiro para o no do proximo jogo*/
    struct lst_node* prev; /*Ponteiro para o no do jogo anterior*/
} *lst_link;

/*Estrutura da lista*/
typedef struct lista_str{
    lst_link head; /*link que aponta para o primeiro elemento da lista*/
    lst_link tail; /*link que aponta para o uliimo elemento da lista*/
} *Lista;

void lst_init(Lista*);
lst_link lst_cria(pJogo);
lst_link lst_insere(pJogo, Lista);
void lst_remove(lst_link, Lista);
void lst_print(Lista, int);
void lst_node_free(lst_link);
void lst_free(Lista);

#endif