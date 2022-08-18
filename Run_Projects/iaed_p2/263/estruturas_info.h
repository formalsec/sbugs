#ifndef ProjetoLeonardo
#define ProjetoLeonardo
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TITLE 1023
#define MAX_TEAM 1023 
#define MAX_HASH 1997
#define MAX_TOTAL 1600
#define SIZE 1997 /* numero primo para minimizar as colisoes */

typedef struct team{ /* estrutura do node da equipa */
  char *name_team;
  int wins;
  struct team *next; /* ponteiro para a proxima equipa da linked list */
} team;

typedef struct game{ /* estrutura do node do jogo */
  char *name_game;
  char *team1;
  char *team2;
  int score1;
  int score2;
  int order;
  struct game *next; /* ponteiro para o proximo jogo da linked list */
} game;

/* FUNCOES AUXILIARES PROTOTIPOS */

team* NEWTEAM(char* name_team);
game* NEWGAME(char* name_game, char* team1, char* team2, int score1, int score2, int order);
game* PutsAsHeadListGame(game* head, char* name_game, char* team1, char* team2, int score1, int score2, int order);
team* PutsAsHeadListTeam(team* head, char* name_team);
int ReturnsHashGameIndex(char *name_game);
int ReturnsHashTeamIndex(char* name_team);
game* LooksUpInGameHash(game** hashtablegame, char* name_game);
team* LooksUpInTeamHash(team** hashtableteam, char* name_team);
void InitializesHashTableGame(game** hashtablegame);
void InitializesHashTableTeam(team** hashtableteam);
void FreeGameInfo(game* t);
game* DeleteGame(game* head, char* name_game);

#endif
