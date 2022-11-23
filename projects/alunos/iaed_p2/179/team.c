#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "team.h"

Team newTeam(char *name, int n){
    Team team = can_fail_malloc((sizeof(struct team)));
    team->name = name;
    team->won = n;
    return team;
}

void freeTeam(Team team){
    free(team->name);
    free(team);
    team = NULLteam;
}
