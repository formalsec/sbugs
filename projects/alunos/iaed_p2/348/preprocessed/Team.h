#ifndef TEAM_H
#define TEAM_H

#include "TeamHashTable.h"
#include "TeamLinkedList.h"

void addTeam(int debugLine, Hash_Table_Team *t, LinkedList_Team *llT);
void findTeam(int debugLine, Hash_Table_Team *t);
void listTeamsMostWinsByName(int debugLine, LinkedList_Team *llT);
Team* teamExists(char *teamName, Hash_Table_Team *t);

void updateScoreValues(Team *team1, Team *team2, 
					   int score1, int score2, LinkedList_Team *ll_Teams);

void updateMaxVictories(LinkedList_Team *llT);

#endif

