#ifndef PROJETO2_COMANDOS_H
#define PROJETO2_COMANDOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"
#include "jogo.h"

/*----------------------------------------------------------------------------*/
/*                              CONSTANTES                                    */
/*----------------------------------------------------------------------------*/

/* limite maximo de caracteres numa string*/
#define MAX_STR 1024

/*----------------------------------------------------------------------------*/
/*                              FUNCOES                                       */
/*----------------------------------------------------------------------------*/
/* adiciona uma nova equipa*/
void comando_A(int cont, lista_equipa le, ht_equipas ht_e);

/* procura uma equipa*/
void comando_P(int cont, ht_equipas ht_e);

/* cria um novo jogo*/
void comando_p(int cont, ht_jogos ht_j);

/* procura um jogo no sistema*/
void comando_a(int cont, lista_jogos lj, ht_jogos ht_j, ht_equipas ht_e);

/* lista todos os jogos pela ordem em que foram introduzidos*/
void comando_l(int cont, lista_jogos lj);

/* altera a pontuacao de um jogo*/
void comando_s(int cont, ht_jogos ht_j);

/* apaga um jogo*/
void comando_r(int cont, ht_jogos ht_j, lista_jogos lj);

/* encontra as equipas que venceram mais jogos*/
void comando_g(int cont, lista_equipa le);

/* elimina as estruturas criadas no programa*/
void comando_x(lista_equipa le, lista_jogos lj, ht_equipas ht_e, ht_jogos ht_j);

#endif