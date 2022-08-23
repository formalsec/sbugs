#ifndef GAME
#define GAME

#include <string.h>
#include "team.h"

/* Estrutura game, que representa um jogo */
typedef struct game_node {
	char * name;
	Team team1, team2;
	int score1, score2;
} * Game;


/* Prototipos das funcoes referentes aos jogos */
void freeGame(Game game);
void printGame(Game game, int c);
Game newGame(char * name, Team team1, Team team2, int score1, int score2);
Team winner(Game game);
void changeScore(Game game, int nScore1, int nScore2);

#endif
