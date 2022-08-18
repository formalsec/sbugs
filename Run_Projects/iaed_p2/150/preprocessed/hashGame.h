#ifndef _HASHGAME_
#define _HASHGAME_

#include "Game.h"
#include "hashTeam.h"


/****** structure ******/

typedef struct GAMEnode {
    Game *game;
    struct GAMEnode *next;
}*GAMElink;


/***************** prototypes ****************/

/* Initializes Games hashtable. */
GAMElink * GAMEinit();

/* Inserts a game in the hashtable. */
void GAMEinsert(Game * game, GAMElink * Games);

/* Searches for a game in the hashtable. */
Game * GAMEsearch(char * name, GAMElink * Games);

/* Deletes a game from the hashtable. */
void GAMEdelete(char * name, GAMElink * Games);

/* Frees all memory attached to the hashtable. */
void GAMESfree(GAMElink * Games);


#endif