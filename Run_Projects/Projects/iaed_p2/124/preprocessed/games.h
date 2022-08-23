#ifndef _GAMES_
#define _GAMES_

#define H_LEN 1009

typedef struct game {
    char *name, *team1, *team2;
    int score1, score2;
} *pGame;


typedef struct gNode {
    pGame game;
    struct gNode *next, *prev;
} *gLink;


gLink gInsert_begin(gLink head, pGame game);
/* inserts game in the top of a list (head) */

gLink gRemove(gLink head, char *name);
/* removes game from a list, searching for its name */

pGame gSearch(gLink head, char *name);
/* search for game in list, by its name */

int gHash(char *v);
/* calculates the hash's list index where the game is */

gLink* gInit(gLink *hash);
/* initiates the hashtable with NULL pointers */

pGame gHTsearch(gLink *hash, char *name);
/* search for a game in hashtable */

void gHTinsert(gLink *hash, pGame game);
/* insert a game in hashtable */

void gHTdelete(gLink *hash, char *name);
/* delete a game from hashtable */

void freeGame(pGame g);
/* frees all the memory allocated for a game */

#endif
