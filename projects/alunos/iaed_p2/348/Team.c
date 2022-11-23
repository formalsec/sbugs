#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Const.h"
#include "Team.h"
#include "TeamLinkedList.h"
#include "QuickSortTeams.h"
#include "TeamHashTable.h"

/* Adds a Team to the system */
void addTeam(int debugLine, Hash_Table_Team *t, LinkedList_Team *llT){
	/* Input data reading */
	char teamName[MAXCHAR];
	int index;
	Hash_Node_Team *pHN;


	scanf("%[^:\n]", teamName);

	index = hash_key(teamName, t->capacity);
	pHN = t->table[index];

	/* Verifies if team exists */
	while(pHN){

		if(!strcmp(teamName, pHN->team->name)){
			printf("%d Equipa existente.\n", debugLine);
			return;
		}
			pHN = pHN->next;			
	}

	/* Add team to HashTable and LinkedList */
	addToTeamHashList(teamName, t, index);
	addToTeamLinkedList(llT, t->table[index]->team);
}


/* Finds a Team in the system */
void findTeam(int debugLine, Hash_Table_Team *t){
	/* Input Data Reading */
	int index;
	char teamName[MAXCHAR];
	Hash_Node_Team * pHN;


	scanf("%[^:\n]", teamName);

	index = hash_key(teamName, t->capacity);
	pHN = t->table[index];
	
	/* Verifies if team exists */
	while(pHN){
			
		if(!strcmp(teamName, pHN->team->name)){
			printf("%d %s %d\n", debugLine, pHN->team->name, pHN->team->gamesWon);
			return;
		}

		if(pHN->next != NULL){
			pHN = pHN->next;
		}
		else
			break;
	}

	printf("%d Equipa inexistente.\n", debugLine);
}


/* Lists all teams with most wins */
void listTeamsMostWinsByName(int debugLine, LinkedList_Team *llT) {
 
 	int i;
 	Team **teamsMostWins;
	List_Node_Team *lNT = llT->head;

	/* Checks if there are any teams created */
 	if(llT->maxTeamsVictories == 0) {
 		return;
 	}
 	
 	teamsMostWins = can_fail_malloc(sizeof(Team) * llT->maxTeamsVictories);

 	/* Finds all teams with maximum victories from LinkedList and adds to new array */
	for(i = 0; i<llT->maxTeamsVictories; i++){
		while(lNT){

			if(lNT->team->gamesWon == llT->maxVictories){
				teamsMostWins[i] = lNT->team;
				lNT = lNT->next;
				break;
			}
			lNT = lNT->next;
		}
	}

	/* Quicksorts the array by name */
	quickSortByTName(teamsMostWins, 0, llT->maxTeamsVictories-1);

	/* Output */
	printf("%d Melhores %d\n", debugLine, llT->maxVictories);
	
	for(i = 0; i<llT->maxTeamsVictories; i++){
		printf("%d * %s\n", debugLine, teamsMostWins[i]->name);
	}

	free(teamsMostWins);
}

/* Finds a team and returns a pointer to it */
Team* teamExists(char *teamName, Hash_Table_Team *t){
	int index;
	Hash_Node_Team *pHN;

	index = hash_key(teamName, t->capacity);
	pHN = t->table[index];

	while(t->table[index]){
		if(!strcmp(teamName, pHN->team->name)){
			return pHN->team;
		}

		if(pHN->next != NULL){
			pHN = pHN->next;
		}
		else 
			break;			
	}

	return NULL;
}

/* Finds new max victories and max teams with similar victories */
void updateMaxVictories(LinkedList_Team *llT){
	List_Node_Team *lNT = llT->head;
	int maxGamesWon = 0, maxTeams = 0;
	while(lNT) {

		if (lNT->team->gamesWon > maxGamesWon) {
			maxGamesWon = lNT->team->gamesWon;
			maxTeams = 1;
		}
		else if (lNT->team->gamesWon == maxGamesWon) {
			maxTeams++;
		}

		lNT = lNT->next;
	}

		llT->maxVictories = maxGamesWon;
		llT->maxTeamsVictories = maxTeams;
}

/* Updates games won by a Team, and max victories after adding a match */
void updateScoreValues(Team *team1, Team *team2, 
					   int score1, int score2, LinkedList_Team *ll_Teams){

	int maxGamesWon = 0;

	if(team1->gamesWon == ll_Teams->maxVictories)
		ll_Teams->maxTeamsVictories--;

	if(team2->gamesWon == ll_Teams->maxVictories)
		ll_Teams->maxTeamsVictories--;

	if(score1 > score2) {
		team1->gamesWon++;
	} else if(score1 < score2) {
		team2->gamesWon++;
	} 

	if(team1->gamesWon >= team2->gamesWon)
		maxGamesWon = team1->gamesWon;
	else if (team1->gamesWon < team2->gamesWon)
		maxGamesWon = team2->gamesWon;	

	if (maxGamesWon > ll_Teams->maxVictories){
		ll_Teams->maxVictories = maxGamesWon;
		ll_Teams->maxTeamsVictories = 0;	
	}	

	if(team1->gamesWon == ll_Teams->maxVictories)
		ll_Teams->maxTeamsVictories++;
	
	if(team2->gamesWon == ll_Teams->maxVictories)
		ll_Teams->maxTeamsVictories++;
}

