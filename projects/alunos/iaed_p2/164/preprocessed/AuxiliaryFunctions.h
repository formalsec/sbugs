#ifndef _AUXILIARYFUNCTIONS_
#define _AUXILIARYFUNCTIONS_

#include "HashTeams.h"
/* Percentage value for which the hash tables created need to be expanded. The value was 
chosen in order to maximize the execution time, considering some bigger tests.*/
#define EXPAND 0.8
/* Max of 1023 characteres plus '\0'.*/
#define MAX_STR 1024 

void exch(char ** vetor,int i, int j);

int partition(char ** vetor, int l, int r);

void Quick_Sort(char ** vetor, int l, int r);

void Clean(List l, Node * hash_game, Team * hash_team, int * n_teams);

char ** CreatesTeamNames(char ** team_names, Team * hash_team, int count, int best);

int CheckHashGame(int * n_games, int * m_game);

int CheckHashTeam(int * n_teams, int * m_team);

#endif