#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashGame.h"
#include "hashTeam.h"
#include "list.h"

void command_a(char name[], char team1[], char team2[],
               int score1, int score2, int counter, LinkGame* games,
               LinkTeam* teams, LinkedList list);
void command_A(char name[], int counter, LinkTeam* teams);
void command_l(int counter, LinkedList list);
void command_p(char name[], int counter, LinkGame* games);
void command_P(char name[], int counter, LinkTeam* teams);
void command_r(char name[], int counter, LinkGame* games, LinkTeam* teams,
               LinkedList list);
void command_s(char name[], int score1, int score2, int counter,
               LinkGame* games, LinkTeam* teams, LinkedList list);
int cmpfunc(const void * a, const void * b);
void command_g(int counter, LinkTeam* teams);

#endif
