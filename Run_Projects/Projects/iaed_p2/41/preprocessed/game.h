#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team.h"

typedef struct gm
{
    char * name;
    team team_1;
    team team_2;
    int score_1;
    int score_2;
}* game;

game create_game(char *, team, team, int, int);
void free_game(game);

#endif