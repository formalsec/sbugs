#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"

/* Estrutura que representa um jogo. */
typedef struct game {
    char *name;          /* Nome do jogo. */
    Team *team1, *team2; /* Equipas participantes do jogo. */
    int score1, score2;  /* Numero de golos das equipas 1 e 2,
                            respetivamente. */
    int ct;              /* Numero que representa a data de criacao. */
} Game;

/* Construtor e libertador. */
Game *newGame(int, char *, Team *, Team *, int, int);
void freeGame(Game *);

/* Getters */
char *getGameName(Game *);
Team *getGameTeam1(Game *);
Team *getGameTeam2(Game *);
int getGameScore1(Game *);
int getGameScore2(Game *);
int getGameCT(Game *);

/* Setters */
void updateGameScore(Game *, int, int);

/* Others */
void printGame(Game *, int);
int gameKeyOrder(char *, Game *);
int gamesOrder(Game *, Game *);

#endif