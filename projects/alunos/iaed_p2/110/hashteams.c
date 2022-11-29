#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashteams.h"

#define FALSE 0
#define TRUE !FALSE

link listInit(){ 
	link head = NULL;
	return head;
}

link listAddNode(ptrTeam team, link next){ 
	link node = can_fail_malloc(sizeof(struct node));
	node->Team = team;
	node->next = next;
	return node;
}

void listDeleteNode(link head){
	if (!listEmpty(head)){
		teamDestroy(head->Team);
		free(head);
	}
	return;
}

ptrTeam getItem(link head){
	if (!listEmpty(head))
		return head->Team;
	return NULL;
}

int listEmpty(link head){
	return head == NULL;
}

link searchList(link head, char* key){
	link node;

	if (!listEmpty(head))
		for (node = head; node; node = node->next)
			if (strcmp(teamName(node->Team), key) == 0)
				return node;
	return NULL;
}

link insertListEnd(link head, ptrTeam i){
    link aux;
	if (listEmpty(head)) 
        return listAddNode(i, NULL); 				/*If the list is empty, add a new head to it*/
	for (aux = head; aux->next; aux = aux->next);
	aux->next = listAddNode(i, NULL);				/*Otherwise, get to the last element and append it*/
	return head;
}


link destroyList(link head){
    link current, aux;
	if (listEmpty(head))							/* If the list is already empty, return NULL*/
        return NULL;
	for (current = head, aux = head->next; current ; aux = current->next, listDeleteNode(current), current = aux);	/* Otherwise delete every node until it's emptied */
	return NULL;		
}


int hash(char *name){								/* Hashing function */
	int key, a = 31415, b = 27183;
	for (key = 0; *name != '\0'; name++, a = a*b % (M-1))
		key = (a*key + *name) % M;
	return key;
}

heads hashInit(){
    int i;
    heads hash = can_fail_malloc(M * sizeof(heads));			/* Allocate memory for the hash table and initialize every head as null */
    for (i=0; i < M; i++)
        hash[i] = NULL;
    return hash;
}

int hashEmpty(heads hash){
	int i;
	for(i = 0; i < M; i++){
		if (!listEmpty(hash[i])){					/* When 1 element is found */
			return FALSE;
		}
	}
	return TRUE;
}

void hashInsert(int NL, heads hashT, ptrTeam team){ 

	if (hashSearch(hashT, team->name)){ 			/*If a team was found*/
		printf("%d Equipa existente.\n", NL);
		teamDestroy(team);
		return;
	}
	else{
		int i = hash(team->name);
		hashT[i] = insertListEnd(hashT[i], team);	/* Otherwise, insert it in the hash table*/
	}
}


link hashSearch(heads heads, char* name){
	return searchList(heads[hash(name)], name);		/* Search the index of the hashtable for the item*/
}

void hashDestroy(link* heads){
    int i;
    for (i=0; i<M; i++)
        destroyList(heads[i]);
    free(heads);
}

maxes getHashMax(heads head){
	int i;
	maxes maxes = {0,0};
	for (i = 0; i < M; i++){
		if (head[i]){
			maxes = getListMax(head[i], maxes);
		}
	}	
	return maxes;
}

maxes getListMax(link head, maxes maxes){
	link current;
	for (current = head; current; current = current->next){
		if (current->Team->wins < maxes.max)
			continue;
		else if (current->Team->wins > maxes.max){					/* If a greater number of wins was found, reset the number of occurences and save it */
			maxes.max = current->Team->wins;
			maxes.maxOcc = 1;
		}
		else if (current->Team->wins == maxes.max)					/* Otherwise increment the number of occurences */
			maxes.maxOcc++;	
	}
	return maxes;
}

char** getHashStrings(heads head, int max, char **strings){
	int i, j = 0;
	char* aux;
	for (i = 0; i < M; i++){
		if (head[i] != NULL){
			if ((aux = getListStrings(head[i], max)) != NULL){
				strings[j] = aux; 								/*Assign a string to the pointer of pointers and increase its index*/
				j++;
			}
		}
	}
	return strings;
}

char* getListStrings(link head, int max){
	link current;
	char* string;
	for (current= head; current; current = current->next)
		if (current->Team->wins == max){
			string = can_fail_malloc(sizeof(char*) * (strlen(current->Team->name)));
			strcpy(string, current->Team->name);
			return string;		
		} 
	return NULL;
}