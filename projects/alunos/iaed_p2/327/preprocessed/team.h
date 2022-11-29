#ifndef TEAM_H
#define TEAM_H

#include <stdlib.h>

typedef struct {
	char * name;
	int wins;
} team;

#define team_name(t) (t->name)
#define team_eq(a, b) (strcmp(a, b) == 0)
#define team_wins(t) (t->wins)

/* Makes a team with the given name.*/
team * mk_team(char * name);
/* Compares the names of two teams.*/
int team_cmp(const void * t1, const void * t2);
/* Frees the memory associated with a team. */
void free_team(team * tm);

#endif