#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"

/******************************************************
*---------------------MAIN FUNCTION-------------------*
******************************************************/

int main(){

	char command;
	int NL = 1; /*this is a counter that represents the
	line number of the input command that originated
	a certain output*/

	h_t_ordered_list *lst = init_list(); /*initialization of the 
	list that saves the games by order of input*/

	list_names *head_lst_names = NULL; /*initializes the 
	list_names head NULL*/

	hash_table_teams *team_ht;
	hash_table_games *game_ht; 
	team_ht = create_ht_team(TABLE_SIZE); /*table of 
	pointers to list_teams*/
	game_ht = create_ht_game(TABLE_SIZE); /*table of 
	pointers to list_games*/

	while ((command = getchar()) != EOF){
		
		switch(command){

		default:
			break;

		case 'a' : 
			/*Function responsible for executing the command: a*/
			new_game(game_ht, team_ht, lst, NL);
			NL++;
			break; 
		
		case 'l' : 
			/*Function responsible for executing the command: l*/
			list_all_games(lst, NL);
			NL++;
			break; 

		case 'p' : 
			/*Function responsible for executing the command: p*/
			search_game(game_ht, NL);
			NL++;
			break;
		
		case 'r' : 
			/*Function responsible for executing the command: r*/
			delete_game(game_ht, team_ht, lst, NL);
			NL++;
			break; 

		case 's' : 
			/*Function responsible for executing the command: s*/
			change_score(game_ht, team_ht, NL);
			NL++;
			break; 

		case 'A' :
			/*Function responsible for executing the command: A*/
			new_team(team_ht, NL);
			NL++;
			break;


		case 'P' :
			/*Function responsible for executing the command: P*/
			search_team(team_ht, NL);
			NL++;
			break;

		case 'g' : 
			/*Function responsible for executing the command: g*/
			find_winners(team_ht, head_lst_names, NL);
			NL++;
			break; 

		case 'x':
			/*Function responsible for executing the command: x*/
			command_x(game_ht, team_ht, lst);
			return 0;
		}
	}
	
	return 0;
}