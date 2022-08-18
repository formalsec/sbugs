#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"


/* Frees all the memory allocated, and not yet freed, during the program */
void free_all(Team_node** teams, Game_node** games, Game_list* game_list, Team_list_node* team_list, int* max_victories){
	Game_list_node* aux1;
	Team_list_node* aux2;
	
	for (aux1 = game_list ->last; game_list ->last != NULL; aux1 = game_list ->last){	/* free games (list and hash table) */
		game_list ->last = game_list ->last ->next;
		delete_game_table(aux1 ->g ->g.name, games);
		free(aux1);
	}

	for (aux2 = team_list; team_list != NULL; aux2 = team_list){						/* free teams (list and hash table) */
		team_list = team_list ->next;
		delete_team_table(aux2 ->t ->t.name, teams);
		free(aux2);
	}
	free(teams);
	free(games);
	free(max_victories);
	free(game_list);
}

int main(){
	char c;
	int nl = 1;	/* number of the input's line */

	int* max_victories = calloc(2, sizeof(int));	/* array that holds, in the first position, the greatest number of victories that 
													 a team has and, in the second, the number of teams with that number of victories */

	Game_node** games_table = init_table_game();	/* hash table for games */
	Team_node** team_table = init_table_team();		/* hash table for teams */
	Game_list* game_linked_list = malloc(sizeof(Game_list_node*) * 2);
	Team_list_node* team_linked_list = NULL;
	game_linked_list ->head = NULL;
	game_linked_list ->last = NULL;
	

	
	while ((c = getchar()) != EOF){
		if (c == 'a')
			game_linked_list = __a__(nl++, games_table, team_table, game_linked_list, max_victories);
		else if (c == 'A')
			team_linked_list = __A__(nl++, team_table, team_linked_list);
		else if (c == 'l')
			__l__(nl++, game_linked_list);
		else if (c == 'p')
			__p__(nl++, games_table);
		else if (c == 'P')
			__P__(nl++, team_table);
		else if (c == 'r')
			game_linked_list = __r__(nl++, games_table, game_linked_list, team_linked_list, max_victories);
		else if (c == 's')
			__s__(nl++, games_table, team_linked_list, max_victories);
		else if (c == 'g')
			__g__(nl++, max_victories, team_linked_list);
		else if (c == 'x')
			break;
	}
	free_all(team_table, games_table, game_linked_list, team_linked_list, max_victories);
	return 0;
}