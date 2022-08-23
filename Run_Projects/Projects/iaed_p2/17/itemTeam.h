#ifndef _ITEMTEAM_H
#define _ITEMTEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct team* ItemTeam;

/* a team is made up of its name and the number of game it has won. */
typedef struct team{
	char* name;
	int numGamesWon;
}Team;

ItemTeam newItem_team(char* name);
void deleteItem_team(ItemTeam i);
void showItem_team(ItemTeam i);

#endif
