#ifndef MAIN_H
#define MAIN_H

#include "equipas.h"
#include "jogos.h"

void criaEquipa(link* hashEquipas, ulong linha);
void criaJogo(jlink* hashJogos,link* hashEquipas, ulong linha, ulong* ordem);
void escreveEquipa(link* hashEquipas, ulong linha);
void escreveJogo(jlink* hashJogos, ulong linha);
void delJogo(jlink* hashJogos, ulong linha);
void alteraScore(jlink* hashJogos, ulong linha);
void listaJogos(jlink* hashJogos, ulong linha);
void listaMelhoresEquipas(link* hashEquipas, ulong linha);

#endif
