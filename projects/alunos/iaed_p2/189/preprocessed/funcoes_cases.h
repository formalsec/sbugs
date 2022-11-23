#ifndef FUNCOES_CASES_H
#define FUNCOES_CASES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipas.h"
#include "Jogos.h"
#include "func_hash.h"
#define SIZE 1009
#define MAX 1024 /*numero maximo de caracteres nos nomes de jogos/equipas eh 1023*/

/*funcao que adiciona um novo jogo*/
link_j letra_a(int num_linhas, link_j *primeiros_j, link_e 
                *primeiras_e, link_j lista_jogos, link_j *fim_lista);

/*funcao que adiciona uma nova equipa*/
link_e letra_A (int num_linhas, link_e *primeiras_e, link_e lista_equipas);

/*funcao que imprime todos os jogos pela ordem em que foram introduzidos*/
int letra_l(int num_linhas, link_j lista_jogos);

/*funcao que procura um jogo com o nome passado como input*/
int letra_p(int num_linhas, link_j *primeiros_j);

/*funcao que procura uma equipa com o nome passado como input*/
int letra_P (int num_linhas, link_e *primeiras_e);

/*funcao que apaga o jogo cujo nume eh passado como input*/
link_j letra_r(int num_linhas, link_j *primeiros_j, link_e *primeiras_e, 
                    link_j lista_jogos, link_j *fim_lista);

/*funcao que altera o resultado de um jogo*/
int letra_s(int num_linhas, link_j *primeiros_j, link_e *primeiras_e);

/*funcao que imprime as equipas que venceram mais jogos*/
int letra_g(int num_linhas, link_e lista_equipas);

/*liberta a memoria alocada ao longo da execucao do programa*/
int frees_projeto(link_j *primeiros_j, link_e *primeiras_e, link_j lista_jogos, link_e lista_equipas);

#endif

