#ifndef TEAMS
#define TEAMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"
#include "structs.h"

/*function prototypes*/

team create_team();

void destroy_team(team t);

node_teams create_node_team(team new_team);

node_teams * push_team(node_teams * head, team t);

node_teams * destroy_teams(node_teams * head);

node_teams * find_team(node_teams **teams_table);

char * get_team_name(node_teams *team);

node_teams * get_prev_team(node_teams *team);

int get_wins(node_teams *team);

void give_win(node_teams *team);

void take_win(node_teams *team);

int compare_names(const void *team1, const void *team2);

#endif