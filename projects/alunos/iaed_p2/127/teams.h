#ifndef TEAMS_H
#define TEAMS_H

/*----------------------------TEAM STRUCTURE---------------------------*/
/*team - structure that represents a team*/
typedef struct team1{
    char * name; /*team s name*/
    long int nr_wins; /*team s number of wins*/
    struct team1 *next; /*pointer to the next team*/

}team;

/*--------------Functions to manipulate team structure--------------*/

team *create_team(char * name);

/*--------------Functions to manipulate teams hash table--------------*/

void table_t_init(team **team_t, long int m);

team **add_team_to_table(team **teams_t, team *t, long int *max_len);

team **expand_t(team **teams_tab, long int *max_len);

team *search_t(char *team_name, team **teams_tab, long int m);

void destroy_team_st(team *last_team);

#endif /* TEAMS_H */
