#ifndef GAMES
#define GAMES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "teams.h"
#include "hash_tables.h"

/*function prototypes*/

int read_score();

game create_game(node_teams **teams_table);

void destroy_game(game g);

node_games create_node_game(game new_game);

node_teams * get_winner(node_games *game);

node_games * push_game(node_games *head, game g);

void free_game(node_games *game);

node_games * destroy_games(node_games *head);

node_games * find_game(node_games **games_table);

void apply_score(node_games *game, int score1, int score2);

node_teams * get_t1(node_games *game);

node_teams * get_t2(node_games *game);

char * get_game_name(node_games *game);

char * get_name_t1(node_games *game);

char * get_name_t2(node_games *game);

int get_score1(node_games *game);

int get_score2(node_games *game);

node_games * get_next_list(node_games *node);

node_games * get_prev_list(node_games *node);

node_games * get_next_table(node_games *node);

node_games * get_prev_table(node_games *node);

void print_games_in_order(node_games *head, int line_counter);

void delete_swaps(node_games **head_games, node_games **games_table, 
                node_games *game_found);

#endif