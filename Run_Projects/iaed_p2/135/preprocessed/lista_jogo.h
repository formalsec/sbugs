#ifndef LISTA_JOGO_H
#define LISTA_JOGO_H

#include <stdio.h>
#include "jogo.h"

/* Definicao de estruturas */
/* Estrutura de um elemento da lista duplamente ligada */
typedef struct d_node_jogo{
    struct d_node_jogo * next, * previous;
    pJogo j;
}el_lista_jogo;

/* Estrutura da lista duplamente ligada de jogos*/
typedef struct  {
    struct d_node_jogo * head, * last;
}list;

/* Prototipos das Funcoes sobre a lista duplamente ligada de jogos */
list* cria_lista_dupla();
el_lista_jogo* adiciona_elemento(list* l, pJogo j);
void remove_elemento(list* l,  el_lista_jogo* elemento);
void imprime_lista_jogo(list* l, const int n_comando);
void FREEel_lista(el_lista_jogo *t);
void FREElista(list* l);

#endif
