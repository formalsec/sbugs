#ifndef _LINKEDLISTH_
#define _LINKEDLISTH_

#include "Item.h"

struct node {
  Item item;
  struct node *next;
};

typedef struct node *link;

link newNode(Item item);
void insertBegin(link* head, Item item);
void insertEnd(link* head, Item item);
void insertSorted(link* head, Item item);
void removeNode(link* head, Item item);
void deleteList(link* head);

#endif
