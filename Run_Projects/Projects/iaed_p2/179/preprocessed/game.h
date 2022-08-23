#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#define NULLgame (NULL)

/* Structure for a game with 2 teams, each with a score */
struct game{
    char *name;
    char *team1;
    char *team2;
    unsigned int score1;
    unsigned int score2;
};

/* Definition for a pointer for the type "game" */
typedef struct game* Game;

/* Prototypes */

/* Creates a new game */
Game newGame(char *str1, char *str2, char *str3, int n1, int n2);
/* Frees the memory associated with the game given */
void freeGame(Game game);

#endif
