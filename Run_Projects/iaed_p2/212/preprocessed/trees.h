#ifndef TREES_H_
#define TREES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista.h"	/* Double linked list based on slides. */

/* Structure representing a binary tree of games. */
typedef struct tree {
  struct node *x;	/* Pointer to double linked list of games. */
  struct tree *l,*r;
  int height;		/* In order to balance the tree, height is stored. */
} Tree;

/* Structure representing a binary tree of teams. */
typedef struct tree2 {
  char *x;
  int win;
  struct tree2 *l,*r;
  int height;		/* In order to balance the tree, height is stored. */
} Tree2;

Tree *initTree(void);												/* Initialization of games tree. */
Tree *newNode(struct node *x);										/* Creates new node. */
int height(Tree *h);												/* Returns the height of a tree. */
Tree *insertTree(Tree *t,struct node *nodo);						/* Inerts a node in a tree. */
Tree *searchTree(Tree *t, char *nome);								/* Searches a game given its name. */
Tree *max(Tree *h);													/* Goes to the max of a tree. */
Tree *deleteR(Tree *h, char *nome, link *head, link *last, int nl);	/* Removes a node from a tree and frees the memory. */
Tree *freeR(Tree *h, link head, link last);							/* Frees the allocated memory of a node. */
void freeTree(Tree *t);												/* Frees the entire tree. */
Tree *rotL(Tree *h);												/* Left rotation. */
Tree *rotR(Tree *h);												/* Right rotation. */
Tree *rotLR(Tree *h);												/* Double rotation Left Right. */
Tree *rotRL(Tree *h);												/* Double rotation Right Left. */
int balance(Tree *h);												/* Balance factor. */
Tree *AVLbalance(Tree *h);											/* AVL Balancing function based on slides. */

Tree2 *initTree2(void);												/* Initialization of teams tree. */
Tree2 *newNode2(char *x);											/* Creates new node. */
int height2(Tree2 *h);												/* Returns the height of a tree. */
Tree2 *insertTree2(Tree2 *t, char *nome);							/* Inerts a node in a tree. */
Tree2 *searchTree2(Tree2 *t, char *nome);							/* Searches a team given its name. */
Tree2 *rotL2(Tree2 *h);												/* Left rotation. */
Tree2 *rotR2(Tree2 *h);												/* Right rotation. */
Tree2 *rotLR2(Tree2 *h);											/* Double rotation Left Right. */
Tree2 *rotRL2(Tree2 *h);											/* Double rotation Right Left. */
int balance2(Tree2 *h);												/* Balance factor. */
Tree2 *AVLbalance2(Tree2 *h);										/* AVL Balancing function based on slides. */
void freeTree2(Tree2 *t);											/* Frees the entire tree. */
void traverse(Tree2 *h, int *win);									/* Travels through every node of a tree. */
void printMostWins(Tree2 *t, int win, int nl);						/* Prints the teams with a certain amount of wins */

#endif