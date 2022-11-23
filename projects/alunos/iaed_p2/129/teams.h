#ifndef teams_h
#define teams_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TEAM_TABLE_SLOTS 1009
#define LEN_TOP_WINNERS_INIT 10
#define MAX_TEAM_NAME_LEN 1023

typedef struct team{
    char *name;
    int won_games;

}team;

typedef struct team_node{
    struct team *team;
    struct team_node *next_node;
    struct team_node *previous_node;

}team_node;

typedef struct team_table{
    char **top_winners_names;
    int len_top_winners;
    int max_no_wins;
    struct team_node *table[TEAM_TABLE_SLOTS];

}team_table;

team_table * init_teams();


int hash_team(char *name);

void push_team(team_table *teams, team *team);

void new_team(team_table *teams, char *name);

team * get_team(team_table *teams, char *name);

char * get_team_name(team *team);

int same_team(team *team_1, team *team_2);

void update_team_wins(team *team, int value);

void print_team(team *team);

int get_max_win_number(team_table *teams);

int compare_names(const void *pointer_1, const void *pointer_2);

char ** get_top_winners_names(team_table *teams);

void free_teams(team_table *teams);


#endif 