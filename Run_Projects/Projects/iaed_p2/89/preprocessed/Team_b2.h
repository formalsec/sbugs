#ifndef TEAM_BASIC_H
#define TEAM_BASIC_H

#include <stdio.h>
#include <stdlib.h>

#include "strdup.h"

#define TRUE 1
#define FALSE 0

/* Key to organize the teams */
#define key(a) (a->name)
/* True if a, a string, is less then b, a string */
#define less(a,b) (strcmp(a,b) < 0)
/* True if a, a string, is equal to b, a string */
#define eq(a,b) (strcmp(a,b) == 0)

/* Structure Team, has a name and a number of wins */
typedef struct team* Team;
struct team{
    char *name;
    int wins;
};

/* Allocs memory for a team and its name. Returns a pointer to the Team Created */
Team Tnew(char *name);
/* Frees the memory for the Team's name and the Team */
void Tdelete(Team team);
/* Adds to_add to the team's wins. Returns the pointer the team */
Team TchangeWins(Team team, int to_add);

/* Returns the name of the team */
char* Tgetname(Team team);
/* Returns the wins of the team */
int Tgetwins(Team team);

/* Returns True if team1 is less than team2, regarding wins and then names */
int Tless(Team team1, Team team2);
#endif