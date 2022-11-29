#ifndef MATCH_H
#define MATCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TEAM.h"

/*Estrutura Match que contem todas as informacoes de cada Jogo*/

typedef struct match{
  char* name;
  Team team1;
  Team team2;
  int score1;
  int score2;
}* Match;

void freeMatch(Match m);
Team getWinTeam(Match match);
Team getLoserTeam(Match match);
void removeScores(Match match);
void changeScores(Match match, int s1, int s2);
void updateTeamScore(Match match);
Match newMatch(char* name, char* team1, char* team2, int score1, int score2);

#endif
