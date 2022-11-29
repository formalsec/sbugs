#ifndef JOGOS_H
#define JOGOS_H

#include "equipas.h"

/* Estrutura de um node de uma lista duplamente ligada que representa um jogo. */
typedef struct node_struct_jogos {
    struct node_struct_jogos *next;     /* Node seguinte. */
    struct node_struct_jogos *previous; /* Node anterior. */
    char *nome;                         /* Nome do jogo. */
    node_equipas *equipa1;              /* Equipa 1. */
    node_equipas *equipa2;              /* Equipa 2. */
    int score1;                         /* Score da equipa 1. */
    int score2;                         /* Score da equipa 2. */

} node_jogos;

/* Estrutura de uma lista duplamente ligada que representa todos os jogos. */
typedef struct {
    node_jogos *head; /* Primeiro jogo da lista. */
    node_jogos *last; /* Ultimo jogo da lista. */

} Jogos;

Jogos *init_jogos();         /* Inicializa os jogos. */
void destroy_jogos(Jogos *); /* Liberta a memoria associada aos jogos. */

node_jogos *cria_jogo(char *, node_equipas *, node_equipas *, int, int); /* Inicializa um jogo. */
void add_jogo(Jogos *, node_jogos *);                                    /* Adiciona um jogo. */
void remove_node_jogos(Jogos *, node_jogos *);                           /* Remove um jogo. */
void atualiza_scores_jogo(node_jogos *, int, int);                       /* Atualiza os scores. */

#endif
