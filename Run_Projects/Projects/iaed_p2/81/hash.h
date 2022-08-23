#ifndef HASH
#define HASH


/* Required imports */
#include <stdlib.h>
#include <stdio.h>
#include "teams.h"
#include "games.h"


/* -------------------------------------------------------------------------- */
/* ----------------------------- STRUCTURES --------------------------------- */
/* -------------------------------------------------------------------------- */


#define INITIAL_TABLE_SIZE 593


/* Struct that represents an hash table for teams */
typedef struct my_hash_teams {

    /* Pointer of team's node */
    sl_link *table;

    /* Max size of table */
    int max_size;

    /* Amount of nodes inside table */
    int current_size;

}* hash_teams;


/* Struct that represents an hash table for games */
typedef struct my_hash_games {

    /* Pointer of game's node */
    dl_link *table;

    /* Max size of table */
    int max_size;

    /* Amount of nodes inside table */
    int current_size;

}* hash_games;


/* -------------------------------------------------------------------------- */
/* -------------------------------- FUNCTIONS ------------------------------- */
/* -------------------------------------------------------------------------- */


/* Receives a string and returns it's hash code */
int get_hash_value(char* word, int table_size);


/* ------------------------------- TEAMS ------------------------------------ */


/* Creates hash table for teams */
hash_teams create_teams_hash_table(int table_size);


/* Inserts a team inside the hash table */
void insert_team_hash(hash_teams table, sl_link team_node);


/* Gets node's index which holds team's name. If not found, returns -1 */
int search_team_index_in_hash(hash_teams table, char* team_name);


/* Expands teams' hash table */
void expands_team_hash(hash_teams table);


/* Deletes hash table for teams, clearing all memory */
void destroy_teams_hash(hash_teams table);


/* ------------------------------- GAMES ------------------------------------ */


/* Creates hash table for games */
hash_games create_games_hash_table(int table_size);


/* Inserts a game inside the hash table */
void insert_games_hash(hash_games table, dl_link game_node);


/* Gets node's index inside table which holds game's name */
int search_game_index_in_hash(hash_games table, char* game_name);


/* Expands games' hash table */
void expands_games_hash(hash_games table);


/* Removes input game's node from the table */
void deletes_game_hash(hash_games table, int game_index);


/* Deletes hash table for games, clearing all memory */
void destroy_games_hash(hash_games table);


#endif
