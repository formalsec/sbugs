#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team.h"
#include "hash_table.h"

/* The maximum size of a team/game name */
#define MAX_STR 1024

/*____________ MAIN FUNCTIONS ____________*/


/* Adds a team to the system */
Team_list_node* __A__(int nl, Team_node** head, Team_list_node* team_list){
	char aux[MAX_STR];
	Team new_team;
	scanf(" %[^\n]", aux);
	if (search_team(aux, head) != NULL){
		printf("%d Equipa existente.\n", nl);
		return team_list;
	}
	new_team.name = can_fail_malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(new_team.name, aux);
	new_team.victories = 0;

	return insert_team_list(insert_team_table(new_team, head), team_list);	/* insert team table returns pointer to table node, */
}																			/* and is used by insert_team_list as an argument */

/* finds a certain team, read from input, and prints his name and number of victories */
void __P__(int nl, Team_node** head){
	char aux[MAX_STR];
	Team_node* node;
	scanf(" %[^\n]", aux);
	if ((node = search_team(aux, head)) == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else
		printf("%d %s %d\n", nl, node ->t.name, node ->t.victories);
}

/* prints the teams with the most victories, orderes by name */
void __g__(int nl, int* max_victories, Team_list_node* team_list){
	Team_list_node* aux;
	if (team_list == NULL)
		return;	
	printf("%d Melhores %d\n", nl, max_victories[0]);
	for (aux = team_list; aux != NULL; aux = aux ->next){				/* team list is already ordered by name, so the function just */
		if (aux ->t ->t.victories == max_victories[0]){					/* finds and prints the teams with the most victories */
			printf("%d * %s\n", nl, aux ->t ->t.name);
		}
	}
}


/*____________ AUX FUNCTIONS ____________*/


/* creates a pointer to a team list node (from a team given as argument) */
Team_list_node* new_team_list_node(Team_node* t){
	Team_list_node* x = can_fail_malloc(sizeof(Team_list_node));
	x ->t = t;
	x ->next = NULL;
	return x;
}

/* inserts a team in the team list, ordered by name */
Team_list_node* insert_team_list(Team_node* team, Team_list_node* head){
	Team_list_node* aux, *prev;
	if (head == NULL)
		return new_team_list_node(team);
	for (aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux ->next){
		if (strcmp(aux ->t ->t.name, team ->t.name) > 0){					/* look for the position where the team will be put */ 
			if (aux == head){
				head = new_team_list_node(team);
				head ->next = aux;
				return head;
			}
			else{
				prev ->next = new_team_list_node(team);
				prev ->next ->next = aux;
				return head;
			}
		}
	}
	prev ->next = new_team_list_node(team);									/* if the cicle ends and the team hasnt yet been placed*/ 
	return head;
}