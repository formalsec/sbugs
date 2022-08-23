#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

/* Makes a game with the given name, teams and score.*/
game * mk_game(char * name, team * team1, team * team2, int score1, int score2) {
	game * new_game = malloc(sizeof(game));

	/* Copies the name. */
	new_game->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new_game->name, name);

	/* Copies the team pointers. */
	new_game->team1 = team1;
	new_game->team2 = team2;

	/* Copies the game score. */
	new_game->score1 = score1;
	new_game->score2 = score2;

	/* Updates team wins. */
	if (score1 > score2)
		team1->wins ++;
	if (score2 > score1)
		team2->wins ++;

	return new_game;
}

/* Changes a game's score. */
void set_game_score(game * gm, int score1, int score2) {
	/* The diference between the old and new number of wins. */
	int dif1 = 0, dif2 = 0;

	/* Removes the old wins. */
	if (gm->score1 > gm->score2)
		dif1 --;
	if (gm->score2 > gm->score1)
		dif2 --;

	/* Adds the new wins. */
	if (score1 > score2)
		dif1 ++;
	if (score2 > score1)
		dif2 ++;

	/* Updates the number of wins. */
	gm->team1->wins += dif1;
	gm->team2->wins += dif2;

	/* Updates the game's score. */
	gm->score1 = score1;
	gm->score2 = score2;

	return;
}

/* Prints a game's name, teams and score. */
void print_game(int line, game * gm) {
	printf("%d %s %s %s %d %d\n",
		line,
		gm->name,
		gm->team1->name,
		gm->team2->name,
		gm->score1,
		gm->score2);

	return;
}

/* Frees the memory associated with a game. */
void free_game(game * gm) {
	/* Resets wins assiciated with the game. */
	set_game_score(gm, 0, 0);
	
	free(gm->name);
	free(gm);

	return;
}
