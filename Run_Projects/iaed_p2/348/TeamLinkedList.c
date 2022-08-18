#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TeamLinkedList.h"

/* Create LinkedList for Teams 
   Stores the max Number of Victories and total teams with max victories */
LinkedList_Team* mk_Team_LinkedList() {
	LinkedList_Team* llT = malloc(sizeof(LinkedList_Team));	
	llT->head = NULL;
	llT->maxVictories = 0;
	llT->maxTeamsVictories = 0;

	return llT;
}

/* Adds a Team to the LinkedList */
void addToTeamLinkedList(LinkedList_Team *llT, Team *team) {
	List_Node_Team *lNT = malloc(sizeof(List_Node_Team));

	lNT->team = team;
	lNT->next = llT->head;
	
	if(llT->maxVictories == 0)
		llT->maxTeamsVictories++;

	llT->head = lNT;
}

/* Free Team LinkedList */
void freeTeamLinkedList(LinkedList_Team *llT) {
	List_Node_Team *temp;

	if(llT->head){
		while(llT->head->next){
			temp = llT->head;
			llT->head = llT->head->next;
			free(temp);
		}
	}
	
	free(llT->head);
	free(llT);
}

