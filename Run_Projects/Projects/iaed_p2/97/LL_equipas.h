#ifndef LL_EQUIPAS
#define LL_EQUIPAS

#include "Equipas.h"

typedef struct elem_eq {
    struct elem_eq *prox;
    Item_eq *equipa;
} elem_eq;

/* Inicializa uma lista de equipas */
elem_eq* inicializa_lista_equipa();

/* Apaga o 1o elemtento da lista e retorna a nova cabeca */
elem_eq* apaga_primeira_equipa_lista(elem_eq *cabeca);

/* Adiciona a string novo a lista e retorna a nova cabeca */
elem_eq* adiciona_equipa_lista(elem_eq *cabeca, Item_eq *equipa);

/* Liberta toda a memoria associada com a lista e retorna NULL */
elem_eq* apaga_lista_equipas(elem_eq *cabeca);

/* Apaga a memoria associada a lista, sem apagar o seu conteudo */
elem_eq* liberta_lista_equipas(elem_eq *cabeca);

/* Retorna NULL se nome se encontrar na lista, o ponteiro caso contrario */
elem_eq* encontra_equipa_lista(elem_eq *cabeca, char *nome);

/* Retorna o proximo elemento da lista */
elem_eq* prox_equipa(elem_eq *el);

/* Retorna a equipa do elemento el */
Item_eq* acede_equipa(elem_eq *el);

/* Retorna o numero de elementos da lista */
int tamanho(elem_eq *el);

#endif