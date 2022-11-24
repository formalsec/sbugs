#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "structs.h"


/* Hash function, which determines where the info will be placed in the HashTable */
int hash(char *v, int M){
    unsigned int h = 0, i = 233, j = 113;
    for (; *v != '\0'; v++, i = (i*j) % (M-1))
        h = (h*i + *v) % (M-1);
    return h;
}

/* Initializes the Games HashTable */
Game* STinitG(int M) {
    int i; 
    Game *stg;
    stg = (Game*)can_fail_malloc(M*sizeof(Game));
    for (i = 0; i < M; i++)
        stg[i] = NULL;
    return stg;
}

/* Adds a Game to the HashTable */
void STinsertG(Game g, int M, Game *stg) {
    int i = hash(g->name, M);
    while (stg[i] != NULL)
        i = (i+1) % M;
    stg[i] = g;
}

/* Deletes a Game from the HashTable */
void STdeleteG(char* v, int M, Game *stg) {
    int j, i = hash(v, M);
    Game g;
    while (stg[i] != NULL) { /* Searches for the Game */
        if (strcmp(stg[i]->name, v) == 0) 
            break;
        else
            i = (i+1) % M;
    }
    if (stg[i] == NULL)
        return;
    FreeGame(stg[i]);
    stg[i] = NULL;
    for (j = (i+1) % M; stg[j] != NULL; j = (j+1) % M) { /* Inserts the Games after the one removed */
        g = stg[j];                                      /* as they might be in the wrong position */
        stg[j] = NULL;
        STinsertG(g, M, stg);
    }
}

/* Searches for a Game in the HashTable */
Game STsearchG(char* v, int M, Game *stg) {
    int i = hash(v, M);
    while (stg[i] != NULL) {
        if (strcmp(stg[i]->name, v) == 0)
            return stg[i];
        else
            i = (i+1) % M;
    }
    return NULL;
}


/*###########################################################*/
/*###########################################################*/


/* Initializes the Teams HashTable */
Team* STinitT(int M) {
    int i;
    Team *stt;
    stt = (Team*)can_fail_malloc(M*sizeof(Team));
    for (i = 0; i < M; i++)
        stt[i] = NULL;
    return stt;
}

/* Adds a Team to the HashTable */
void STinsertT(Team t, int M, Team *stt) {
    int i = hash(t->name, M);
    while (stt[i] != NULL)
        i = (i+1) % M;
    stt[i] = t;
}

/* Deletes a Team from the HashTable */
void STdeleteT(char* v, int M, Team *stt) {
    int j, i = hash(v, M);
    Team t;
    while (stt[i] != NULL) {
        if (strcmp(stt[i]->name, v) == 0) 
            break;
        else 
            i = (i+1) % M;
    }
    if (stt[i] == NULL)
        return;
    FreeTeam(stt[i]); 
    stt[i] = NULL;
    for (j = (i+1) % M; stt[j] != NULL; j = (j+1) % M) {
        t = stt[j];
        stt[j] = NULL;
        STinsertT(t, M, stt);
    }
}

/* Searches for a Team in the HashTable */
Team STsearchT(char* v, int M, Team *stt) {
    int i;
    i = hash(v, M);
    while (stt[i] != NULL) {
        if (strcmp(stt[i]->name, v) == 0)
            return stt[i];
        else
            i = (i+1) % M;
    }
    return NULL;
}
