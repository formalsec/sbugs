#ifndef LISTADUPEQUIPA_H
#define LISTADUPEQUIPA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 1024
#define MAXEQUIPA 1024

/* Definicao da estrutura equipa */
typedef struct {
    char *nome;
    int vitorias;
} Equipa;

typedef struct str_node_equipa {
    struct str_node_equipa *next, *previous;
    Equipa * equipa;
} node_equipa;

typedef struct {
    node_equipa *head, *last;
} list_equipa;

/* cria uma nova equipa */
Equipa * mk_equipa(char nome[MAXEQUIPA]);

/* cria lista duplamente ligada de equipas vazia */
list_equipa * mk_list_equipa();

/* acrescenta nova equipa no final da lista */
void add_last_equipa(list_equipa * l, Equipa * j);

/* liberta toda a memoria associada a uma equipa */
void free_equipa(Equipa * j);

/* liberta toda a memoria associada a lista */
void free_list_equipa(list_equipa * l);

#endif