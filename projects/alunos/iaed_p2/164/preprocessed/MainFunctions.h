#ifndef _MAINFUNCTIONS_
#define _MAINFUNCTIONS_

#include "AuxiliaryFunctions.h"

void NewGame(Node * hash_game, Team * hash_team, List l, int NL, int * m_game, int * m_team, int * n_games);

void NewTeam(Team * hash_team, int * m, int NL, int * n_teams);

void ListGames(int NL, List l);

void SearchGame(Node * hash_game, int * m, int NL);

void SearchTeam(Team * hash_team, int * m, int NL);

void DeleteGame(Node * hash_game, List l, int * m, int NL, int * n_games);

void ChangeScore(Node * hash_game, int * m, int NL);

void FindBest(Team * hash_team, int * n_teams, int NL);

#endif