#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <string.h>
#include <stdlib.h>
#include "LISTAS.h"
#include "HASH.h"

int adicionaJogo_aux(char* name1, char* name2, tlink* HashTeams, pTeam* pTeam1, pTeam* pTeam2);
void atualizaWins_adicJogo(int score1, int score2, pTeam pEquipa1, pTeam pEquipa2);
void atualizaWins_apagaJogo(int score1, int score2, pTeam pEquipa1, pTeam pEquipa2);
void alteraScore_aux(int score1, int score2, int newscore1, int newscore2, pTeam pE1, pTeam pE2);
void atualizaVitorias(pGame pJogo, int caso, int newscore1, int newscore2);
void apagaJogoHash(char* buffer, glink* HashGames, pGame hit);
void apagaJogoLista(glink* pLGhead, glink* pLGtail, pGame hit);
int cstring_cmp(const void *a, const void *b);

#endif
