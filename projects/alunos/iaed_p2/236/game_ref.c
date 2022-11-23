#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"

/* prints single game from games.c */
void printSingleGame(game *single_game, int NL);

/*
creates new game reference
input: data(*game)
output: new_game_reference(*game_reference)
*/
game_reference *newReference(game *data){
	game_reference *new_game_reference = can_fail_malloc(sizeof(game_reference));
	new_game_reference->data = data;
	new_game_reference->next = NULL;
	new_game_reference->prev = NULL;
	return new_game_reference;
}

/*
finds a game reference
input: head(*game_reference), name(char*)
output: tmp(*game_reference)
*/
game_reference *findReference(game_reference *head, char *name){
	game_reference *tmp = head;
	while(tmp!=NULL){
		if(strcmp(tmp->data->name, name)==0) return tmp;
        tmp = tmp->next;
    }
    free(tmp);
	return NULL;
}

/*
pushes a game reference
input: head(game_reference**), name(char*)
output: tmp(game_reference*)
*/
void pushReference(game_reference **head, game_reference *new_game_reference){
    new_game_reference->next = *head; 
    new_game_reference->prev = NULL;
    if((*head) != NULL){
    	(*head)->prev = new_game_reference; 
    }
    *head = new_game_reference;
}

/*
deletes a game reference
input: head(game_reference**), node_to_delete(game_reference*)
output: none
*/
void deleteReference(game_reference **head, game_reference *node_to_delete){
	if(*head == node_to_delete){
		*head = node_to_delete->next;
		if(*head != NULL){
			(*head)->prev = NULL;
		}
	}else{
		node_to_delete->prev->next = node_to_delete->next;
		if(node_to_delete->next != NULL){
			node_to_delete->next->prev = node_to_delete->prev;
		}
	}
	node_to_delete->next = NULL;
	node_to_delete->prev = NULL;
	free(node_to_delete); /*new*/
}

/*
prints all games
input: head(game_reference*), NL(int)
output: none
*/
void printReference(game_reference *head, int  NL){
	game_reference *tmp;
	if(head==NULL) return;
	tmp = head;
	while(tmp->next!=NULL){
		tmp = tmp->next;
	}
	while(tmp!=NULL){
		printSingleGame(tmp->data, NL);
		tmp = tmp->prev;
	}
	free(tmp);
}

/*
frees all references
input: head(game_reference*)
output: none
*/
void freeReference(game_reference *head){
	game_reference *tmp, *current;
	if(head==NULL) return;
	current = head;
	while(current!=NULL){
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

