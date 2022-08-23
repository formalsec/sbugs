#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "teams.h"
#include "games.h"
#include "hash_tables.h"

/*function prototypes*/

void init_program(node_games **head_games, node_teams **head_teams, 
                node_games **games_table, node_teams **teams_table);

void add_game(node_games **head_games, node_games **games_table, 
            node_teams **teams_table, int l_count);

void search_game(node_games **games_table, int l_count);

void add_team(node_teams **head_teams, node_teams **teams_table, int l_count);

void search_team(node_teams **teams_table, int l_count);

void list_games(node_games **head_games, int l_count);

void delete_game(node_games **head_games, node_games **games_table, int l_count);

void change_score(node_games **games_table, int l_count);

void list_most_wins(node_teams **head_teams, int l_count);

void end_program(node_games **head_games, node_teams **head_teams);

#endif