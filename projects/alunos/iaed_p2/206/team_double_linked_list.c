#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team_double_linked_list.h"

Team_List *init_team_list() {

	Team_List *TL = can_fail_malloc(sizeof(Team_List)); 
	TL->head = TL->last = NULL;
	return TL;
}

void add_last_team_list(Team_List *TL, Team team) {

	Team_Node *new_team_node = can_fail_malloc(sizeof(Team_Node));
	new_team_node->previous = TL->last;
	new_team_node->next = NULL;
	new_team_node->team = can_fail_malloc(sizeof(struct team_node));
	new_team_node->team->name = can_fail_malloc(sizeof(char) * (strlen(team->name) + 1));
	new_team_node->team = team;

	if (TL->last) {
		TL->last->next = new_team_node;
	} else {
		TL->head = new_team_node;
	}

	TL->last = new_team_node;
}

int length_team_list(Team_List *TL) {

	int n_teams = 0;
	Team_Node *aux_team_node = TL->head;

	while (aux_team_node != NULL) {
		n_teams++;
		aux_team_node = aux_team_node->next;
	}

	return n_teams;
}

void free_team_node(Team_Node *team_node) {

	free(team_node->team->name);
	free(team_node->team);
	free(team_node);
}

void free_teams_list(Team_List *TL) {

	while (TL->head != NULL) {
		Team_Node *aux_team_node = TL->head->next;
		free_team_node(TL->head);
		TL->head = aux_team_node;
	}
	
	free(TL);
}