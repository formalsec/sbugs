#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define SIM 1
#define NAO 0
#define STR_SIZE 1023
#define INICAP 1237

node_jogo *func_a(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq, node_jogo *head_lista_jogos);

void func_l(int cont, node_jogo *head_lista_jogos);

void func_p(int cont, hash_table_jogo *syst_jogos);

node_jogo *func_r(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq, node_jogo *head_lista_jogos);

void func_s(int cont, hash_table_jogo *syst_jogos, hash_table_equipa *syst_eq);

void func_A(int cont, hash_table_equipa *syst_eq);

void func_P(int cont, hash_table_equipa *syst_eq);

void func_g(int cont, hash_table_equipa *syst_eq);

#endif
