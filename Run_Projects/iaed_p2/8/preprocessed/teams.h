#ifndef TEAMS_H_
#define TEAMS_H_

#include "team.h"

#define MAX_TEAMS 100

typedef struct teams_data_item {
    Team * team;
    char * key;
} TeamsDataItem;

typedef struct  {
    int count;
    TeamsDataItem ** items;
} Teams;

Teams * teams_new();
void    teams_add(Teams *tt, Team * t);
Team  * teams_get_team(Teams *tt, char * team_name);

#endif
