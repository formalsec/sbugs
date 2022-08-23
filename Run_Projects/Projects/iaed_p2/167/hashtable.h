#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdup.h"

/* ============================================================ */

typedef struct game 
{
    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;
} *p_game;

typedef struct team
{
    char *name;
    int wins;
} *p_team;

/* ============================================================ */

int Hash(char *name, int M);

/* ============================================================ */

p_game * Init(int m);

p_game * HTInsertElement(p_game *p, char *name, char *team1, char *team2, int score1, int score2, int N, int M);

p_game * HTRemoveElement(p_game *p, char *name, int N, int M);

p_game Search(p_game *p, char *name, int M);

p_game * Expand(p_game *p, int N, int M);

p_game * FreeAllHT(p_game *p, int M);

/* ============================================================ */

p_team *Init_T(int m);

p_team * HTInsertElement_T(p_team *p, char *name, int wins, int N, int M);

p_team * HTRemoveElement_T(p_team *p, char *name, int N, int M);

p_team Search_T(p_team *p, char *name, int M);

p_team * Expand_T(p_team *p, int N, int M);

p_team * FreeHT_T(p_team *p);

p_team * FreeAllHT_T(p_team *p, int M);

/* ============================================================ */

#endif