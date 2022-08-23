#ifndef _NODE_
#define _NODE_

#include "Game.h"

/* Node structure.*/

/* Since it will be used at a double linked list, the structure Node is defined by 
2 Node pointers "next" and "prev" and 1 Game.*/ 
typedef struct node {
    struct node * next, * prev;
    Game game;
} * Node;

/* Prototypes of Node's basic operations.*/

Node InitNode();

void SetGame(Node node, Game g);

void SetNext(Node node, Node next);

void SetPrev(Node node, Node prev);

Node Next(Node node);

Node Prev(Node node);

Game NodeGame(Node node);

void DestroyNode(Node node);

#endif