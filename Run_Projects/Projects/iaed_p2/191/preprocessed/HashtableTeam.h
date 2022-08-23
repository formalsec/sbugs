#ifndef _HASHTABLETEAM_
#define _HASHTABLETEAM_

#include "Team.h"

/* Structure representing hashtable of teams. */
typedef struct hashtableT
{
    int size;
    int factor;
    Team **items;
} HTT;

/* Initializes hashtable */
HTT *newHTT(int factor, int size);

/* Inserts a team into the hashtable */
void insertHTT(HTT *table, Team *item);

/* Deletes a team from the hashtable */
void deleteHTT(HTT *table, Team *item);

/* Finds team on hashtable given its name */
Team *getTeam(HTT *table, char *name);

/* Frees the allocated memory of the hashtable */
void freeHTT(HTT *table);

#endif