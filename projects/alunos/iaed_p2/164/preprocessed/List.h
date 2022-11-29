#ifndef _LIST_
#define _LIST_

#include "Node.h"

/* List structure.*/

/* A double linked List is defined by 2 Nodes, a "head" and a "end".*/ 
typedef struct list {
    Node head, end;
} * List;

/* Prototypes of List's basic operations.*/

List InitList();

void SetHead(List l, Node node);
    
void SetEnd(List l, Node node);

Node Head(List l);

Node End(List l);

void InsertEnd(List l, Game g);

void RemoveGame(Node node, List l);

void DestroyList(List l);

#endif