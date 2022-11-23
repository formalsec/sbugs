#ifndef _HASHTABLEGAME_
#define _HASHTABLEGAME_

#include "Game.h"

/* Structure representing hashtable of games. */
typedef struct hashtableG
{
    int size;
    int factor;
    Game **items;
} HTG;

/* Initializes hashtable */
HTG *newHTG(int factor, int size);

/* Inserts a game into the hashtable */
void insertHTG(HTG *table, Game *item);

/* Deletes a game from the hashtable */
void deleteHTG(HTG *table, Game *item);

/* Finds game on hashtable given its name */
Game *getGame(HTG *table, char *name);

/* Frees the allocated memory of the hashtable */
void freeHTG(HTG *table);

#endif