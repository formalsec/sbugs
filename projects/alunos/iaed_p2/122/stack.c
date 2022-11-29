#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "match.h"
#include "stack.h"
#include "strdup.h"

/* creates a new node for the stack*/
tlink tNEWnode(char* team, tlink next) {
    tlink x = (tlink)can_fail_malloc(sizeof(struct STACKteamsnode));
    x->team = team;
    x->next = next;
    return x;
}

/* frees a stack node*/
void tFREEnode(tlink t) {
    free(t->team);
    free(t);
}

/* initializes a stack*/
tSTACK tSTACKinit() {
    tSTACK ts = (tSTACK)can_fail_malloc(sizeof(struct tstack));
    ts->head = NULL;
    return ts;
}

/* checks if the stack is empty*/
int tSTACKempty(tSTACK ts) {
    return ts->head == NULL;
}

/* pushes a new team into the stack*/
void tSTACKpush(tSTACK ts, char* team) {
    ts->head = tNEWnode(team, ts->head);
}

/* checks if a team exists in the stack and returns in case it finds it*/
char* tSTACKteamsearch(tSTACK ts, char* team) {
    tlink t;
    for(t = ts->head; t != NULL; t = t->next)
        if(strcmp(t->team, team) == 0)
            return t->team;
    return NULL;
}

/* checks the stack's length*/
int tSTACKlength(tSTACK ts) {
    tlink t;
    int len = 0;
    for(t = ts->head; t != NULL; t = t->next)
        len++;
    return len;
}

/* deletes a stack*/
void tSTACKdelete(tSTACK ts) {
    tlink aux;
    while(ts->head != NULL) {
        aux = ts->head;
        ts->head = ts->head->next;
        free(aux->team);
        free(aux);
    }
    free(ts);
}