#ifndef TEAM_H
#define TEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Estrutura Team que contem todas as informacoes de cada equipa*/

typedef struct team* Team;

struct team {
  char* name;
  int score;
};

void freeTeam(Team t);
Team newTeam(char* name);

#endif
