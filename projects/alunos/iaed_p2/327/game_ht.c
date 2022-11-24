#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdbool.h>
#include "game_ht.h"

/* A hash function for games. */
int hash_game(char * v, int M) {
	int h, a, b;

	a = HASH_NO_1;
	b = HASH_NO_2;

	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;

	return h;
}

/* Initializes a game hashtable. */
void game_ht_init(game_ht * games, int max) {
	int i;

	games->M = max;
	games->N = 0;
	games->ht = can_fail_malloc(games->M * sizeof(game_node*));

	for (i = 0; i < games->M; i++)
		games->ht[i] = NULL;

	return;
}

void game_ht_expand(game_ht * games);

/* Inserts a game into a hashtable. */
void game_ht_insert(game_ht * games, game_node * node, int can_expand) {
	char * name = game_name(node);
	int i = hash_game(name, games->M);

	while (games->ht[i] != NULL)
		i = (i+1) % games->M;

	games->ht[i] = node;
	
	if ((games->N)++ > games->M/2 && can_expand)
		game_ht_expand(games);

	return;
}

/* Deletes a game from a hashtable. */
game_node * game_ht_delete(game_ht * games, char * name) {
	int j, i = hash_game(name, games->M);
	game_node * aux, * v;

	while (games->ht[i] != NULL)
		if (game_eq(name, game_name(games->ht[i])))
			break;
		else i = (i+1) % games->M;

	if (games->ht[i] == NULL)
		return games->ht[i];
	/* Stores the item to be removed in aux. */
	aux = games->ht[i];

	games->ht[i] = NULL;
	games->N--;

	for (j = (i+1) % games->M; games->ht[j] != NULL; j = (j+1) % games->M, games->N--) {
		v = games->ht[j];
		games->ht[j] = NULL;
		game_ht_insert(games, v, true);
	}

	return aux;
}

/* Searches for a game in a hashtable. */
game_node * game_ht_search(game_ht * games, char * name) {
	int i = hash_game(name, games->M);

	while (games->ht[i] != NULL)
		if (game_eq(name, game_name(games->ht[i])))
			return games->ht[i];
		else
			i = (i+1) % games->M;
	return NULL;
}

/* Espands a team hashtable. */
void game_ht_expand(game_ht * games) {
	int i;
	game_node ** t = games->ht;

	game_ht_init(games, games->M * 2);
	for (i = 0; i < games->M/2; i++)
		if (t[i] != NULL)
			game_ht_insert(games, t[i], false);
		
	free(t);
}

/* Frees a game hashtable and the games within. */
void game_ht_free(game_ht * games) {
	free(games->ht);
	free(games);

	return;
}