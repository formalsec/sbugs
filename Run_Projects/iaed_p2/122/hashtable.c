#include "hashtable.h"
#include "strdup.h"
#include <stdlib.h>
#include <string.h>

static MATCH* st;   /* matches hashtable*/
static int M;    /* size of the hashtable*/

/* hashing function*/
unsigned int hash(char* v) {
    unsigned int val = 0, a;
    a = strlen(v);
    for(; *v != '\0'; v++)
        val = (a * val + *v);
    return val % M;
}

/* initializes the hashtable*/
void STinit() {
    int i;
    M = 2 * SIZE;
    st = (MATCH*)malloc(M*sizeof(MATCH));
    for(i = 0; i < M; i++)
        st[i] = NULL;
}

/* inserts a new match into the hashtable*/
void STinsert(MATCH match) {
    unsigned int i;
    i = hash(match->name);
    while(st[i] != NULL)
        i = (i + 1) % M;
    st[i] = matchdup(match);
    free(match->name);
    free(match->team1);
    free(match->team2);
    free(match);
}

/* deletes a match from the hashtable*/
void STdelete(char* name) {
    unsigned int i, j;
    MATCH v;

    i = hash(name);

    while(st[i] != NULL) {
        if(strcmp(st[i]->name, name) == 0)
            break;
        else
            i = (i + 1) % M; 
    }
    if(st[i] == NULL)
        return;
    free(st[i]->name);
    free(st[i]->team1);
    free(st[i]->team2);
    free(st[i]);
    st[i] = NULL;
    for(j = (i + 1) % M; st[j] != NULL; j = (j + 1) % M) {
        v = matchdup(st[j]);
        free(st[j]->name);
        free(st[j]->team1);
        free(st[j]->team2);
        free(st[j]);
        st[j] = NULL;
        STinsert(v);
    }
}

/* searches for match in the hashtable with a given name*/
MATCH STsearch(char* name) {
    unsigned int i;
    i = hash(name);
    while(st[i] != NULL) {
        if(strcmp(st[i]->name, name) == 0)
            return st[i];
        else
            i = (i + 1) % M;
    }
    return NULL;
        
}

/* deletes the hashtables*/
void STdeletetable() {
    int i;
    for(i = 0; i < M; i++) {
        if(st[i] != NULL) {
            free(st[i]->name);
            free(st[i]->team1);
            free(st[i]->team2);
            free(st[i]);
        }
    }
    free(st);
}

