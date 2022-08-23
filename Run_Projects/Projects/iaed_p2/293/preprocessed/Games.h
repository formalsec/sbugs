#ifndef _GAMES_H
#define _GAMES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void Solve (FILE *fpIn, FILE *fpOut);
void Funcaocaso_a( FILE *fpOut, Game *headG, Team *headT, char *nome, char *team1,char  *team2, int score1, int score2, int NL);
void Funcaocaso_l(Game *headG, FILE *fpOut, int NL);
void Funcaocaso_p(Game *headG, FILE *fpOut, char *nome, int NL);
void Funcaocaso_r(char *nome, Game *headG, FILE *fpOut, int NL);
void Funcaocaso_s(Team *headT, char *nome, int score1, int score2, Game *headG, FILE *fpOut, int NL);
void Funcaocaso_A(char *nome, FILE *fpOut, Team *headT, int NL);
void Funcaocaso_P(char *nome, Team *headT, FILE *fpOut, int NL);
void Funcaocaso_g( Team *headT, FILE *fpOut, int NL);

#endif
