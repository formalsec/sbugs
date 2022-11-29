#ifndef _TEAM_
#define _TEAM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Team structure.*/

/* A Team is defined by it's name and number of wins.*/
typedef struct team {
    char * name;
    int wins;
} * Team;

/* Prototypes of Team's basic operations.*/

Team InitTeam();

int Wins(Team t);

char * TeamName(Team t);

void SetTeamName(Team t, char name[]);

void WriteTeam(Team t, int NL);

void IncWins(Team t);

void DecWins(Team t);

void DestroyTeam(Team t);

#endif