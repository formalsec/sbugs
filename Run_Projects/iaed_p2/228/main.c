#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "hash_table.h"

#define NAME_DIM 1024 			/* Maximum dimension of a given name/team */
#define HASH_DIM 572 			/* Dimension of the hash table (names/teams) */

int main(){
	char cmd; /* stores the command letter given by the user */

	ht *games = create_games_ht(HASH_DIM);
	ht *teams = create_teams_ht(HASH_DIM);
	while(1){
		scanf("%c", &cmd);
		switch(cmd){
			case 'a': /*adding a game*/
				cmd_a(games,teams);
				break;
			case 'A': /*adding a team*/
				cmd_A(teams);
				break;
			case 'l': /*list games*/
				cmd_l(games);
				break;
			case 'p': /*search game*/
				cmd_p(games);
				break;
			case 'P': /*search team*/
				cmd_P(teams);
				break;
			case 'r': /*delete a game*/
				cmd_r(games,teams);
				break;
			case 's': /*change the score of a game*/
				cmd_s(games,teams);
				break;
			case 'g': /*list teams win more wins in lexicographical order*/
				cmd_g(teams);
				break;
			case 'x': /*deallocates all the memory*/
				free_ht(teams);
				free_ht(games);
				return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}