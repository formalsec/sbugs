#ifndef TEAM_H
#define TEAM_H

#include "structs.h"

orderedTeams * pushTeam(orderedTeams * head, Team * team);

void printTeams(orderedTeams * head, int cmd_count, int maxWins);

/* function that frees all orderedGames nodes in the end of the program so theres no memory leak */
orderedTeams * destroyTeams(orderedTeams * head);

void updateMaxWins(orderedTeams * head, int * maxWins);

#endif
