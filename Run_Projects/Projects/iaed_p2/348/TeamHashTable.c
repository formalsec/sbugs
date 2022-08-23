#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TeamHashTable.h"
#include "Const.h"

/* Creates a Hash_Table */
Hash_Table_Team* mk_Team_Hash_Table(){

	int i;

	Hash_Table_Team* pHT = malloc(sizeof(Hash_Table_Team));
	pHT->capacity = TEAM_HASH_SIZE;
	pHT->table = malloc(sizeof(Hash_Node_Team) * pHT->capacity);

	for(i=0; i < pHT->capacity; i++){
		pHT->table[i] = NULL;
	}

	return pHT;
}

/* Generates index to place new Match or Team in Hash Table - Taken from class' powerpoint*/
int hash_key(char *name, int capacity){
	int h = 0, a = HASH_DIV;

	for(; *name != '\0'; name++)
		h = (a*h + *name) % capacity;

	return h;
}

/* Adds element to the HashTable */
void addToTeamHashList(char *teamName, Hash_Table_Team *t, int index){

	Hash_Node_Team *node = malloc(sizeof(Hash_Node_Team));
	Team *team = malloc(sizeof(Team));

	team->name = malloc(sizeof(char) * (strlen(teamName) + 1));
	strcpy(team->name, teamName);
	team->gamesWon = 0;

	node->team = team;
	node->next = t->table[index];

	t->table[index] = node;
}

/* Free Team Hash Table */
void free_node_team(Hash_Node_Team *pHN){
	free(pHN->team->name);
	free(pHN->team);
}

void freeTeamHash(Hash_Table_Team *t){
	int i;
	Hash_Node_Team *temp;

	for(i = 0; i < t->capacity; i++){
		while(t->table[i]){
			temp = t->table[i]->next;			
			free_node_team(t->table[i]);
			free(t->table[i]);
			t->table[i] = temp;
		}		
	}
	free(t->table);
	free(t);
}

