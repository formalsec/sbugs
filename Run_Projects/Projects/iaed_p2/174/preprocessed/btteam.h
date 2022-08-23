#ifndef BTTEAM_H
#define BTTEAM_H

#include "team.h"
#include "teamlist.h"
#include <stdlib.h>

/* Estrutura que representa um node de uma arvore binaria de equipas. */
typedef struct BTTeam {
    Team *team;                  /* A equipa. */
    struct BTTeam *left, *right; /* Ramos esquerda e direita da arvore. */
    int height;                  /* Altura relativa para efeitos de optimacao. */
} BTTeam;

/* Construtores libertadores. */
BTTeam *newBTTeam();
void freeBTTeam(BTTeam *);

/* Outras funcoes. */
int countBTTeam(BTTeam *);
Team *searchBTTeam(BTTeam *, char *);
int existsBTTeam(BTTeam *, char *);
void insertBTTeam(BTTeam **, Team *);
void deleteBTTeam(BTTeam **, char *);
TeamList *bestBTTeam(BTTeam *);

#endif