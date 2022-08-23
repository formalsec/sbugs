#include "jogos.h"

#ifndef NODES_H
#define NODES_H

/* Estrutura dos nos de equipas */
typedef struct node_eq{
	eq *equipa;
	struct node_eq *next;
} *node_eq;

/* Estrutura dos nos de jogos */
typedef struct node_jg{
	jg *jogo;
	struct node_jg *next;
} *node_jg;

/* Estrutura dos nos da lista do comando l */
typedef struct link{
	struct node_jg *tail, *head;
} link;

node_eq push_eq(node_eq head, eq *equipa);
int l_eq_empty(node_eq head);
eq *search_eq(node_eq head, char *nome);
node_jg push_jg(node_jg head, jg *jogo);
int l_jg_empty(node_jg head);
jg *search_jg(node_jg head, char *nomep);
node_jg remove_jg(node_jg head, jg *jogo);
void push_before(link *lista, jg *jogo);
void push_lista(link *lista, jg *njogo);
void remove_lista(link *lista, jg *jogo);

#endif