#ifndef PRIMARY_FUNCTIONS_h
#define PRIMARY_FUNCTIONS_h

#include <stdio.h>
#include <string.h>

#include "games.h"
#include "teams.h"

#define MAX_STRING_LEN 1023

void add_game(unsigned int ln, game_table *games, team_table *teams);

void add_team(unsigned int ln, team_table *teams);

void change_game_score(unsigned int ln, game_table *games);

void find_game(unsigned int ln, game_table *games);

void find_team(unsigned int ln, team_table *teams);

void list_games(unsigned int ln, game_table *game_table);

void list_top_winners(unsigned int ln, team_table *teams);

void remove_game(unsigned int ln, game_table *games);

void free_all(game_table * games, team_table *teams);

char * get_string_until(char stop_char);

#endif