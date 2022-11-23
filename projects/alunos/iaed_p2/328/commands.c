#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"

/*------------------COMMANDS FUNCTION----------------*/

/* a */
/*Adds a new game to the system*/
void new_game(hash_table_games *game_ht, hash_table_teams *team_ht, h_t_ordered_list *lst, int NL){

	char name[MAX_JOGO_EQUIPA], team1[MAX_JOGO_EQUIPA], team2[MAX_JOGO_EQUIPA];
	char *pName = name, *pTeam1 = team1, *pTeam2 = team2;
    int score1, score2;
	list_games *g;
    list_teams *l, *ll;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", name, team1, team2, &score1, &score2);

	/*Searches for a game in the hash table, if it finds it returns the game, if not returns NULL*/
    if((g = search_game_aux(game_ht, pName)) != NULL){
        printf("%d Jogo existente.\n", NL);
        return;
    }
	
	/*Searches for a team in the hash table, if it finds it returns the team, if not returns NULL*/
	if(((l = search_team_aux(team_ht, pTeam1)) == NULL) || ((ll = search_team_aux(team_ht, pTeam2)) == NULL)){
		printf("%d Equipa inexistente.\n", NL);
        return;
	}
	
	/*Inserts a game in the hash table*/
    g = insertBegin_games(game_ht, pName, pTeam1, pTeam2, score1, score2);
	
	/*Insert a game at the end of the list, this way, that same list is
	ordered by the order of input*/
	insertEnd_list(lst, g);

	/*If the score of team1 is higher than the score of team2, the number of victories of team1 increases*/
	if(score1 > score2){
		l->victories++;
	}

	/*If the score of team2 is higher than the score of team1, the number of victories of team2 increases*/
	if(score1 < score2){
		ll->victories++;
	}
} 

/* l */
/*Lists all games in the order they were entered*/
void list_all_games(h_t_ordered_list *lst, int NL){

	/*Prints all the games (characteristics) of the list*/
	print_list(lst, NL);
}

/* p */
/*Search for a certain game*/
void search_game(hash_table_games *game_ht, int NL){

	list_games *g;
	char name[MAX_JOGO_EQUIPA], *pName = name;

	scanf(" %[^:\n]\n", name);

	/*Searches for a game in the hash table, if it finds it returns the game, if not returns NULL*/
	if((g = search_game_aux(game_ht, pName)) != NULL){ 
		printf("%d %s %s %s %d %d\n", NL, g->name, g->team1, g->team2, g->score1, g->score2);
		return;
	}

	printf("%d Jogo inexistente.\n", NL);
}

/* r */
/*Removes a certain game*/
void delete_game(hash_table_games *game_ht, hash_table_teams *team_ht, h_t_ordered_list *lst, int NL){

	list_games *g;
	char name[MAX_JOGO_EQUIPA], *pName = name;

	scanf(" %[^:\n]\n", name);

	/*Searches for a game in the hash table, if it finds it returns the game, if not returns NULL*/
	if((g = search_game_aux(game_ht, pName)) != NULL){ 

		/*If the game no longer exists, none of the teams involved must have a win associated with this game,
		so the score must be changed*/
		change_score_aux(g, team_ht, 0, 0);

		/*Removes the game with a certain name from the list*/
		remove_list(lst, pName);

		/*Deletes the game from the hash table*/
		delete_game_aux(game_ht, pName);

		return;
	}

	printf("%d Jogo inexistente.\n", NL);
}

/* s */
/*Changes the score of a certain game*/
void change_score(hash_table_games *game_ht, hash_table_teams *team_ht, int NL){

	char name[MAX_JOGO_EQUIPA], *pName = name;
    int score1, score2;
	list_games *g;

	scanf(" %[^:\n]:%d:%d\n", name, &score1, &score2);

	/*Searches for a game in the hash table, if it finds it returns the game, if not returns NULL*/
	if((g = search_game_aux(game_ht, pName)) == NULL){
		printf("%d Jogo inexistente.\n", NL);
		return;
	}

	/*Changes the score of a certain game*/
	change_score_aux(g, team_ht, score1, score2);
}

/* A */
/*Adds a new team to the system*/
void new_team(hash_table_teams *team_ht, int NL){

	list_teams *l;
	char name[MAX_JOGO_EQUIPA], *pName = name;

	scanf(" %[^:\n]\n", name);

	/*Searches for a team in the hash table, if it finds it returns the team, if not returns NULL*/
	if((l = search_team_aux(team_ht, pName)) == NULL){

		/*Inserts a team in the hash table*/
		insertBegin_teams(team_ht, pName);

		return;
	}
	
	printf("%d Equipa existente.\n", NL);
}

/* P */
/*Search for a certain team*/
void search_team(hash_table_teams *team_ht, int NL){

	list_teams *l;
	char name[MAX_JOGO_EQUIPA], *pName = name;

	scanf(" %[^:\n]\n", name);

	/*Searches for a team in the hash table, if it finds it returns the team, if not returns NULL*/
	if((l = search_team_aux(team_ht, pName)) != NULL){ 
		printf("%d %s %d\n", NL, l->name, l->victories);
		return;
	}

	printf("%d Equipa inexistente.\n", NL);
}

/* g */
/*Finds the teams that have won most games and lists them in 
lexicographic order (from the team name)*/
void find_winners(hash_table_teams *team_ht, list_names *head_lst_names, int NL){

	int i, j, most_vict = 0;
	list_teams *temp, *aux;

	/*This cycle serves to find the greatest number of victories of a team in the system*/
	for(i = 0; i < team_ht->size; i++){

		temp = team_ht->table[i];

		while(temp != NULL){

			if(temp->victories > most_vict)
				most_vict = temp->victories;

			temp = temp->next;
		}
	}

	/*This cycle serves to find and put in a linked list all the teams that have the 
	same victory number as the one discover above*/
	for (j = 0; j < team_ht->size; j++){

		aux = team_ht->table[j];

		while (aux != NULL){

			if(aux->victories == most_vict)
				head_lst_names = insert_name_list(head_lst_names, aux->name);
			
			aux = aux->next;
		}
	}

	/*If there aren't any teams the program shoudn't print anything*/
	if(head_lst_names != NULL)
		printf("%d Melhores %d\n", NL, most_vict);
	
	/*Prints all the teams names of the list*/
	print_list_names(head_lst_names, NL);
}

/* command_x */
/*Frees the hashtables*/
void command_x(hash_table_games *game_ht ,hash_table_teams *team_ht, h_t_ordered_list *lst) {

    int i, j;
	list_teams *list, *temp;
    list_games *g, *aux;
	ordered_list_g head_aux = lst->head;
	
	/*This cycle frees the team hash table and its elements*/
	if(team_ht != NULL){

		for(i=0;i<team_ht->size;i++){

			list=team_ht->table[i];

			while(list != NULL){

				temp = list;
				list = list->next;
				free(temp->name);
				free(temp);
			}
		}

		free(team_ht->table);
		free(team_ht);
	}
	
	/*This cycle frees the game hash table and its elements*/
    if(game_ht != NULL){

		for(j = 0; j < game_ht->size; j++){

        	g = game_ht->table[j];

       		while(g != NULL){

        		aux = g;
            	g = g->next;
            	free(aux->name);
            	free(aux->team1);
            	free(aux->team2);
            	free(aux);
        	}
    	}

    	free(game_ht->table);
    	free(game_ht);
	}

	/*This cycle frees the linked list*/
	while(head_aux != NULL){
		
		head_aux = lst->head->next;
		free(lst->head);
		lst->head = head_aux; 
	}

	free(lst);
}