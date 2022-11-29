#ifndef FUNCTIONS
#define FUNCTIONS


/* Required imports */
#include "teams.h"
#include "games.h"
#include "hash.h"


/* Max number of characters given for each string */
#define MAX_STRING_SIZE 1024


/* -------------------------------------------------------------------------- */
/* ------------------------------- FUNCTIONS -------------------------------- */
/* -------------------------------------------------------------------------- */


/* Verifies if team is already in system */
int team_exists(hash_teams teams_tbl, char* team_name);


/* Verifies if game is already in system */
int game_exists(hash_games games_tbl, char* game_name);


/* Qsort comparison function for strings */
int string_cmp(const void *input_word1, const void *input_word2);


/* Creates a new match */
void adds_new_game(int lct, hash_teams teams_tbl,
                    hash_games games_tbl, dl_list games_lst);


/* Creates a new team */
void add_new_team(int lct, hash_teams teams_tbl, sl_list teams_lst);


/* Prints all games in system */
void lists_all_games(int lct, dl_list games_lst);


/* Searches for a match and prints it's values if found */
void search_game(int lct, hash_games games_tbl);


/* Searches for a team and prints it's name and score if found */
void search_team(int lct, hash_teams teams_tbl);


/* Removes match from system */
void deletes_game(int lct, hash_teams teams_tbl,
                    hash_games game_tbl, dl_list games_lst);


/* Changes final score of a match */
void changes_game_score(int lct, hash_teams teams_tbl, hash_games game_tbl);


/* Prints, in alphabetical order, all team's names that won the most games */
void prints_top_teams(int lct, sl_list teams_lst);


#endif
