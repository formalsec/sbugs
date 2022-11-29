#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_equipas{ /*node para equipas*/
   struct node_equipas *next; /*ponteiro para outra equipa*/
   char *nome; /*equipa*/
   int vitorias; /*numero de vitorias dessa equipa*/
} node_equipa;

typedef struct node_jogo{ /*node para jogos*/
   struct node_jogo *next, *next_list, *prev_list; /*ponteiro para outro jogo*/
   int s1, s2; /*pontuacao do jogo*/
   char *nome; /*nome do jogo*/
   char *t1, *t2; /*nome das equipas do jogo*/
} node_jogo;

void printlist_equipa(int cont, int vitorias, node_equipa *head);

void printlist_jogo(node_jogo *head, int cont);

node_jogo *cria_node_jg(char *nome, char *t1, char *t2, int s1, int s2);

node_equipa *cria_node_eq(char *nome);

node_jogo *insere_jogo_lista(node_jogo *head, node_jogo *jogo);

node_jogo *_insere_jogo_lista(node_jogo *head, node_jogo *jogo, node_jogo **last);

node_equipa *insere_equipa_lista(node_equipa *head, node_equipa *equipa);

node_equipa *encontra_listnode_eq(node_equipa *head, char *nome);

node_jogo *encontra_listnode_jg(node_jogo *head, char *nome);

void free_node_eq(node_equipa *node);

void free_node_jg(node_jogo *node);

node_jogo *delete_node_list(node_jogo *head, char *nome);

node_jogo *remove_node_list(node_jogo *head, node_jogo *jogo, node_jogo **last);

void destroy_list_eq(node_equipa *head);

void destroy_list_jg(node_jogo *head);

int compara(const void *a, const void *b);

#endif
