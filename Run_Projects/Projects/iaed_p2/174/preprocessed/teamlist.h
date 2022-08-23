#ifndef TEAMLIST_H
#define TEAMLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "team.h"

/* Estrutura que representa um node de uma lista de equipas. */
typedef struct teamlist {
    Team *team;             /* A equipa. */
    struct teamlist *next;  /* Link para o node seguinte. */
} TeamList;

/* Construtores e libertadores. */
TeamList *newTeamList();
void clearTeamList(TeamList **);

/* Outras funcoes. */
void appendTeamList(TeamList **, Team *);
void shiftTeamList(TeamList **, Team *);
int countTeamList(TeamList *);
void removeTeamList(TeamList **, Team *);
void printTeamList(TeamList *, int);

#endif