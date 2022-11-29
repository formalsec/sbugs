#ifndef _LISTA_
#define _LISTA_

#define MAX_STRING 1024
#define HASH_SIZE 2000

#include "hash_table_jogo.h"
#include <stdio.h>

typedef struct node
{
    struct jogo* jogo;
    struct node* next;
}node;

node * lista_insert(jogo *j, node *head);

node * lista_lookup(char *nome, node *head);

node* lista_delete(char *nome, node *head);

#endif