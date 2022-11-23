#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "constantes.h"


/* Prototipos dos comandos */
Jogo *CriaJogo(char input_separado[MAX_PARAM][MAX_STR]);

void AdicionaNovoJogo(int NL, Jogo *jogo, Node **hash_table_jogos, Node **hash_table_equipas, Lista *lista_jogos);

void ListaJogosIntroduzidos(int NL, Lista *lista_jogos);

void ProcuraJogo(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos);

void ApagaJogo(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos, Node **hash_table_equipas, Lista *lista_jogos);

void AlteraScore(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_jogos, Node **hash_table_equipas);

Equipa *CriaEquipa(char input_separado[MAX_PARAM][MAX_STR]);

void AdicionaNovaEquipa(int NL, Equipa *equipa, Node **hash_table_equipas, Lista *lista_equipas);

void ProcuraEquipa(int NL, char input_separado[MAX_PARAM][MAX_STR], Node **hash_table_equipas);

void OrdenaEquipas(int NL, Lista *lista);

#endif