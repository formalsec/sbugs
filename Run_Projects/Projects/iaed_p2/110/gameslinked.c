#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameslinked.h"
#include "hashteams.h"


gamelist game_listInit(){
	gamelist list = malloc(sizeof(struct _gamelist));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

gamelink game_listAddNode(Game game, gamelink prev, gamelink next){
	gamelink node = malloc(sizeof(struct gamenode));
	
	node->game = game;
	node->next = next;
	node->prev = prev;
	
	return node;
}

/*Add to end of the list*/
gamelist game_insertListEnd(gamelist list, Game game){
    if(game_listEmpty(list)){								/*If its the first element to be inserted, create a head and return it*/		
		gamelist aux = list;
		gamelink node = game_listAddNode(game, NULL, NULL);

		node->prev = node;
        aux->head = aux->tail = node;

		return aux;
    }
	list->tail->next = game_listAddNode(game, list->tail, NULL);		/*Otherwise, simply append*/
	list->tail = list->tail->next;

	return list;
}

void game_listDeleteNode(gamelink node){ 
	gameDestroy(node->game);											/*Free the node's data*/
	free(node);
}

Game game_getItem(gamelist list){ 
	if(!game_listEmpty(list))
		return list->head->game;
	return NULL;
}

int game_listEmpty(gamelist list){
	return list->head == NULL;
}

gamelink game_searchList(gamelist list, char* key){
	
	if (!game_listEmpty(list)){							
		if (strcmp(list->head->game->name, key) == 0)		/*If the item is on the head*/
			return list->head;

		else if (strcmp(list->tail->game->name, key) == 0)	/*If the item is on the tail*/
			return list->tail;
		
		else{
			gamelink node;
			for (node = list->head; node != NULL;  node = node->next) /*Otherwise, search for it*/
				if (strcmp(node->game->name, key) == 0)
					return node;
		}
	}
	return NULL;
} 

gamelist game_removeList(gamelist list, gamelink node2Delete){
	
	if (node2Delete){
		if (list->tail == list->head){ 			/* If its the only item on the list */
			list->head = list->tail = NULL;			
		}
		else if (node2Delete == list->head){ 	/* If the item is at the beginning of the list */
			list->head = node2Delete->next;
			list->head->prev = list->tail;
					
		}
		else if (node2Delete == list->tail){ 	/* If the item is at the end of the list */
			list->tail = node2Delete->prev;
			list->tail->next = NULL;
		}		
		else {									/* Otherwise, its somewhere in the middle, rearrange the pointers */
			(node2Delete->next)->prev = node2Delete->prev; 
			(node2Delete->prev)->next = node2Delete->next;
		}
	}
	game_listDeleteNode(node2Delete);			/* Delete the node */
	return list;
}

void game_showList(int NL, gamelist list){
	gamelink current;
	for (current = list->head; current != NULL; current = current->next){	/* Go through every node and print its data */
		gamePrint(NL, current->game);	
	}
}

gamelist game_changeScore(int NL, gamelist list, char* key, int news1, int news2){
	gamelink node = game_searchList(list, key);
	
	if(node){ /* If the node exists */
		int s1 = gameScoreT1(node->game), s2 = gameScoreT2(node->game);
		
		node->game = gameChangeScore(node->game, news1, news2);
		/*Rollback the previous win and recalculate it*/
		if (s1 != s2){
			if (s1 > s2)
				node->game->t1->wins--;

			if (s1 < s2)
				node->game->t2->wins--;	
		}	
		/*Check for a winning condition*/

		if (news1 == news2)
			return list;

		if (news1 > news2)
			node->game->t1->wins++;

		if (news1 < news2)
			node->game->t2->wins++;	
        /*If there is a tie, no increments are to be made*/     
	}
	else{
		printf("%d Jogo inexistente.\n", NL);
	}
	return list;
}

void game_destroyList(gamelist list){
    gamelink current, aux;
	
	for (current = list->head ; current != NULL; current=aux){		
		aux = current->next;
		game_listDeleteNode(current);
	}
	
	free(list);
}
