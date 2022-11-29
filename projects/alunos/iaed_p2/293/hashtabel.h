#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct team TeamH;
typedef struct game GameH;
typedef struct in_teams NodeE;
typedef struct in_games NodeJ;
typedef struct hashteams Hteams;
typedef struct hashgames Hgames;
size_t hash(char *V, size_t M); 
void init_hash();
int hash_insert(TeamH *t);
TeamH *lookup(char *name);

#endif
