#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Const.h"
#include "Match.h"
#include "Team.h"

#include "TeamHashTable.h"
#include "TeamLinkedList.h"

#include "MatchHashTable.h"
#include "MatchLinkedList.h"

int main() {

	/* HashTable and LinkedLists initialization */
	Hash_Table_Team *hash_Teams = mk_Team_Hash_Table(TEAM_HASH_SIZE);
	LinkedList_Team *ll_Teams = mk_Team_LinkedList();
	
	Hash_Table_Match *hash_Matches = mk_Match_Hash_Table();
	LinkedList_Match *ll_Matches = mk_Match_LinkedList();

	int debugLine = 1;
	char command;

	while (1){

		switch (command = getchar()) {
			case 'a': 
				getchar();
				addMatch(debugLine, hash_Teams, hash_Matches, ll_Teams, ll_Matches);
				break;

			case 'l':
				listMatches(debugLine, ll_Matches);
				break;

			case 'p':
				getchar();
				findMatch(debugLine, hash_Matches);
				break;

			case 'r':
				getchar();
				deleteMatch(debugLine, hash_Matches, ll_Teams, ll_Matches, hash_Teams);
				break;

			case 's':
				getchar();
				changeMatchScore(debugLine, hash_Matches, hash_Teams, ll_Teams);
				break;

			case 'A':
				getchar();
				addTeam(debugLine, hash_Teams, ll_Teams);
				break;

			case 'P':
				getchar();
				findTeam(debugLine, hash_Teams);
				break;

			case 'g':
				listTeamsMostWinsByName(debugLine, ll_Teams);
				break;

			case 'x': 
				freeTeamHash(hash_Teams);
				freeTeamLinkedList(ll_Teams); 

				freeMatchHash(hash_Matches);
				freeMatchLinkedList(ll_Matches);
				return 0;
		} getchar();

		debugLine++;
	}

	return 0;
}