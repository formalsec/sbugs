#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"
/*hashing func from hash.c*/
unsigned int hash(char *name);

/*
creates new team
input: team's name(*char)
output: new_team(*team)
*/
team *newTeam(char *team_name){
	team *new_team;
	new_team= can_fail_malloc(sizeof(team));
	new_team->name = can_fail_malloc(strlen(team_name) * sizeof(char) + 1);
	strcpy(new_team->name, team_name);
	new_team->wins = 0;
	return new_team;
}
/*
inserts a team to the hashtable
input: hash table(*team[]), new_team(*team)
output: none
*/
void insertTeam(team *hash_table[], team *new_team){
	int index = hash(new_team->name);
	new_team->next = hash_table[index];
	hash_table[index] = new_team;
}
/*
finds a team
input: hash table(*team[]), name(*char)
output: team(*team)
*/
team *findTeam(team *hash_table[], char *name){
	int index = hash(name);
	team *tmp = hash_table[index];
	while(tmp!=NULL && strncmp(tmp->name, name, MAX_NAME)!=0){
		tmp = tmp->next;
	}
	return tmp;
}
/*
initializes the hash table
input: hash table(*team[])
output: none
*/
void initTeamHashTable(team *hash_table[]){
	int i;
	for (i = 0; i < TABLE_SIZE; ++i) hash_table[i] = NULL;
}
/*
frees memory
input: hash table(*team[])
output: none
*/
void freeTeamHashTable(team *hash_table[]){
	int i;
	team *tmp, *current;
	for (i = 0; i < TABLE_SIZE; ++i){
		current = hash_table[i];
		while(current!=NULL){
			tmp = current;
			current = tmp->next;
			free(tmp->name);
			free(tmp);
		}
	}
}
