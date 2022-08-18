#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h" /* Ficheiro que contem as funcoes que gerem as hashtables */

			         
#define DIM_STR	1024

void ListaJogos(game_list* l, int NL);

Jogo* FindGame(game_list* l, char buffer[DIM_STR]);

void SearchGame(game_list* l,int NL);

game_list* apagaJogo(team_list* tl,game_list* l, int NL);

game_list* comando_s(team_list* tl,game_list* l, int NL);

game_list* ChangeScores(team_list* tl,game_list* l, char* buffer, int NL);

#endif
