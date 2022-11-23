#ifndef MATCH_HASHTABLE_H
#define MATCH_HASHTABLE_H

#include "Structs.h"

#include "TeamLinkedList.h"
#include "MatchLinkedList.h"
#include "LinkedHashStructs.h"

Hash_Table_Match* mk_Match_Hash_Table();

void addToMatchHashList(char *matchName, Team *team1, Team *team2, 
						int score1, int score2, 
						Hash_Table_Match *t, LinkedList_Team *ll_Teams, int index);

void freeMatchHash(Hash_Table_Match *t);


#endif

