#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"

/* Makes a team with the given name.*/
team * mk_team(char * name) {
	team * new_team = can_fail_malloc(sizeof(team));

	/* Copies the name. */
	new_team->name = can_fail_malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new_team->name, name);
	/* Resets the number of wins. */
	new_team->wins = 0;

	return new_team;
}

/* Compares the names of two teams.*/
int team_cmp(const void * a, const void * b) {
	team * team_a = *(team **)a;
	team * team_b = *(team **)b;

	return strcmp(team_a->name, team_b->name);
}

/* Frees the memory associated with a team. */
void free_team(team * tm) {
	free(tm->name);
	free(tm);

	return;
}
