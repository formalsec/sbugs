#ifndef _ITEMGAME_H
#define _ITEMGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct game* ItemGame;

/* a game is made up of its name, the names of the teams, and their scores. */
typedef struct game{
	char * name, * team1, * team2;
	int score1, score2;
}Game;

ItemGame newItem_game(char* name, char* team1, char* team2, int score1,
	                   int score2);
void deleteItem_game(ItemGame i);
void showItem_game(ItemGame i);

#endif
