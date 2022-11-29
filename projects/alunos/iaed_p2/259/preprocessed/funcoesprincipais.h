#ifndef FUNCOESPRINCIPAIS_H
#define FUNCOESPRINCIPAIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*************************
***funcoes principais****
*************************
*/
void cmd_a(jogo * heads_jogos[], equipa * heads_equipas[], int n_linha, lista_jogo * jogos_ordenados);
void cmd_A(equipa * heads_equipas[], int n_linha);
void cmd_l(lista_jogo * jogos_ordenados, int n_linha);
void cmd_p(jogo * heads_jogos[], int n_linha);
void cmd_P(equipa * heads_equipas[], int n_linha);
void cmd_r(jogo * heads_jogos[], lista_jogo * jogos_ordenados, int n_linha);
void cmd_s(jogo * heads_jogos[], int n_linha);
void cmd_g(equipa * heads_equipas[], int n_linha);

#endif