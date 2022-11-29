#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Node.h"

/* Creates and returns a new Node with all values initialized as NULL.*/
Node InitNode(){
    Node node = (Node) can_fail_malloc(sizeof(struct node));
    node->next = NULL;
    node->prev = NULL;
    node->game = NULL;
    return node;
}

/* Receives a Node and Game, sets that Node's game as Game.*/
void SetGame(Node node, Game g){
    node->game = g;
}

/* Receives two Nodes, the second one is defined as the firt's next.*/
void SetNext(Node node, Node next){
    node->next = next;
}

/* Receives two Nodes, the second one is defined as the firt's previous.*/
void SetPrev(Node node, Node prev){
    node->prev = prev;
}

/* Receives a Node and returns the next Node.*/
Node Next(Node node){
    return node->next;
}

/* Receives a Node and returns the previous Node.*/
Node Prev(Node node){
    return node->prev;
}

/* Receives a Node and return it's Game.*/
Game NodeGame(Node node){
    return node->game;
}

/* Receives a Node and destroys it.*/
void DestroyNode(Node node){
    free(node);
}