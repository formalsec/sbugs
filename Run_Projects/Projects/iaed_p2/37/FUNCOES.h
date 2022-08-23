#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AUXILIARES.h"
#include "LISTAS.h"
#include "HASH.h"

void adicionaJogo(int NL, glink* pLGhead, glink* pLGtail, tlink* HashTeams, glink* HashGames);
void adicionaEquipa(int NL, tlink* pLThead, tlink* pLTtail, tlink* HashTeams);
void listaJogos(int NL, glink* pLGhead);
void procuraJogo(int NL, glink* pLGhead);
void procuraEquipa(int NL, tlink* HashTeams);
void apagaJogo(int NL, glink* pLGhead, glink* pLGtail, glink* HashGames);
void alteraScore(int NL, glink* HashGames);
void melhoresEquipas(int NL, tlink* pLThead);
void sair(tlink* pLThead, tlink* pLTtail, glink* pLGh, glink* pLGt, tlink* HashT, glink* HashG);

#endif
