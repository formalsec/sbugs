#ifndef COMMANDS_H
#define COMMANDS_H

#include "OOP.h"
#include "game.h"
#include "team.h"
#include "hash_table.h"

#define NAME_DIM 1024 			/* Maximum dimension of a given name */
#define TEAM_DIM 1024 			/* Maximum dimension of a given name */

/* contact hash tables are instances of the hash table 'class' */
#define create_games_ht(SIZE) create_ht(SIZE, free_game, get_game_name)
#define create_teams_ht(SIZE) create_ht(SIZE, free_team, get_team_name)

/* handles game adding */
void cmd_a(ht *games,ht *teams);

/* handles team adding */
void cmd_A(ht *teams);

/* lists games in the same order as they were added */
void cmd_l(ht *games);

/* searches in ht *games for a requested game and print's it using print_game */
void cmd_p(ht *games);

/* prints a requested game*/
void print_game(void *v);

/* searches in ht *teams for a requested team and print's it */
void cmd_P(ht *teams);

/* removes a given game */
void cmd_r(ht *games, ht *teams);

/*edits the score of a given game */
void cmd_s(ht *games, ht *teams);

/*lists,lexicographically,the teams with more wins */
void cmd_g(ht *teams);

#endif