#ifndef EQUIPALINCADA_H
#define EQUIPALINCADA_H

#include "Equipa.h"

/* Criacao do tipo do no de Equipa. */
typedef struct no_equipa {
    struct no_equipa *prox, *ant;
    Equipa *equipa;
} no_equipa;

/* Criacao do tipo da lista lincada de Equipas. */
typedef struct {
    no_equipa *cabeca, *ult;
} lista_equipa;

/* Funcao que gera uma lista lincada de Equipas. */
lista_equipa* gerar_lista_equipa();
/* Funcao que libera a memoria alocada pela lista lincada.*/
void liberar_lista_equipa(lista_equipa *lista);
/* Funcao que remove um no da lista de Equipas. */
void remover_no_equipa(lista_equipa *lista, no_equipa *n);
/* Funcao que adiciona um no de Equipa ao final da lista lincada. */
void adicionar_ultimo_equipa(lista_equipa *lista, Equipa *equipa);

#endif
