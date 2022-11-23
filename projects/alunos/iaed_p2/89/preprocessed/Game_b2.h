#ifndef GAME_H
#define GAME_H

#include "Team_b2.h"
#include "strdup.h"

#define TRUE 1
#define FALSE 0

/* Key to organize */
#define key(a) (a->name)
/* True if a, a string, is less then b, a string */
#define less(a,b) (strcmp(a,b) < 0)
/* True if a, a string, is equal to b, a string */
#define eq(a,b) (strcmp(a,b) == 0)

/* Structure Game, has a name, two teams, and two scores */
typedef struct game* Game;
struct game{
    char *name;
    Team team1;
    Team team2;
    int score1;
    int score2;
    int id;
};

/* Allocs memory for a Game and its name. Returns a pointer to the Game Created */
Game Gnew(char *name, Team team1, Team team2, int score1, int score2, int NL);
/* Changes the scores of game*/
Game Gchange_score(Game game, int score1, int score2);

/* The sorting function to organize the games */
int Gqsort(const void* game1, const void* game2);

/* Frees the memory of the Game's name and the Game */
void Gdelete(Game game);

/* Returns the name of a Game */
char* Ggetname(Game game);
/* Returns the winner team of a game */
Team Ggetwinner(Game game);
/* Returns the team1 of a game */
Team Ggetteam1(Game game);
/* Returns the team2 of a game */
Team Ggetteam2(Game game);
/* Returns the score1 of game */
int Ggetscore1(Game game);
/* Returns the score2 of game */
int Ggetscore2(Game game);
/* Returns the id of game */
int Ggetid(Game game);
#endif