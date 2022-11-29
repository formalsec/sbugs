#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "function_hashtable.h"
#include "team_hashtable.h"

void init_team_hashtable_table(Team_Hashtable *TH) {

	int i;
	TH->team_table = (Team *) can_fail_malloc(sizeof(Team) * TH->size);

	for (i = 0; i < TH->size; i++) {
		TH->team_table[i] = NULL;
	}
}

Team_Hashtable *init_team_hashtable(int team_hashtable_size) {

	Team_Hashtable *TH = can_fail_malloc(sizeof(struct team_hashtable));
	TH->size = team_hashtable_size;
	
	TH->count = 0;
	init_team_hashtable_table(TH);

	return TH;
}

void insert_team_hashtable(Team_Hashtable *TH, Team team) {

	int index = HASH(team->name, TH->size), position = index;

	if (TH->count > EXPANDING_SIZE(TH)) {
		expand_team_hashtable(TH);
	}

	while (TH->team_table[position] != NULL) {
		position = (index++) % (TH->size);
	}

	TH->team_table[position] = team;
	TH->count++;
}

void expand_team_hashtable(Team_Hashtable *TH) {

	int i, old_size = TH->size;
	Team *aux_team_table = TH->team_table;

	TH->size = (old_size * EXPAND_CONSTANT_VARIABLE);

	init_team_hashtable_table(TH);

	for (i = 0; i < EXPANDING_SIZE(TH); i++) {
		if (aux_team_table[i] != NULL) {
			insert_team_hashtable(TH, aux_team_table[i]);
		}
	}

	free(aux_team_table);
}

Team search_team_hashtable(Team_Hashtable *TH, char *name) {

	int index = HASH(name, TH->size), position = index;

	while (TH->team_table[position] != NULL) {
		if (strcmp(TH->team_table[position]->name, name) == 0) {
			return TH->team_table[position];
		}

		position = (index++) % (TH->size);
	}

	return NULL;
}

void free_team_hashtable_table(Team_Hashtable *TH, int index) {

	free(TH->team_table[index]->name);
	free(TH->team_table[index]);	
}

void free_teams_hashtable(Team_Hashtable *TH) {

	int i = 0;

	while(TH->team_table[i] != NULL) {
		free_team_hashtable_table(TH, i);
		i++;
	}
	
	free(TH->team_table);
	free(TH);
}