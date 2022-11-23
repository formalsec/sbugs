#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MatchLinkedList.h"

/* Create LinkedList for Matches */
LinkedList_Match* mk_Match_LinkedList() {
	LinkedList_Match* llM = can_fail_malloc(sizeof(LinkedList_Match));	
	llM->head = NULL;
	llM->tail = NULL;

	return llM;
}

/* Adds a Match to the LinkedList */
void addToMatchLinkedList(LinkedList_Match *llM, Hash_Node_Match *hNM) {
	List_Node_Match *lNM = can_fail_malloc(sizeof(List_Node_Match));

	lNM->match = hNM->match;
	lNM->next = llM->head;
	lNM->prev = NULL;

	if(!(llM->head))
		llM->tail = lNM;
	else
		llM->head->prev = lNM;

	llM->head = lNM;

	/* Pointer on the HashTable Node to the Linked List element for easier deletion */
	hNM->lNM = lNM;
}


/* Free Match LinkedList */
void free_list_node_match(List_Node_Match *lNM){
	free(lNM->prev);
	free(lNM->next);
}

void freeMatchLinkedList(LinkedList_Match *llM) {
	List_Node_Match *temp;

	if(llM->head){
		while(llM->head->next){
			temp = llM->head;
			llM->head = llM->head->next;
			free(temp);
		}
	}

	free(llM->head);
	free(llM);
}

