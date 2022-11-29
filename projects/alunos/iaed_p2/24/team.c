#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "team.h"

/* Creates a new team */
Team newTeam(char *name)
{
    Team team = (Team)can_fail_malloc(sizeof(struct team));

    team->name = copyString(name);
    team->victories = 0;

    return team;
}

/* Print a team */
void printTeam(Team team)
{
    printf("%s %d\n", team->name, team->victories);
}

/* Free the data of a team */
void freeTeam(Team team)
{
    free(team->name);
    free(team);
}