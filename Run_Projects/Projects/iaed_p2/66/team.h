#ifndef _TEAMS_
#define _TEAMS_
#include <stdio.h>
#include "common_code.h"

#define INITIAL_WINS 0
#define INITIAL_ITEM_COUNT 0

/*A struct Team has an array of chars coitaining the name of the team and an int with the number of wins of that team*/
typedef struct Team
{
    int wins;
    char *name;
} * Team_ptr;

/*A struct TeamHash has one Team_ptr * containing the hashtable of teams and two int's, one for the size of the hashtable
and one for the number of teams inside the hashtable*/
typedef struct TeamHash
{
    int N, M;
    Team_ptr *hash_table;
} * TeamHash_ptr;

#define name(team) (team->name)
#define wins(team) (team->wins)
#define hash_size(x) (x->M)
#define item_count(x) (x->N)

/*Team functions*/
Team_ptr NewTeam(char *name);
void PrintTeam(Team_ptr team);

/*Hashtable functions*/
TeamHash_ptr TeamHashInit(int max);
TeamHash_ptr TeamHashInsert(TeamHash_ptr *team_hash, Team_ptr team);
TeamHash_ptr TeamHashExpand(TeamHash_ptr team_hash);
Team_ptr TeamHashSearch(TeamHash_ptr team_hash, char *name);

/*Auxilary functions*/
void ArrayInsert(Team_ptr best_teams[], Team_ptr team, int *N);
void mergesort(Team_ptr arr[], int left, int right, TeamHash_ptr team_hash);
void merge(Team_ptr arr[], int left, int m, int right, TeamHash_ptr team_hash);

/*FREE's*/
void DeleteTeamHash(TeamHash_ptr hash_table);

#endif