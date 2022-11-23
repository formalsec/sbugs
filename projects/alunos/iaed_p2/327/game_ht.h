#ifndef GAME_HT_H
#define GAME_HT_H

#include "game_list.h"

/* Constants used in hash functions. */
#define HASH_NO_1 27183
#define HASH_NO_2 31415

typedef struct {
	int M, N;
	game_node ** ht;
} game_ht;

/* A hash function for games. */
int hash_game(char * name, int M);
/* Initializes a game hashtable. */
void game_ht_init(game_ht * games, int max);
/* Inserts a game into a hashtable. */
void game_ht_insert(game_ht * games, game_node * node, int can_expand);
/* Deletes a game from a hashtable. */
game_node * game_ht_delete(game_ht * games, char * name);
/* Searches for a game in a hashtable. */
game_node * game_ht_search(game_ht * games, char * name);
/* Espands a team hashtable. */
void game_ht_expand(game_ht * games);
/* Frees a game hashtable and the games within. */
void game_ht_free(game_ht * games);

#endif