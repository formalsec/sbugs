#ifndef _GAME_
#define _GAME_

#include "Team.h"

/* Game structure.*/

/* A Game is defined by 2 integers "score_1" and "score_2", a name and 2 Teams. The
"score_1" belongs to "team_1" and "score_2" belongs to "team_2".*/
typedef struct game {
    int score_1, score_2;
    char * name;
    Team team_1, team_2;
} * Game;

/* Prototypes of Game's basic operations.*/

Game InitGame();

void SetScore(int score_1, int score_2, Game g);

void SetName(char name[],Game g);

void SetTeams(Team team_1, Team team_2, Game g);

Team Winner(Game g);

char * GameName(Game g);

Team GameTeam1(Game g);

Team GameTeam2(Game g);

int GameScore1(Game g);
    
int GameScore2(Game g);

void WriteGame(Game g, int NL);

void DestroyGame(Game g);

#endif