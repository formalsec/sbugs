#ifndef _TEAMS_
#define _TEAMS_

#define H_LEN 1009  /* hash length */

typedef struct team {
    char *name;
    int wins;
} *pTeam;


typedef struct tNode {
    pTeam team;
    struct tNode *next, *prev;
} *tLink;

tLink tInsert_begin(tLink head, pTeam team);
/* inserts team in the top of a list (head) */

tLink tRemove(tLink head, char *name);
/* removes team from a list, searching for its name */

pTeam tSearch(tLink head, char *name);
/* search for team in a list, by its name */

int tHash(char *v);
/* calculates the hash's list index where the team is */

tLink* tInit(tLink *hash);
/* initiates the hashtable with NULL pointers */

pTeam tHTsearch(tLink *hash, char *name);
/* search for a team in hashtable */

void tHTinsert(tLink *hash, pTeam team);
/* insert a team in hashtable */

void tHTdelete(tLink *hash, char *name);
/* delete a team from hashtable */

int max_wins(tLink *hashTeam);
/* calculates the number of wins of the most winning team */

tLink alphInsert(tLink tHead, pTeam team);
/* insert a team in a linked list, sorted alphabetically. */

void freeTeam(pTeam t);
/* frees all the memory allocated for a team */

#endif