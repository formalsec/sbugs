#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"


Team new_team(const char *team_name) {
	Team new_team = malloc(sizeof(struct team));

	new_team->matches_won = 0;
	new_team->name = malloc(sizeof(char) * (strlen(team_name) + 1));

	strcpy(new_team->name, team_name);
	
	return new_team;
}


void free_team(Team t) {
	if (t) {
		free(t->name);
		free(t);
	}
}

