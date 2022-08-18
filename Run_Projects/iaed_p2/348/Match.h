#ifndef MATCH_H
#define MATCH_H

#include "MatchHashTable.h"
#include "TeamHashTable.h"
#include "MatchLinkedList.h"

void addMatch(int debugLine, 
			 Hash_Table_Team *hash_Team, Hash_Table_Match *hash_Match, 
			 LinkedList_Team *ll_Teams, LinkedList_Match *ll_Matches);

void listMatches(int debugLine, LinkedList_Match *ll_Matches);
void findMatch(int debugLine, Hash_Table_Match *t);

void deleteMatch(int debugLine, 
				Hash_Table_Match *hash_Match, LinkedList_Team *ll_Teams, 
				LinkedList_Match *ll_Matches, Hash_Table_Team *hTT);

void changeMatchScore(int debugLine, 
					 Hash_Table_Match *hTM, Hash_Table_Team *hTT, LinkedList_Team *llT);

#endif