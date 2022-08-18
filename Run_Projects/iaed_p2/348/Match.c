#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Const.h"
#include "MatchHashTable.h"
#include "TeamHashTable.h"
#include "MatchLinkedList.h"
#include "Team.h"

/* Adds a Match to the HashTable and LinkedList */
void addMatch(int debugLine, 
			 Hash_Table_Team *hash_Team, Hash_Table_Match *hash_Match, 
			 LinkedList_Team *ll_Teams, LinkedList_Match *ll_Matches) {

	char matchName[MAXCHAR], team1[MAXCHAR], team2[MAXCHAR];
	int score1, score2, index;	
	Hash_Node_Match *pHN;
	Team *t1, *t2;

	/* Input data reading */
	scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", matchName, team1, team2, &score1, &score2);

	/* Verifies if match exists */
	index = hash_key(matchName, hash_Match->capacity);
	pHN = hash_Match->table[index];

	while(pHN) {

		if (!strcmp(matchName, pHN->match->name)) {
			printf("%d Jogo existente.\n", debugLine);
			return;
		}

		pHN = pHN->next;	
	}

	/* Verifies if teams exist */
	if (!(t1 = teamExists(team1, hash_Team)) || !(t2 = teamExists(team2, hash_Team))) {
		printf("%d Equipa inexistente.\n", debugLine);
		return;
	}

	/* Adds Match to HashTable and Linked List */
	addToMatchHashList(matchName, t1, t2, score1, score2, hash_Match, ll_Teams, index);
	addToMatchLinkedList(ll_Matches, hash_Match->table[index]);
}

/* Lists all matches */
void listMatches(int debugLine, LinkedList_Match *ll_Matches) {
	List_Node_Match *tail = ll_Matches->tail;

	while(tail) {
		printf("%d %s %s %s %d %d\n", debugLine, tail->match->name,
									  tail->match->team1, tail->match->team2, 
									  tail->match->score1, tail->match->score2);

		tail = tail->prev;
	}
}

/* Finds a Match in the HashTable */
void findMatch(int debugLine, Hash_Table_Match *t) {
	int index;
	char matchName[MAXCHAR];

	Hash_Node_Match * pHN;

	/* Input data reading */
	scanf("%[^:\n]", matchName);

	/* Verifies if match exists */
	index = hash_key(matchName, t->capacity);
	pHN = t->table[index];

	while(pHN) {
			
		if (!strcmp(matchName, pHN->match->name)) {
			printf("%d %s %s %s %d %d\n", debugLine, pHN->match->name, 
										  pHN->match->team1, pHN->match->team2, 
										  pHN->match->score1, pHN->match->score2);
		return;
		}

		pHN = pHN->next;
	}

	printf("%d Jogo inexistente.\n", debugLine);
}

/* Updates Team Scores and max victories count */
void updateTeamScores(Team *t1, Team *t2, Match *match, LinkedList_Team *llT) {

	/* Updates Match's scores */
	if (match->score1 > match->score2) {
		if (t1->gamesWon == llT->maxVictories)
			llT->maxTeamsVictories--;

		t1->gamesWon--;

	}else if (match->score1 < match->score2) {
		if (t2->gamesWon == llT->maxVictories)
			llT->maxTeamsVictories--;

		t2->gamesWon--;
	}

	/* Find new max victories and max teams with similar victories */

	if (llT->maxTeamsVictories == 0) {
		updateMaxVictories(llT);
	}
}




/* Free LinkedList Node when Match is deleted */
void freeLinkedListNode (List_Node_Match *lNM, LinkedList_Match *llM) {
	if (lNM->prev == NULL && lNM->next == NULL) {
		free(lNM);
		llM->head = NULL;
		llM->tail = NULL;

	} else if (lNM->prev == NULL && lNM->next != NULL) {
		lNM->next->prev = lNM->prev;
		llM->head = lNM->next;
		free(lNM);

	} else if (lNM->prev != NULL && lNM->next == NULL) {
		lNM->prev->next = lNM->next;
		llM->tail = lNM->prev;
		free(lNM);

	} else if (lNM->prev != NULL && lNM->next != NULL) {
		lNM->next->prev = lNM->prev;
		lNM->prev->next = lNM->next;
		free(lNM);
	}
}

/* Free HashTable Node when Match is deleted */
void free_nd_match(Hash_Node_Match *hNM) {
	free(hNM->match->name);
	free(hNM->match);
}

void freeHashTableNode(Hash_Node_Match *hNM, int index, Hash_Table_Match *hTM) {
	if (hNM->prev == NULL && hNM->next == NULL) {
		free_nd_match(hNM);
		free(hNM);
		hTM->table[index] = NULL;	

	} else if (hNM->prev == NULL && hNM->next != NULL) {
		hNM->next->prev = hNM->prev;
		hTM->table[index] = hNM->next;
		free_nd_match(hNM);
		free(hNM);

	} else if (hNM->prev != NULL && hNM->next == NULL) {
		hNM->prev->next = hNM->next;
		free_nd_match(hNM);
		free(hNM);

	} else if (hNM->prev != NULL && hNM->next != NULL) {
		hNM->prev->next = hNM->next;
		hNM->next->prev = hNM->prev;
		free_nd_match(hNM);
		free(hNM);
	}
}

/* Free HashTable and LinkedList nodes when match is deleted */
void freeMatch(Hash_Node_Match *hNM, int index, Hash_Table_Match *hTM, 
			   LinkedList_Match *llM) {

	freeLinkedListNode (hNM->lNM, llM);
	freeHashTableNode (hNM, index, hTM);
}

/* Deletes a Match from the HashTable and LinkedList */
void deleteMatch(int debugLine, Hash_Table_Match *hash_Match, 
				 LinkedList_Team *ll_Teams, LinkedList_Match *ll_Matches, 
				 Hash_Table_Team *hTT) {

	char matchName[MAXCHAR];
	int index;
	Team *t1, *t2;
	Hash_Node_Match *pHN;

	/* Input data reading */
	scanf("%[^:\n]", matchName);

	/* Verifies if match exists */
	index = hash_key(matchName, hash_Match->capacity);
	pHN = hash_Match->table[index];
	while(pHN) {
		if (!strcmp(matchName, pHN->match->name)) {
			t1 = teamExists(pHN->match->team1, hTT);
			t2 = teamExists(pHN->match->team2, hTT);
			updateTeamScores(t1, t2, pHN->match, ll_Teams);
			freeMatch(pHN, index, hash_Match, ll_Matches);
			return;
		}

		pHN = pHN->next;	
	}

	printf("%d Jogo inexistente.\n", debugLine);
}

/* Updates Match scores and max victories */
void changeScores(int score1, int score2, Match *match, 
				  Hash_Table_Team *hTT, LinkedList_Team *llT) {

	Team *t1 = teamExists(match->team1, hTT), *t2 = teamExists(match->team2, hTT);

	if (match->score1 > match->score2)
		t1->gamesWon--;
	else if (match->score1 < match->score2)
		t2->gamesWon--;

	match->score1 = score1;
	match->score2 = score2;

	if (match->score1 > match->score2)
		t1->gamesWon++;
	else if (match->score1 < match->score2)
		t2->gamesWon++;

	/* Find new max victories and max teams with similar victories */
	updateMaxVictories(llT);
}

/* Changes a Match Score */
void changeMatchScore(int debugLine, Hash_Table_Match *hTM, Hash_Table_Team *hTT, 
					  LinkedList_Team *llT) {
	
	char matchName[MAXCHAR];
	int score1, score2, index;
	Hash_Node_Match *pHN;

	/* Input data reading */
	scanf("%[^:\n]:%d:%d", matchName, &score1, &score2);

	index = hash_key(matchName, hTM->capacity);
	pHN = hTM->table[index];

	/* Verifies if match exists */
	while(pHN) {
		if (!strcmp(matchName, pHN->match->name)) {
			changeScores(score1, score2, pHN->match, hTT, llT);
			return;
		}

		pHN = pHN->next;	
	}

	printf("%d Jogo inexistente.\n", debugLine);
}