#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team.h"

Team create_team(char *name) {

	Team new_team = can_fail_malloc(sizeof(struct team));
	new_team->name = can_fail_malloc(sizeof(char) * (strlen(name) + 1));

	strcpy(new_team->name, name);
	new_team->winnings = 0;

	return new_team;
}

