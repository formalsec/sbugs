#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Structure representing a game */
struct jogo{
	char *nome, *equipa1, *equipa2;
	unsigned int score1, score2;
};

/* Structure representing a double linked list */
typedef struct node {
	struct jogo game;
	struct node *next, *prev;
} *link;

link NEW(struct jogo game, link x);											/* Creates new node. */
link insertEnd(link head, link *last, struct jogo game, struct node **new);	/* Inserts a node at the end of list. */
void freeNode(link x);														/* Frees the dynamically allocated memory of a node. */
void rmNode(link x, link *head, link *last);								/* Removes a node from the double linked list. */
void print(link head, int nl);												/* Function to print all nodes in a given doubly linked list. */
void printSingle(link node, int nl);										/* Function to print a single node in a given doubly linked list. */

#endif