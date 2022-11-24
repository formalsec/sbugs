#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Team_b2.h"

/* Allocs memory for a team and its name. Returns a pointer to the Team Created */
Team Tnew(char *name){
    Team new = (Team) can_fail_malloc(sizeof(struct team));
    new->wins = 0;
    new->name = my_strdup(name);
    return new;
}

/* Frees the memory for the Team's name and the Team */
void Tdelete(Team team){
    free(team->name);
    free(team);
}

/* Adds to_add to the team's wins. Returns the pointer the team */
Team TchangeWins(Team team, int to_add){
    /* Wins aren't less than zero */
    if(Tgetwins(team) + to_add >= 0)
        team->wins += to_add;
    return team;
}

/* Returns the name of the team */
char* Tgetname(Team team){
    return team->name;
}

/* Returns the wins of the team */
int Tgetwins(Team team){
    return team->wins;
}

/* Returns True if team1 is less than team2, regarding wins and then names */
int Tless(Team team1, Team team2){
    if(Tgetwins(team1) < Tgetwins(team2))
        return TRUE;
    else if(Tgetwins(team1) == Tgetwins(team2))
        return !less(key(team1), key(team2));
    else
        return FALSE;
}