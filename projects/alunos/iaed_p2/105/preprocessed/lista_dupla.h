#include "hash_table.h"
#define MAX_TABELA 1000

#ifndef LISTA
#define LISTA

typedef struct node{
    char *nome; /*nome do jogo*/
    struct node* next; /*elemento seguinte*/
    struct node* prev; /*elemento anterior*/
 } node_lista;


void insere_fim_lista(char *nome,node_lista **inicio,node_lista **fim);
void remove_el_lista(char *nome,node_lista **inicio,node_lista **fim);
void apaga_mem_lista(node_lista **inicio);

#endif
