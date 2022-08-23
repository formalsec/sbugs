#ifndef GAMES
#define GAMES

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "teams.h"
#include "lists.h"
#define MAX_GAME_NAME 1024

typedef struct {
    char *name;
    team *team1, *team2;
    short score1, score2;
} game;

void del_game(void *);
int cmp_game_str(void *, void *);
int cmp_game_nds(void *, void *);
void print_game(game *, int);
void print_targets(t_node *, short, int);

#endif