#ifndef _GAME_
#define _GAME_

#include "Team.h"

/* Structure representing a game */
typedef struct Game
{
    char *name;
    Team *team1;
    Team *team2;
    unsigned int score[2];
    unsigned int id;
    int isDeleted;
} Game;

/* Creates a new game */
Game *newGame(unsigned int id, unsigned int score[], Team *team1,
                Team *team2, char *name);

/* Frees the allocated memory of the team */
void freeGame(Game *game);

#endif