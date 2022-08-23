#ifndef COMMANDS_H
#define COMMANDS_H

#include "team_ht.h"
#include "game_ht.h"

#define MAX_STR 1024

/* Adds a new game. */
void cmd_a(int NL, game_list * game_lst, game_ht * games, team_ht * teams);
/* Adds a new team. */
void cmd_A(int NL, team_ht * teams);
/* Lists all games in the order they were inserted. */
void cmd_l(int NL, game_list * game_lst);
/* Searches for a game. */
void cmd_p(int NL, game_ht * games);
/* Searches for a team. */
void cmd_P(int NL, team_ht * teams);
/* Removes a game. */
void cmd_r(int NL, game_list * game_lst, game_ht * games);
/* Alters a game's score. */
void cmd_s(int NL, game_ht * games);
/* Finds the teams that have won the most games. */
void cmd_g(int NL, team_ht * teams);

#endif