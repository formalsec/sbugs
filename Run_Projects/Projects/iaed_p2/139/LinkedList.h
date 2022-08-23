#ifndef _LINKED_H
#define _LINKED_H

/**
 * File:  LinkedList.h
 * Estrutura de dados que permite guardar um sequencia de elementos 
 * com tamanho variavel
**/

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

typedef struct Node* Link;

struct Node {
	Item item;
	Link next;
};

typedef struct MasterNode {
	int load;
	Link head;
	Link tail;
}* LinkedList;

LinkedList list_init();
void delete_node(Link node);
int is_empty(LinkedList list);
Item get_first_item(LinkedList list);
void append(LinkedList list, Item i);
void destroy_list_nodes(LinkedList list);
void destroy_list_node(LinkedList list, Key nome);
void destroy_list(LinkedList list);
Item get_item(Link node);
void remove_element(LinkedList list, Key k);
Link search_list(LinkedList list, Key key);
void insertInOrder(LinkedList list,Item i);
void push(LinkedList list, Item i);
void pop(LinkedList list);
#endif
