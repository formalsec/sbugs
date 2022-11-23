#ifndef AUXILIARY_FUNCS_H
#define AUXILIARY_FUNCS_H

#include <stdio.h>

#include "linked_list.h"
#include "hashtable.h"

/* Max length of a string (1023 chrs + "\0") */
#ifndef MAXLEN
#define MAXLEN 1024
#endif

/* Calculates the length of a string */
int length(char str[MAXLEN]);
/* Copies a string from a vector to a pointer */
void strCopy(char *srt1, char *str2);
/* Allocates memory and writes the string in it */
char* allocateWrite(char str[MAXLEN]);
/* Given two teams, evaluates which is lexicographically bigger */
int compareQsort(const void* a, const void* b);
/* Reduces the number of victories of a team by one */
void withdrawVictory(Ht_teams ht, char *name);
/* Increases the number of victories of a team by one */
void addVictory(Ht_teams ht, char *name);
/* Finds the biggest number of won games */
int mostWins(nodeTeam head);
/* Counts how many teams have a given number of wins */
int countTeams(nodeTeam head, unsigned int w);
/* Finds the teams with a certain number of wins */
Team* nWinsTeams(nodeTeam head, int n, unsigned int w);
/* Evaluates the current scores of a game and the previous ones */
void changeWins(Ht_teams ht, Game *game,\
                int score1, int score2, int prev1, int prev2);
/* Outputs the details of a game */
void outputGame(Game game, int inL);
/* Outputs the information about a team */
void outputTeam(Team team, int inL);
/* Frees all the memory in the program */
void freeMemory(Ht_games htg, Ht_teams htt, nodeGame hg, nodeTeam ht);

#endif
