#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "game.h"
#include "hash_table.h"

/* The maximum size of a team/game name */
#define MAX_STR 1024


/*____________MAIN FUNCTIONS____________*/


/* adds a game to the system */
Game_list* __a__(int nl, Game_node** head_game, Team_node** head_team, Game_list* game_list, int* max_victories){
	Game new_game;
	char aux[MAX_STR];
	char c;
	Team_node* team1, *team2;

	scanf(" %[^:\n]", aux);
	if (search_game(aux, head_game) != NULL){
		printf("%d Jogo existente.\n", nl);
		while ((c = getchar()) != '\n');				/* read until '\n', after an error */
		return game_list;
	}
	new_game.name = can_fail_malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(new_game.name, aux);

	scanf(":%[^:\n]", aux);
	if ((team1 = search_team(aux, head_team)) == NULL){
		printf("%d Equipa inexistente.\n", nl);
		free(new_game.name);							/* frees name, which has already been allocated but won't be used due to an error*/
		while ((c = getchar()) != '\n');
		return game_list;
	}
	new_game.team1 = team1;

	scanf(":%[^:\n]:%d:%d", aux, &new_game.score[0], &new_game.score[1]);
	if ((team2 = search_team(aux, head_team)) == NULL){
		printf("%d Equipa inexistente.\n", nl);
		free(new_game.name);
		return game_list;
	}
	new_game.team2 = team2;

	if (new_game.score[0] < new_game.score[1]){
		increase_vic(team2, max_victories);
		new_game.winner = 2;
	}
	else if (new_game.score[0] > new_game.score[1]){
		increase_vic(team1, max_victories);
		new_game.winner = 1;
	}
	else
		new_game.winner = 0;

	return insert_game_list(insert_game_table(new_game, head_game), game_list);	/* insert game table returns pointer to table node, */
}																				/* and is used by insert_game_list as an argument */

/* removes a game from the system */
Game_list* __r__(int nl, Game_node** head_game, Game_list* game_list, Team_list_node* team_list, int* max_victories){
	char aux[MAX_STR];
	Game_node* game;

	scanf(" %[^:\n]", aux);
	if (search_game(aux, head_game) == NULL){
		printf("%d Jogo inexistente.\n", nl);
		return game_list;
	}
	game = search_game(aux, head_game);

	if (game ->g.winner == 1)										/* if there was a winner in the game to be removed, verify if */
		decrease_vic(game ->g.team1, max_victories, team_list); 	/* max_victories has to be changed */
	else if (game ->g.winner == 2)
		decrease_vic(game ->g.team2, max_victories, team_list);

	game_list = delete_game_list(aux, game_list, head_game);
	delete_game_table(aux, head_game);
	return game_list;
}


/* change the score of a game */
void __s__(int nl, Game_node** head_game, Team_list_node* team_list, int* max_victories){
	char aux[MAX_STR];
	char c;
	Game_node* game_to_change;
	scanf(" %[^:\n]", aux);
	if ((game_to_change = search_game(aux, head_game)) == NULL){
		printf("%d Jogo inexistente.\n", nl);
		while ((c = getchar()) != '\n');								/* read until '\n', after an error */
		return;
	}
	scanf(":%d:%d", &(game_to_change ->g.score[0]), &(game_to_change ->g.score[1]));
	if (game_to_change ->g.winner == 1){
		if (game_to_change ->g.score[0] < game_to_change ->g.score[1]){ 		/* if the team that first won, now lost */
			game_to_change ->g.winner = 2;
			increase_vic(game_to_change ->g.team2, max_victories);
			decrease_vic(game_to_change ->g.team1, max_victories, team_list);
		}
		else if (game_to_change ->g.score[0] == game_to_change ->g.score[1]){	/* if now it is a draw */
			game_to_change ->g.winner = 0;
			decrease_vic(game_to_change ->g.team1, max_victories, team_list);
		}
	}
	else if (game_to_change ->g.winner == 2){
		if (game_to_change ->g.score[0] > game_to_change ->g.score[1]){
			game_to_change ->g.winner = 1;
			increase_vic(game_to_change ->g.team1, max_victories);
			decrease_vic(game_to_change ->g.team2, max_victories, team_list);
		}
		else if (game_to_change ->g.score[0] == game_to_change ->g.score[1]){
			game_to_change ->g.winner = 0;
			decrease_vic(game_to_change ->g.team2, max_victories, team_list);
		}
	}
	else {
		if (game_to_change ->g.score[0] > game_to_change ->g.score[1]){		/* if it was a draw, and now there is a winner */
			game_to_change ->g.winner = 1;
			increase_vic(game_to_change ->g.team1, max_victories);
		}
		else if (game_to_change ->g.score[0] < game_to_change ->g.score[1]){
			game_to_change ->g.winner = 2;
			increase_vic(game_to_change ->g.team2, max_victories);
		}
	}
}

/* finds a certain game, read from input, and prints his name, teams and score */
void __p__(int nl, Game_node** head){
	char aux[MAX_STR];
	Game_node* node;
	scanf(" %[^'\n']", aux);
	if ((node = search_game(aux, head)) == NULL)
		printf("%d Jogo inexistente.\n", nl);
	else
		printf("%d %s %s %s %d %d\n", nl, node ->g.name, node ->g.team1 ->t.name, node ->g.team2 ->t.name, node ->g.score[0], 
			   node ->g.score[1]);
}

/* prints all the games in the system, in the order they were inserted */
/* As the teams are always placed at the beginnig of the list, the function starts reading at the end of it, thus, 
 * games are listed in order of insertion */
void __l__(int nl, Game_list* game_list){
	Game_list_node* aux;
	if (game_list ->last == NULL)
		return;
	for (aux = game_list ->last; aux != NULL; aux = aux ->next){
		printf("%d %s %s %s %d %d\n", nl, aux ->g ->g.name, aux ->g ->g.team1 ->t.name, aux ->g ->g.team2 ->t.name,
				 aux ->g ->g.score[0], aux ->g ->g.score[1]);
	}
}


/*____________AUX FUNCTIONS____________*/


/* if team(argument), after a new win, is one of the teams with the most victories, change max_victories */
void increase_vic(Team_node* team, int* max_victories){
	int i;
	if ((i = (team ->t.victories ++) + 1) == max_victories[0])	/* if team's nr. of victories(i) (plus 1, because they just won another)*/
		max_victories[1]++;									  	/* is the same as max_victories, max_victories[1] increases one */
	else if (i > max_victories[0]){								/* if i is a new maximum, max_victories[0] is that number */
		max_victories[0] = i;									/* and max_victories[1] is 1, because team is the only with i victories */
		max_victories[1] = 1;
	}
}

/* if team(argument), before losing a win(game removed or score changed), was one of the teams 
 * with the most victories,  verify if max_victories has to be changed */
void decrease_vic(Team_node* team, int* max_victories, Team_list_node* team_list){
	int i;
	if ((i = team ->t.victories --) == max_victories[0]){				/* if team was one of the most victorious */
		if (max_victories[1] == 1){										/* if was the only with so many victories */
			max_victories[0]--;											/* maximum of victories decreases one */
			max_victories[1] = search_i_victories(i - 1, team_list);	/* search the number of teams with the new maximum of victories */
		}
		else
			max_victories[1]--;
	}
}

/* creates a pointer to a game list node (from a game given as argument) */
Game_list_node* new_game_list_node(Game_node* g){
	Game_list_node* x = can_fail_malloc(sizeof(Game_list_node));
	x ->g = g;
	x ->next = NULL;
	return x;
}

/* inserts a game at the beginning of the game list */
Game_list* insert_game_list(Game_node* g, Game_list* game_list){
	if (game_list -> head == NULL){										/* if the list is empty, both head and last point to */
		game_list -> head = game_list -> last = new_game_list_node(g);	/* the new game list node */
		return game_list;
	}
	game_list ->head ->next = new_game_list_node(g);
	game_list ->head = game_list ->head ->next;
	return game_list;
}

/* removes a game from the game list */
Game_list* delete_game_list(char* name, Game_list* game_list, Game_node** games_table){
	Game_node* node = search_game(name, games_table);
	Game_list_node* prev, *aux;
	for (aux = game_list ->last, prev = NULL; aux != NULL; prev = aux, aux = aux ->next){
		if (aux ->g == node){
			if (aux == game_list ->last)
				if (aux == game_list ->head)						/* if the list had only one value, head and last are NULL */
					game_list ->head = game_list ->last = NULL;
				else												
					game_list ->last = aux ->next;
			else if (aux == game_list ->head){
				prev ->next = NULL;
				game_list ->head = prev;
			}
			else
				prev ->next = aux ->next;
			free(aux);
			return game_list;
		}
	}
	return game_list;
}


/* counts the number of team with n_victories(argument) wins */
int search_i_victories(int n_victories, Team_list_node* team_list){
	int count = 0;
	Team_list_node* aux = team_list;
	for (; aux != NULL; aux = aux ->next){
		if (aux ->t ->t.victories == n_victories)
			count++;
	}
	return count;
}
