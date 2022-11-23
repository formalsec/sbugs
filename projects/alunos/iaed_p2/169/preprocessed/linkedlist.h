#ifndef _LINKEDLIST_
#define _LINKEDLIST_

#include "hash.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/* estrutura da lista */
typedef struct {

    struct node1 *head, *last;

}list;

list* mk_list();

void free_list(list* l);

void rm_node(list* l, node1 *n);

void add_last(list* l, char *n);

link1 search(list* l, char* n);

#endif