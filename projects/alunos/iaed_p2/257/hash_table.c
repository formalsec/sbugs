#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "game.h"
#include "hash_table.h"

/* size of both hash tables */
#define HASH_SIZE 11119


/* calculates the index, with a name(parameter), where the team/game will be placed in the hash table, and returns it */ 
int hash(char* name, int M){
	int h, a = 31415, b = 27183;
	for (h = 0; *name != '\0'; name++, a = a*b % (M - 1))
		h = (a*h + *name) % M;
	return h;
}

/* initializes the game hash table and returns its pointer */
Game_node** init_table_game(){
	int i;
	Game_node **games_table = can_fail_malloc(HASH_SIZE * sizeof(Game_node*));		/* creates pointer to the hash table */
	for (i = 0; i < HASH_SIZE; i++)
		games_table[i] = NULL;
	return games_table;
}

/* initializes the team hash table and returns its pointer */
Team_node** init_table_team(){
	int i;
	Team_node **team_table = can_fail_malloc(HASH_SIZE * sizeof(Team_node*));		/* creates pointer to the hash table */
	for (i = 0; i < HASH_SIZE; i++)
		team_table[i] = NULL;
	return team_table;
}

/* creates a pointer to a new game node, with a game given as an argument, and returns it */
Game_node* new_game_node(Game p_game){
	Game_node* x = can_fail_malloc(sizeof(Game_node));
	x ->g = p_game;
	x ->next = NULL;
	return x;
}

/* creates a pointer to a new game node, with a game given as an argument, and returns it */
Team_node* new_team_node(Team p_team){
	Team_node *x = can_fail_malloc(sizeof(Team_node));
	x ->t = p_team;
	x ->next = NULL;
	return x;
}

/* inserts a game(given as an argument) in the hash table, and returns a pointer of his node */
Game_node* insert_game_table(Game g, Game_node ** head){
	int i = hash(g.name, HASH_SIZE);						/* finds where the node has to be placed */
	Game_node* x = new_game_node(g);						/* creates the node */
	x->next = head[i];
	head[i] = x;
	return x;
}

/* inserts a team(given as an argument) in the hash table, and returns the node pointer */
Team_node* insert_team_table(Team t, Team_node ** head){
	int i = hash(t.name, HASH_SIZE);						/* finds where the node has to be placed */
	Team_node* x = new_team_node(t);						/* creates the node */
	x->next = head[i];
	head[i] = x;
	return x;
}

/* searches where a game(given as an argument) is placed and returns its node pointer. If the game doesn't exist returns NULL */
Game_node* search_game(char* name, Game_node** head){
	int i = hash(name, HASH_SIZE);
	Game_node* aux;
	for (aux = head[i]; aux != NULL; aux = aux->next){
		if (strcmp(name, aux->g.name) == 0)
			return aux;
	}
	return NULL;
}

/* searches where a team(given as an argument) is placed and returns its node pointer. If the team doesn't exist returns NULL */
Team_node* search_team(char* name, Team_node** head){
	int i = hash(name, HASH_SIZE);
	Team_node* aux;
	for (aux = head[i]; aux != NULL; aux = aux ->next){
		if (strcmp(name, aux ->t.name) == 0)
			return aux;
	}
	return NULL;
}

/* deletes a game from the hash table and frees its space */
void delete_game_table(char* name, Game_node** head){
	int i = hash(name, HASH_SIZE);
	Game_node* aux, * prev;
	for (aux = head[i], prev = NULL; aux != NULL; prev = aux, aux = aux ->next){
		if (strcmp(name, aux ->g.name) == 0){
			if (aux == head[i])
				head[i] = aux ->next;
			else
				prev ->next = aux ->next;
			free(aux ->g.name);
			free(aux);
			return;
		}
	}
}

/* deletes a game from the hash table and frees its space. Only used at the end of the orogram, to free all the allocated memory */
void delete_team_table(char* name, Team_node** head){
	int i = hash(name, HASH_SIZE);
	Team_node* aux, * prev;
	for (aux = head[i], prev = NULL; aux != NULL; prev = aux, aux = aux ->next){
		if (strcmp(name, aux ->t.name) == 0){
			if (aux == head[i])
				head[i] = aux ->next;
			else
				prev ->next = aux ->next;
			free(aux ->t.name);
			free(aux);
			return;
		}
	}
}
