#ifndef GAME_H
#define GAME_H

#include "team.h"

typedef struct {
	char * name;
	team * team1, * team2;
	int score1, score2;
} game;

/* Makes a game with the given name, teams and score.*/
game * mk_game(char * name, team * team1, team * team2, int score1, int score2);
/* Changes a game's score. */
void set_game_score(game * gm, int score1, int score2);
/* Prints a game's name, teams and score. */
void print_game(int NL, game * gm);
/* Frees the memory associated with a game. */
void free_game(game * gm);

#endif
