#ifndef TEAMHTABLE_H
#define TEAMHTABLE_H

#define MAXTEAM 257

#include "TEAM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Uso de uma hashtable para organizar as equipas e suas respetivas informacoes*/
typedef struct teamnode{
  Team team;
  struct teamnode* next;
}*teamNode;

teamNode* teamHeads;

/*Utilizacao de uma linked list para guardar as equipas com maior numero de vitorias*/
teamNode THeadList;

int hashT(char* v);
void teamInit();
void teamInsert(Team team);
void teamDelete(Team team);
teamNode teamSearch(char* name);
void teamHashListFREE(teamNode t);
void teamHashFREE();
void TlistInit();
teamNode newTeamNode(Team t, teamNode next);
void addTeamNodeList(Team t);
void TfreeHead(teamNode node);
#endif
