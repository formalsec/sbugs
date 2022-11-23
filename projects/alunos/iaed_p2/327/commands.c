#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"

/* Adds a new game. */
void cmd_a(int line, game_list * game_lst, game_ht * games, team_ht * teams) {
	char name[MAX_STR], t1_name[MAX_STR], t2_name[MAX_STR];
	int score1, score2;
	team * team1, * team2;
	game * new_game;
	game_node * node;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
		name,
		t1_name,
		t2_name,
		&score1,
		&score2);

	team1 = team_ht_search(teams, t1_name);
	team2 = team_ht_search(teams, t2_name);
	if (game_ht_search(games, name)) {
		printf("%d Jogo existente.\n", line);
		return;
	} else if (!team1 || !team2) {
		printf("%d Equipa inexistente.\n", line);
		return;
	}

	new_game = mk_game(name, team1, team2, score1, score2);
	node = add_game_list(game_lst, new_game);
	game_ht_insert(games, node, true);
	return;
}

/* Adds a new team. */
void cmd_A(int line, team_ht * teams) {
	char name[MAX_STR];
	team * new_team;

	scanf(" %[^:\n]", name);
	if (team_ht_search(teams, name)) {
		printf("%d Equipa existente.\n", line);
		return;
	}

	new_team = mk_team(name);
	team_ht_insert(teams, new_team);
	return;
}

/* Lists all games in the order they were inserted. */
void cmd_l(int line, game_list * game_lst) {
	print_game_list(line, game_lst);
	return;
}

/* Searches for a game. */
void cmd_p(int line, game_ht * games) {
	char name[MAX_STR];
	game_node * node;

	scanf(" %[^:\n]", name);
	node = game_ht_search(games, name);
	if (node)
		print_game(line, node->gm);
	else
		printf("%d Jogo inexistente.\n", line);
	
	return;
}

/* Searches for a team. */
void cmd_P(int line, team_ht * teams) {
	char name[MAX_STR];
	team * t;

	scanf(" %[^:\n]", name);
	t = team_ht_search(teams, name);
	if (t)
		printf("%d %s %d\n", line, name, t->wins);
	else
		printf("%d Equipa inexistente.\n", line);
	
	return;
}

/* Removes a game. */
void cmd_r(int line, game_list * game_lst, game_ht * games) {
	char name[MAX_STR];
	game_node * node;

	scanf(" %[^:\n]", name);
	node = game_ht_delete(games, name);
	if (!node) {
		printf("%d Jogo inexistente.\n", line);
		return;
	}

	rm_game_list(game_lst, node);
	return;
}

/* Alters a game's score. */
void cmd_s(int line, game_ht * games) {
	char name[MAX_STR];
	int score1, score2;
	game_node * node;

	scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
	node = game_ht_search(games, name);
	if (node)
		set_game_score(node->gm, score1, score2);
	else
		printf("%d Jogo inexistente.\n", line);
	
	return;
}

/* Finds the teams that have won the most games. */

void cmd_g(int line, team_ht * teams) {
	team_ht_print_most_wins(line, teams);
	return;
}