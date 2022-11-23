#ifndef __HASH_H__
#define __HASH_H__
#define HASH_SIZE 1009 /* Hash map's number of indexes */

#include "games.h"

typedef struct hash_node {
    char *id;
    void * item; /* Setting item as void * allows for more abstraction */
    struct hash_node *next;
} *hash; /* Internal representation of an hash node */ 

unsigned int hashCode(char *str);
void HASHinit();
void hashInsertTeam(Team *team);
void hashInsertGame(Game *game);
void hashInsert(hash *table, hash item, char *str);
Game *searchGameHash(char *str);
Team *searchTeamHash(char *str);
void *hashSearch(hash *table, char *str);
void *hashRemove(char *str);
void particularHashClean(hash *head, void(* freeItem)(void *item));
void hashClean();
char **getBestTeams(int *length, unsigned int *wins);

#endif
