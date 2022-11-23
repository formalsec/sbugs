#ifndef GAME_LIST_H
#define GAME_LIST_H

#include "game.h"

typedef struct _game_node {
	game * gm;
	struct _game_node * next, * prev;
} game_node;

typedef struct {
	game_node * head, * last;
} game_list;

#define game_name(node) (node->gm->name)
#define game_eq(a, b) (strcmp(a, b) == 0)

/* Makes a new game node. */
game_node * mk_game_node(game * gm);
/* Frees a node in a game list. */
void free_game_node(game_node * node);

/* Makes a new game list. */
game_list * mk_game_list();
/* Adds a game to a game list. */
game_node * add_game_list(game_list * lst, game * gm);
/* Prints a game list. */
void print_game_list(int NL, game_list * lst);
/* Removes a node from a game list. */
void rm_game_list(game_list * lst, game_node * node) ;
/* Frees the memory associated with a game list. */
void free_game_list(game_list * lst);

#endif
