#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "team.h"

/*Creates a team and returns its pointer.*/
team create_team(char * name)
{
    /*create team pointer*/
    team new_team;
    new_team = (team) can_fail_malloc(sizeof(struct team));
    
    /*allocate memory and assign name*/
    new_team->name = (char *)can_fail_malloc(sizeof(char)*(strlen(name) + 1));
    strcpy(new_team->name, name);
    
    /*assign score*/
    new_team->score = 0;

    return new_team;
}

/*Frees a given team structure.*/
void free_team(team team)
{
    free(team->name);
    free(team);
}

/*Increases score of a given team.*/
void inc_score(team team)
{
    team->score++;
}

/*Decreases the score of a given team.*/
void dec_score(team team)
{
    team->score--;
}

/*Prints a given team structure.*/
void print_team(team team, int NL)
{
    printf("%d * %s\n", NL, team->name);
}