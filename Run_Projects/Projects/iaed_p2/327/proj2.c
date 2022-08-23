#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

#define TEAM_HT_M 1033
#define GAME_HT_M 2029

int main() {
	char cmd;
	int line = 0;
	game_list * game_lst = mk_game_list();
	team_ht * teams = malloc(sizeof(team_ht));
	game_ht * games = malloc(sizeof(game_ht));

	team_ht_init(teams, TEAM_HT_M);
	game_ht_init(games, GAME_HT_M);

	do {
		line ++;
		cmd = getchar();

		switch (cmd) {
			case 'a': cmd_a(line, game_lst, games, teams); break;
			case 'A': cmd_A(line, teams); break;
			case 'l': cmd_l(line, game_lst); break;
			case 'p': cmd_p(line, games); break;
			case 'P': cmd_P(line, teams); break;
			case 'r': cmd_r(line, game_lst, games); break;
			case 's': cmd_s(line, games); break;
			case 'g': cmd_g(line, teams); break;
			case 'x': break;
		}

		getchar();
	} while (cmd != 'x');

	game_ht_free(games);
	free_game_list(game_lst);
	team_ht_free(teams);

	return EXIT_SUCCESS;
}