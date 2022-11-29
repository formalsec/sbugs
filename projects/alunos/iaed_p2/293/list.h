#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* type definition for structure to hold cell*/
typedef struct _game Game;
typedef struct _team Team;
/*Declaration of functions for game structure*/

Game *InitGameNode();
Game *SetGameNode(Game *new, Game *headG, char *fname, char *fteam1, char *fteam2, int fscore1, int fscore2, int nl);
Game *DeleteGameNode(Game *delete, Game *headG);
char *GetName(Game *current);
char *GetTeam1(Game *current);
char *GetTeam2(Game *current);
int Getscore1(Game *current);
int Getscore2(Game *current);
int Getline(Game *current);
Game *GetNext_game(Game *current);
Game *GetPrev_game(Game *current);
Team *GetNext_team(Team *current);
void FreeAll (Game *headG);
Game *muda_score(int score1, int score2, Game *elemento);
Team *InitTeamNode();
Team *SetTeamNode(Team *new, Team *headT, char *fname);
char *Getteam_name(Team *current);
int GetWin(Team *current);
void FreeT (Team *headT);
void Determinewins(Team *headT, Game *current);

#endif
