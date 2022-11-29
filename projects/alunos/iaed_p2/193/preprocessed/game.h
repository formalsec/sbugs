#include "team.h"

#ifndef PROJECT2_GAME_H
#define PROJECT2_GAME_H

/*
 * Struct of the adt game
 */
typedef struct game {
    char *name; /*char array with the game's name*/
    Team **teams; /*Teams array*/
    int *scores; /*Scores array*/
} Game;

Game *createGame(char *name, Team **team, int *score);

void deleteGame(void *game);

int compareGameFunction(char *name, void *dataPointer);

void printGame(void *game, int *cmdCounter);

#endif
