#ifndef LISTADUPJOGO_H
#define LISTADUPJOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 1024
#define MAXEQUIPA 1024

/* Definicao da estrutura jogo */
typedef struct {
    char *nome, *equipa1, *equipa2;
    int score[2];
} Jogo;

typedef struct str_node_jogo {
    struct str_node_jogo *next, *previous;
    Jogo * jogo;
} node_jogo;

typedef struct {
    node_jogo *head, *last;
} list_jogo;

/* cria um novo jogo */
Jogo * mk_jogo(char nome[MAXNOME], char eq1[MAXEQUIPA],
               char eq2[MAXEQUIPA], int score[2]);

/* cria lista duplamente ligada de jogos vazia */
list_jogo * mk_list_jogo();

void remove_jogo_aux(node_jogo * l_head, Jogo * j);

/* Remove jogo de uma lista */
void remove_jogo(list_jogo * l, Jogo *j);

/* acrescenta novo jogo no final da lista */
void add_last_jogo(list_jogo * l, Jogo * j);

/* liberta toda a memoria associada ao jogo */
void free_jogo(Jogo * j);

/* liberta toda a memoria associada a lista */
void free_list_jogo(list_jogo * l);

#endif