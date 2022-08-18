#ifndef TEAMS_H
#define TEAMS_H

/*
    structures
*/

typedef struct teams{
    int games_w;
    char *name;
    struct teams *next;
}teams;


/*
    funtions
*/

/*initialize the list of teams*/
void init_teams(teams **lst_teams, int size);
/*returns the new head of the list*/
teams* new_team(teams *team, char *name);
/*adds a victory to a certain team*/
void add_victory(teams **lst_teams, char *name);
/*remove a victory*/
void remove_victory(teams **lst_teams, char *name);
/*checks if a certain name already exits as a team*/
int look_team(teams **lst_teams, char *name);/*returns 1 if it does, 0 if it doesn t*/
/*insert a new team at the begining of the correct list*/
void insert_new_team(teams **lst_teams, teams *new);/*return the new head*/
/*get the poiter of a team with a given name*/
teams* get_team(teams **lst_teams,  char *name);
/*best teams*/
int most_wins(teams **lst_teams);
/*free the list of teams*/
void clear_the_teams(teams **lst_teams);


#endif