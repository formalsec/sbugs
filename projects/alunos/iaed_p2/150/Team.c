#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"


/* New teams' number of wins. */
#define NULLWINS 0



/* Creates a new team and returns the team's pointer. */
Team * newTeam(char * str) {
    Team *new = NULL;
    char *name = NULL;
    int length = strlen(str) + 1;

    new = can_fail_malloc(sizeof(Team));
    name = can_fail_malloc(sizeof(char) * length),
    strcpy(name, str);

    new->name = name;
    new->wins = NULLWINS;

    return new;
}


/* Prints a team. */
void printTeam(Team * team) {
    printf("%s", team->name);
}


/* Frees all memory attached to a team. */
void destroyTeam(Team * team) {
    free(team->name);
    free(team);
}


