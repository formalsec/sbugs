#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MatchHashTable.h"
#include "TeamLinkedList.h"
#include "Team.h"
#include "Const.h"

/* Creates a Hash_Table */
Hash_Table_Match* mk_Match_Hash_Table(){

	int i;

	Hash_Table_Match* pHT = can_fail_malloc(sizeof(Hash_Table_Match));
	pHT->capacity = MATCH_HASH_SIZE;
	pHT->table = can_fail_malloc(sizeof(Hash_Node_Match) * pHT->capacity);

	for(i=0; i < pHT->capacity; i++){
		pHT->table[i] = NULL;
	}

	return pHT;
}


/* Adds element to the HashTable */
void addToMatchHashList(char *matchName, Team *team1, Team *team2, 
						int score1, int score2, 
						Hash_Table_Match *t, LinkedList_Team *ll_Teams, int index) {


	Hash_Node_Match *node = can_fail_malloc(sizeof(Hash_Node_Match));
	Match *match = can_fail_malloc(sizeof(Match));

	match->name = can_fail_malloc(sizeof(char) * (strlen(matchName) + 1));
	strcpy(match->name, matchName);
	match->team1 = team1->name;
	match->team2 = team2->name;
	match->score1 = score1;
	match->score2 = score2;

	node->match = match;

	if(t->table[index] != NULL)
		t->table[index]->prev = node;

	node->next = t->table[index];
	node->prev = NULL;

	t->table[index] = node;
	updateScoreValues(team1, team2, score1, score2, ll_Teams);
}


/* Free Match Hash Table */
void free_node_match(Hash_Node_Match *pHN){
	free(pHN->match->name);
	free(pHN->match);
}

void freeMatchHash(Hash_Table_Match *t){
	int i;
	Hash_Node_Match *temp;

	for(i = 0; i < t->capacity; i++){
		while(t->table[i]){
			temp = t->table[i]->next;	
			free_node_match(t->table[i]);		
			free(t->table[i]);
			t->table[i] = temp;
		}		
	}
	free(t->table);
	free(t);
}


