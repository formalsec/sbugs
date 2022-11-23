#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"

Game* newG(int id, char* name, char* team1, char* team2, int score1, int score2){
	Game* game = can_fail_malloc(sizeof(Game));
	game->id = id;

	game->name = can_fail_malloc(strlen(name)+1 * sizeof(char));
	strcpy(game->name, name);
	game->team1 = can_fail_malloc(strlen(team1)+1 * sizeof(char));
	strcpy(game->team1, team1);
	game->team2 = can_fail_malloc(strlen(team2)+1* sizeof(char));
	strcpy(game->team2, team2);
	game->score1 = score1;
	game->score2 = score2;
	return game;
}

void freeGame(Game* game){
	free(game->name);
	free(game->team1);
	free(game->team2);
	free(game);
}

Team* newT(char* name){
	Team* team = can_fail_malloc(sizeof(Team));

	team->name = can_fail_malloc(strlen(name)+1 * sizeof(char));
	strcpy(team->name, name);
	team->cont = 0; 
	return team;
}

void freeTeam(Team* team){
	free(team->name);
	free(team);
}