#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"


/* This function allocates memory for a string and duplicates the given string */
char* ReadString(char *v) {
    char *s;
    s = (char*)can_fail_malloc(sizeof(char)*(strlen(v)+1));
    s = strcpy(s,v);
    return s;
}

/* Allocates memory for a Game and adds the info to the struct */
Game NewGame(link *head, link *tail, char *name, char *t1, char *t2) {
    Game g;
    g = (Game)can_fail_malloc(sizeof(struct game));
    scanf(":%d:%d", &g->s1, &g->s2);
    g->name = ReadString(name);
    g->t1 = ReadString(t1);
    g->t2 = ReadString(t2);
        InsertGame(head, tail, g);
    return g;
}

/* Adds a game to the tail of the double linked list */
void InsertGame(link *head, link *tail, Game g) {
    link aux = (link)can_fail_malloc(sizeof(struct node));
    if (*head == NULL) {
        *head = aux;
        (*head)->g = g;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        *tail = *head;
    }
    else {
        aux->g = g;
        aux->next = NULL;
        (*tail)->next = aux;
        aux->prev = *tail;
        *tail = aux;
    }
}

/* Removes a node from the list */
void RemoveGame(link *head, link *tail, char *name) {
    link aux, del;
    aux = *head;
    while (aux != NULL) {
        if (strcmp(aux->g->name, name) == 0)
            del = aux;
        aux = aux->next;
    }
    if (*head == NULL || del == NULL) 
        return; 
    if (*head == del)
        *head = del->next;
    else if (*tail == del)
        *tail = del->prev;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del);
}

/* Prints the Games from the list */
void PrintGame(link *node, int NL) {
    link aux;
    aux = *node;
    while(aux != NULL) {
        printf("%d %s %s %s %d %d\n",
         NL, aux->g->name, aux->g->t1, aux->g->t2, aux->g->s1, aux->g->s2);
        aux = aux->next;
    }
}

/* Frees the memory allocated for a Game */
void FreeGame(Game g) {
    free(g->name);
    free(g->t1);
    free(g->t2);
    free(g);
}


/*###########################################################*/
/*###########################################################*/


/* Allocates memory for a Team, and adds it to the system */
Team NewTeam(char *name, Team *head) {
    Team t;
    t = (Team)can_fail_malloc(sizeof(struct team));
    t->name = ReadString(name);
    t->wins = 0;
    if (*head == NULL) {
        *head = t;
        (*head)->next = NULL;
    }
    else {
        t->next = *head;
        *head = t;
    }
    return t;
}

/* Returns the max amount of victories */
int* MaxWins(Team *head, int *lst) {
    Team aux;
    aux = *head;
    lst[0] = 0;
    lst[1] = 0;
    while (aux != NULL) {
        if (aux->wins > lst[0]) {
            lst[0] = aux->wins;
            lst[1] = 1;
        }
        else if (aux->wins == lst[0])
            lst[1]++;
        aux = aux->next;
    }
    return lst;
}

/* Frees the memory allocated for a Team */
void FreeTeam(Team t) {
    free(t->name);
    free(t);
}
