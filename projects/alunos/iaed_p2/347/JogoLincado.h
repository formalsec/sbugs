#ifndef JOGOLINCADA_H
#define JOGOLINCADA_H

#include "Jogo.h"

/* Criacao do tipo do no de Jogo. */
typedef struct no_jogo {
    struct no_jogo *prox, *ant;
    Jogo *jogo;
} no_jogo;

/* Criacao do tipo da lista lincada de Jogos. */
typedef struct {
    no_jogo *cabeca, *ult;
} lista_jogo;

/* Funcao que gera uma lista lincada de Jogos. */
lista_jogo* gerar_lista_jogo();
/* Funcao que libera a memoria alocada pela lista lincada.*/
void liberar_lista_jogo(lista_jogo *lista, int index);
/* Funcao que remove um no da lista de Jogos. */
void remover_no_jogo(lista_jogo *lista, no_jogo *n);
/* Funcao que adiciona um no de Jogo ao final da lista lincada. */
void adicionar_ultimo_jogo(lista_jogo *lista, Jogo *jogo);

#endif

