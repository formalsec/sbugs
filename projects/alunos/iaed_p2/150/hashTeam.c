#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h> /* para tirar */
#include <string.h>
#include <stdlib.h>
#include "hashTeam.h"


/* Number of positions of the teams hashtable */
#define M 1009 



/* Returns index by doing the sum of all characters of the team name module M. */
int hash(char * name) {
    int sum = 0, a = 127;

    for (; *name != '\0'; name++) {
        sum = (a * sum + *name) % M;
    }
    return sum;
}


/* Initializes Teams hashtable. */
TEAMlink * TEAMinit() {
    int i;
    TEAMlink *Teams;

    Teams = can_fail_malloc(sizeof(TEAMlink) * M);
    for (i = 0; i < M; i++) {
        Teams[i] = NULL;
    }
    return Teams;
}


/* Inserts a team in the hashtable. */
void TEAMinsert(Team * team, TEAMlink *Teams) {   
    int i = hash(team->name);
    TEAMlink next = Teams[i];

    Teams[i] = can_fail_malloc(sizeof(struct TEAMnode));
    Teams[i]->next = next;
    Teams[i]->team = team;
}


/* Searches for a team in the hashtable. */
Team * TEAMsearch(char * name, TEAMlink * Teams) {
    int i = hash(name);
    TEAMlink head = Teams[i];

    while(head && strcmp(name, head->team->name) != 0) {
        head = head->next;
    }
    if (!head) return NULL;
    return head->team;
}


/* Deletes a team from the hashtable. */
void TEAMdelete(Team * team, TEAMlink *Teams) {
    int i = hash(team->name);
    TEAMlink *link = &Teams[i];
    TEAMlink tmp = NULL;

    while (*link) {
        tmp = *link;
        if (strcmp(tmp->team->name, team->name) == 0) {
            *link = tmp->next;
            destroyTeam(tmp->team);
            free(tmp);
            break;
        }
        else {
            link = &(*link)->next;
        }
    }
}


/* Frees all memory attached to the hashtable. */
void TEAMSfree(TEAMlink *Teams) {
    int i;
    TEAMlink head, tmp;

    for (i = 0; i < M; i++) {
        head = Teams[i];
        while (head) {
            destroyTeam(head->team);
            tmp = head->next;
            free(head);
            head = tmp;
        }        
    }

    free(Teams);
}

