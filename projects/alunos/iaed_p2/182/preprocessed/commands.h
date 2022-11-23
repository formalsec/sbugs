#ifndef COMMANDS_H
#define COMMANDS_H

#include "structures.h"

/* Main Commands */

void add_team(unsigned int NL, tlink** team_table);
void add_game(unsigned int NL, game** first_game, game** last_game, glink** game_table, tlink** team_table);
void list_games(unsigned int NL, game** first_game);
void search_team(unsigned int NL, tlink** team_table);
void search_game(unsigned int NL, glink** game_table);
void remove_game(unsigned int NL, game** first_game, game** last_game, glink** game_table, tlink** team_table);
void change_score(unsigned int NL, glink** game_table, tlink** team_table);
void best_teams(unsigned int NL, tlink** team_table);

/* Shutdown Auxiliary */

void free_memory(glink** game_table, tlink** team_table, game** first_game, game** last_game);
#endif
