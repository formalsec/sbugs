#ifndef COMANDOS_H
#define COMANDOS_H

#include "nome_jogos.h"
#include "jogos.h"
#include "equipas.h"
#include "hash_table.h"
#include "hash_table_eq.h"

/*adiciona um novo jogo a base de dados*/
void cmd_a(int NL, char * j_nome, char * eq1_nome, char * eq2_nome, int s1, int s2, ht_games ht_j, 
	ht_teams ht_eq, List_Names * jogos_introduzidos);

/*adiciona uma nova equipa a base de dados*/
void cmd_A(int NL, char * nome, ht_teams ht_eq);

/*lista todos os jogos pela ordem em que foram introduzidos*/
void cmd_l(int NL, List_Names * j, ht_games ht_j);

/*procura um jogo*/
void cmd_p(int NL, char * nome, ht_games ht_j);

/*apaga um jogo*/
void cmd_r(int NL, char * nome, ht_games ht_j, List_Names * l_jogos, ht_teams ht_eq);

/*altera a pontuacao de um jogo*/
void cmd_s(int NL, char * nome, int s1, int s2, ht_games ht_j, ht_teams ht_eq);

/*procura uma equipa*/
void cmd_P(int NL, char * nome, ht_teams ht_eq);

/*encontra as equipas que venceram mais jogos*/
void cmd_g(int NL, ht_teams ht_eq);

#endif
