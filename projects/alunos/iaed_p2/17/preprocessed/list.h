#ifndef _LINKED_H
#define _LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itemGame.h"

typedef struct node* Link;

typedef struct node{
	ItemGame item;
	Link next;
}Node;

/* Struct for the whole list. Starts on head, ends on tail, has load games. */
typedef struct masterNode{
	int load;
	Link head;
	Link tail;
}* LinkedList;

LinkedList init_list();
Link add_node_before_list(Link next, ItemGame item);
Link add_node_after_list(Link prev, ItemGame item);
void delete_node_list(Link node);
ItemGame search_list(LinkedList list, char* name);
void append_list(LinkedList list, ItemGame item);
void remove_elem_list(LinkedList list, char* name);
void show_list(LinkedList list, int counter);
void destroy_list(LinkedList list);

#endif
