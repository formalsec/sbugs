#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strdup.h"

/* ============================================================ */

typedef struct stru_node /* structure of a node of the linked list */
{
    struct stru_node *next;
    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;
} node;

/* ============================================================ */

node * ListDelete(node *head, char *string);

node * AddElement(node *head,  char *name, char *team1, char *team2, int score1, int score2);

node * DestroyList(node *head);

node * SearchLL(node*head, char *name);

/* ============================================================ */

#endif