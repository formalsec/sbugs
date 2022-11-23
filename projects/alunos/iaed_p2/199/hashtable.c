#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int hash(char* name, int m){
	int h = 0, a = 127;

	for (; *name != '\0'; name++)
		h = (a*h + *name) % m;
	return h;
}

pGame* initG(int m){
	int i;

	pGame* heads = can_fail_malloc(m * sizeof(pGame)); 
	for (i = 0; i < m; i++) 
		heads[i] = NULL;
	return heads;
}

int insertG(pGame* heads, Game* game, int m){
	int h = hash(game->name, m);
	pGame temp;
	pGame prev;

	if(heads[h] == NULL){
		heads[h] = can_fail_malloc(sizeof(struct nodeG));
		heads[h]->game = game;
		heads[h]->next = NULL;
		return 0;
	}
	temp = heads[h];
		
	while(temp != NULL){
		if(strcmp(temp->game->name,game->name)==0){
			freeGame(game);
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	prev->next = can_fail_malloc(sizeof(struct nodeG));
	prev->next->game = game;
	prev->next->next = NULL;
	return 0;
}

Game* searchG(pGame* heads, char* name, int m){
	int h = hash(name, m);

	pGame temp = heads[h];

	while(temp != NULL){
		if(strcmp(name,temp->game->name)==0){
		return temp->game;
		}
		temp = temp->next;
	}
	return NULL;

}

int deleteG(pGame* heads, char* name, int m){
	int h = hash(name, m);

	pGame temp = heads[h];
	pGame prev = NULL;

	while(temp != NULL){
		if(strcmp(name,temp->game->name)==0){
			if(prev!=NULL){
				prev->next = temp->next;				
			}else{
				heads[h] = temp->next;
			}
			freeGame(temp->game);
			free(temp);
			return 0;
		}
		prev = temp;
		temp = temp->next;
	}
	return 1;
}

void freeG(pGame* heads, int m){
	int i;

	for (i = 0; i < m; i++){
		pGame temp = heads[i];
		pGame g;
		while(temp != NULL){
			g = temp->next;
			freeGame(temp->game);
			free(temp);
			temp = g;
		}
	}
	free(heads);
}

pTeam* initT(int m){
	int i;

	pTeam* heads = can_fail_malloc(m* sizeof(pTeam)); 
	for (i = 0; i < m; i++) 
		heads[i] = NULL;
	return heads;
}

int insertT(pTeam* heads, Team* team, int m){
	int h = hash(team->name, m);
	pTeam temp;
	pTeam prev;

	if(heads[h] == NULL){
		heads[h] = can_fail_malloc(sizeof(struct nodeT));
		heads[h]->team = team;
		heads[h]->next = NULL;
		return 0;
	}
	temp = heads[h];
		
	while(temp != NULL){
		if(strcmp(temp->team->name,team->name)==0){
			freeTeam(team);
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
	prev->next = can_fail_malloc(sizeof(struct nodeT));
	prev->next->team = team;
	prev->next->next = NULL;
	return 0;
}

Team* searchT(pTeam* heads, char* name, int m){
	int h = hash(name, m);

	pTeam temp = heads[h];

	while(temp != NULL){
		if(strcmp(name,temp->team->name)==0){
		return temp->team;
		}
		temp = temp->next;
	}
	return NULL;
}

void freeT(pTeam* heads, int m){
	int i;

	for (i = 0; i < m; i++){
		pTeam temp = heads[i];
		pTeam t;
		while(temp != NULL){
			t = temp->next;
			freeTeam(temp->team);
			free(temp);
			temp = t;
		}
	}
	free(heads);
}