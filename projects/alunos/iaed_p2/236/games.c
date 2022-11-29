#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"
/*hashing func from hash.c*/
unsigned int hash(char *name);

/*
creates new game
input: name(char*), team_name1(char*), team_name2(char*), score1(int), score2(int)
output: new_game(*game)
*/
game *newGame(char *name, char *team_name1, char *team_name2, int score1, int score2){
	game *new_game = can_fail_malloc(sizeof(game));
	new_game->name = can_fail_malloc(strlen(name) * sizeof(char) + 1);
	new_game->team1 = can_fail_malloc(strlen(team_name1) * sizeof(char) + 1);
	new_game->team2 = can_fail_malloc(strlen(team_name2) * sizeof(char) + 1);
	new_game->score1 = can_fail_malloc(sizeof(int));
	new_game->score2 = can_fail_malloc(sizeof(int));
	strcpy(new_game->name, name);
	strcpy(new_game->team1, team_name1);
	strcpy(new_game->team2, team_name2);
	*new_game->score1 = score1;
	*new_game->score2 = score2;
	return new_game;
}
/*
inserts a game to the hashtable
input: hash table(*game[]), new_game(*game)
output: none
*/
void insertGame(game *hash_table[], game *new_game){
	int index = hash(new_game->name);
	new_game->next = hash_table[index];
	hash_table[index] = new_game;
}
/*
finds a game
input: hash table(*game[]), name(*char)
output: tmp(*game)
*/
game *findGame(game *hash_table[], char *name){
	int index = hash(name);
	game *tmp = hash_table[index];
	while(tmp!=NULL && strncmp(tmp->name, name, MAX_NAME)!=0){
		tmp = tmp->next;
	}
	return tmp;
}
/*
prints a game
input: single game(*game[]), NL(int)
output: none
*/
void printSingleGame(game *single_game, int NL){
	printf("%d %s %s %s %d %d\n", 
	NL,
	single_game->name,
	single_game->team1,
	single_game->team2,
	*single_game->score1,
	*single_game->score2
	);
}
/*
deletes a game from the hash table
input: hash table(*game[]), name(*char)
output: none
*/
void deleteGame(game *hash_table[], char *name){
	int index = hash(name);
	game *tmp = hash_table[index];
	game *prev = NULL;
	while(tmp!=NULL && strncmp(tmp->name, name, MAX_NAME)!=0){
		prev = tmp;
		tmp = tmp->next;
	}
	if(tmp==NULL) return;
	if(prev==NULL) hash_table[index] = tmp->next;
	else prev->next = tmp->next;
	free(tmp->name);
	free(tmp->team1);
	free(tmp->team2);
	free(tmp->score1);
	free(tmp->score2);
	free(tmp);
}
/*
initializes the hash table
input: hash table(*game[])
output: none
*/
void initGameHashTable(game *hash_table[]){
	int i;
	for (i = 0; i < TABLE_SIZE; ++i) hash_table[i] = NULL;
}
/*
frees memory
input: hash table(*game[])
output: none
*/
void freeGameHashTable(game *hash_table[]){
	int i;
	game *tmp, *current;
	for (i = 0; i < TABLE_SIZE; ++i){
		current = hash_table[i];
		while(current!=NULL){
			tmp = current;
			current = tmp->next;
			free(tmp->name);
			free(tmp->team1);
			free(tmp->team2);
			free(tmp->score1);
			free(tmp->score2);
			free(tmp);
		}
	}
}
