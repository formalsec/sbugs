#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include "game_list.h"

/* Makes a new game node. */
game_node * mk_game_node(game * gm) {
	game_node * node = can_fail_malloc(sizeof(game_node));

	node->gm = gm;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

/* Frees a node in a game list. */
void free_game_node(game_node * node) {
	free_game(node->gm);
	free(node);

	return;
}

/* Makes a new game list. */
game_list * mk_game_list() {
	game_list * lst = can_fail_malloc(sizeof(game_list));

	lst->head = NULL;
	lst->last = NULL;

	return lst;
}

/* Adds a game to a game list. */
game_node * add_game_list(game_list * lst, game * gm) {
	game_node * node = mk_game_node(gm);

	node->prev = lst->last;
	if (lst->last)
		lst->last->next = node;
	else
		lst->head = node;

	lst->last = node;

	return node;
}

/* Prints a game list. */
void print_game_list(int NL, game_list * lst) {
	game_node * node = lst->head;

	while (node) {
		print_game(NL, node->gm);
		node = node->next;
	}

	return;
}

/* Removes a node from a game list. */
void rm_game_list(game_list * lst, game_node * node) {
	if (node->prev)
		node->prev->next = node->next;
	else
		lst->head = node->next;

	if (node->next)
		node->next->prev = node->prev;
	else
		lst->last = node->prev;

	free_game_node(node);
	return;
}

/* Frees the memory associated with a game list. */
void free_game_list(game_list * lst) {
	game_node * node = lst->head, * next;

	while (node) {
		next = node->next;
		free_game_node(node);
		node = next;
	}
	free(lst);

	return;
}