#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Number of positions of the games hashtable */
#define M 1009 



/* Initializes Games hashtable. */
GAMElink * GAMEinit() {
    int i;
    GAMElink *Games;

    Games = can_fail_malloc(sizeof(GAMElink) * M);
    for(i = 0; i < M; i++) {
        Games[i] = NULL;
    }
    return Games;
}


/* Inserts a game in the hashtable. */
void GAMEinsert(Game * game, GAMElink * Games) {
    int i = hash(game->name);
    GAMElink next = Games[i];

    Games[i] = can_fail_malloc(sizeof(struct GAMEnode));
    Games[i]->next = next;
    Games[i]->game = game;
}


/* Searches for a game in the hashtable. */
Game * GAMEsearch(char * name, GAMElink * Games) {
    int i = hash(name);
    GAMElink head = Games[i];

    while(head && strcmp(name, head->game->name) != 0) {
        head = head->next;
    }
    if (!head) return NULL;
    return head->game;
}


/* Deletes a game from the hashtable. */
void GAMEdelete(char * name, GAMElink * Games) {
    int i = hash(name);
    GAMElink *link = &Games[i];
    GAMElink head = Games[i], *prev, tmp;

    for (prev = NULL; *link != NULL; prev = &(*link), link = &(*link)->next) {
        tmp = *link;
        if (strcmp(tmp->game->name, name) == 0) {
            if (tmp == head)
                *link = tmp->next;
            else
                (*prev)->next = tmp->next;
            destroyGame(tmp->game);
            free(tmp);
            break;
        }
    }
}


/* Frees all memory attached to the hashtable. */
void GAMESfree(GAMElink * Games) {
    int i;
    GAMElink head, tmp;

    for (i = 0; i < M; i++) {
        head = Games[i];
        while (head) {
            destroyGame(head->game);
            tmp = head->next;
            free(head);
            head = tmp;
        }        
    }

    free(Games);
}
