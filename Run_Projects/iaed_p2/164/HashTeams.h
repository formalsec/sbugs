#ifndef _HASHTEAMS_
#define _HASHTEAMS_

#include "HashGames.h"

Team * HashTeamsInit(int * m);

void HashTeamsInsert(Team * hash_table, Team t, int * m);

Team TeamSearch(char * name, int * m, Team * hash_table);

void DestroyHashTeams(Team * hash_team, int * n_teams);

Team * ExpandTeams(Team * hash_team, int * n_teams, int * m);

#endif