#ifndef TEAM_H
#define TEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que representa uma equipa. */
typedef struct team {
    char *name; /* Nome da equipa. */
    int wins;   /* Total de vitorias da equipa. */
} Team;

/* Construtor e libertador. */
Team *newTeam(char *, int);
void freeTeam(Team *);

/* Getters */
char *getTeamName(Team *);
int getTeamWins(Team *);

/* Setters */
void addTeamWins(Team *, int );

/* Others */
void printTeam(Team *, int );
int teamKeyOrder(char *, Team *);
int teamsOrder(Team *, Team *);

#endif