#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "teams.h"
#include "games.h"


int main(){
	char c;
	int NL = 0;
	Games * games_list = init_Glist();
	Teams * teams_list = init_Tlist();
	HashGames * hashtable_games = init_HGtable(DEFAULTSIZE);
	HashTeams * hashtable_teams = init_HTtable(DEFAULTSIZE);

	while ((c = getchar()) != 'x'){

		if (c != ' ' && c != ':' && c != '\n')
			NL += 1;

		switch(c){

			case 'a':
				new_game(games_list, hashtable_games, hashtable_teams, NL);
				break;

			case 'A':
				new_team(teams_list, hashtable_teams, NL);
				break;

			case 'l':
				show_all_games(games_list, NL);
				break;

			case 'p':
				lookfor_game(hashtable_games, NL);
				break;

			case 'P':
				lookfor_team(hashtable_teams, NL);
				break;

			case 'r':
				remove_game(games_list, hashtable_games, NL, hashtable_teams);
				break;

			case 's':
				change_game_score(hashtable_games, hashtable_teams, NL);
				break;

			case 'g':
				find_most_winning_teams(teams_list, NL);
				break;

		}
	}
	destroy_Glist(games_list);
	destroy_Tlist(teams_list);
	destroy_HTtable(hashtable_teams);
	destroy_HGtable(hashtable_games);

	return 0;
}










/* Nota: Projeto interessante, gostei do facto de sermos nos a criar nossas estruturas de dados. Da mais liberdade */