#include "equipas.h"

#ifndef JOGOS_H
#define JOGOS_H

typedef struct game{
  char *name;
  Team *teams;
  int *teamsScores;
  struct game *nextGame;
}Game;

/*Game *createGame(char* gameName, Team team1, Team team2, int scoreTeam1, int scoreTeam2);
int addGame(Game *game, char* gameName, Team team1, Team team2, int scoreTeam1, int scoreTeam2);*/
void prepareGame(Game **gameList, Teams *teamsList,char* string, int commandNumber);
void changeScore(Game *game, Teams *teamsList, char *string, int commandNumber);
void printGames(Game *game, int commandNumber);
void searchGame(Game *game, char *gameName, int commandNumber);
Game *removeGame(Game *game, Teams *teamsList, char *gameName, int commandNumber);
void freeGame(Game *game);

#endif
