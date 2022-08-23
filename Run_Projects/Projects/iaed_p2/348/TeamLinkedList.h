#ifndef TEAM_LINKEDLIST_H
#define TEAM_LINKEDLIST_H

#include "Structs.h"

typedef struct list_node_team {
	Team *team; 
	struct list_node_team *next;
} List_Node_Team;

typedef struct linkedlist_team {
	List_Node_Team *head;
	int maxVictories, maxTeamsVictories;
} LinkedList_Team;

LinkedList_Team* mk_Team_LinkedList();
void addToTeamLinkedList(LinkedList_Team *llT, Team *team);
void freeTeamLinkedList(LinkedList_Team *llT);

#endif