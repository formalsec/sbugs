#ifndef HASH_TABLES
#define HASH_TABLES

#include <string.h>
#include "structs.h"

#define M 1993 /*Mod to hash and table length*/

/*function prototypes*/

int sum_chars(char a[]);

int hash_team(node_teams *node);

int hash_game(node_games *node);

void insert_team(node_teams **table, node_teams *node);

void insert_game(node_games **table, node_games *node);

node_teams * in_table_teams(node_teams **table, node_teams *node);

node_games * in_table_games(node_games **table, node_games *node);

#endif
