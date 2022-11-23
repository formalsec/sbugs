#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include "LISTAS.h"

/* Hash tables teem o tamanho 5857 fixo, colisoes sao resolvidas por encadeamento externo. */
#define M 5857

int hash(char *v);

tlink* initTeams();
tlink Tinsert_aux(pTeam pEquipa, tlink next);
void Tinsert(tlink* HeadFila, pTeam pEquipa);
int searchTeamHash(char* buffer, tlink* HashTeams, pTeam* hit);
void limpaHashTeams(tlink* HashTeams);

glink* initGames();
glink Ginsert_aux(pGame pJogo, glink next);
void Ginsert(glink* HeadFila, pGame pJogo);
int searchGameHash(char* buffer, glink* HashGames, pGame* hit);
void limpaHashGames(glink* HashGames);

#endif
