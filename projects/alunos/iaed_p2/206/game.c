#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"

Game create_game(char *name, char *team1, char *team2, int score1, int score2) {

	Game new_game = can_fail_malloc(sizeof(struct game)); /* Aloca memoria necessaria para a estrutura Game. */
	new_game->name = can_fail_malloc(sizeof(char) * (strlen(name) + 1)); /* O +1 serve para incluir o \0. */
	new_game->team1 = can_fail_malloc(sizeof(char) * (strlen(team1) + 1));
	new_game->team2 = can_fail_malloc(sizeof(char) * (strlen(team2) + 1));

	strcpy(new_game->name, name);
	strcpy(new_game->team1, team1);
	strcpy(new_game->team2, team2);
	new_game->score1 = score1;
	new_game->score2 = score2;

	return new_game;
}