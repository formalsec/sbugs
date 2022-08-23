#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "JogoEquipa.h"

/* Prototipo para a funcao hash */
int hash(char* string, int max);

/* Prototipos para a hashtable dos Jogos */
void TabJogosinit(int* max_jogos, int* N_jogos, Jogo* TabJogos);
Jogo* expand_jogos(int* max_jogos, int* N_jogos, Jogo* TabJogos);
void TabJogosinsert(int* max_jogos, int* N_jogos, Jogo* TabJogos, Jogo Jogo);
void TabJogosdelete(int* max_jogos, int* N_jogos, Jogo* TabJogos, char* string);
Jogo TabJogossearch(int* max_jogos, Jogo* TabJogos, char* string);
void freeTabJogos(int* max_jogos, Jogo* TabJogos);

/* Prototipos para a hashtable das Equipas */
void TabEquipasinit(int* max_equipas, int* N_equipas, Equipa* TabEquipas);
Equipa* expand_equipas(int* max_equipas, int* N_equipas, Equipa* TabEquipas);
void TabEquipasinsert(int* max_equipas, int* N_equipas, Equipa* TabEquipas, Equipa Equipa);
Equipa TabEquipassearch(int* max_equipas, Equipa* TabEquipas, char* string);
void freeTabEquipas(int* max_equipas, Equipa* TabEquipas);

#endif