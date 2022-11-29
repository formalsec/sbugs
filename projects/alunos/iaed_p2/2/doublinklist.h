#ifndef DOUBLINKLIST_H
#define DOUBLINKLIST_H

#include "jogo.h"

/* doubly linked list node */
typedef struct node {
	
	ItemDL v;
	struct node *prev, *next;
} *link;

extern link head;		/* head of the linked list. The tail is head->prev */


void DLinsertEnd(ItemDL v);

link DLsearch(ItemkeyDL k);

void DLremove_with_item_free(link p);

void DLdestroy_with_item_free();


#endif