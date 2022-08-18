#ifndef COMANDOS_H
#define COMANDOS_H

#include "jog_ligados.h"
#include "eq_ligadas.h"
#include "jogos.h"
#include "equipas.h"

/* Adiciona um novo jogo */
void comando_a(int linha, jlink *hash_jogos, elink * hash_equipas, Lista_Jogos lista);

/* Adiciona uma nova equipa */
void comando_A(int linha, elink * hash_equipas);

/* Lista todos os jogos pela ordem em que foram introduzidos */
void comando_l(int linha, Lista_Jogos lista);

/* Procura um jogo dado um nome */
void comando_p(int linha, jlink *hash_jogos);

/* Procura uma equipa dado um nome */
void comando_P(int linha, elink * hash_equipas);

/* Apaga um jogo */
void comando_r(int linha, jlink *hash_jogos, Lista_Jogos lista);

/* Altera a pontuacao de um jogo */
void comando_s(int linha, jlink * hash_jogos);

/* Encontra as equipas que venceram mais jogos */
void comando_g(int linha, elink *hash_equipas);

#endif