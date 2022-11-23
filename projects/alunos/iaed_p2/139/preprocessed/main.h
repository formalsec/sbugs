#ifndef _MAIN_H
#define _MAIN_H

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Hash.h"


#define DRAW NULL
#define MIN -1
#define PLUS_ONE 1
#define MINUS_ONE -1
#define M 1000
#define MAX_CHAR_NOME 1024 /* Maximo de caracteres de um jogo ou equipa mais um para o \0.*/
#define TRUE 1             /* Representa o valor booleano verdadeiro. */

/** Comandos **/

void a(LinkedList *jogos, LinkedList *equipas, LinkedList jogos_list, int NL); /* a Adiciona um novo jogo. */
void A(LinkedList *equipas,LinkedList equipas_list, int NL); /* A Adiciona uma nova equipa. */
void l(LinkedList jogos_list, int NL); /* l Lista todos os jogos pela ordem em que foram introduzidos. */
void p(LinkedList *jogos, int NL); /* p Procura um jogo. */
void P(LinkedList *equipas, int NL); /* P Procura uma equipa. */
void r(LinkedList* jogos, LinkedList* equipas,LinkedList jogos_list,int NL); /* r Apaga um jogo. */
void s(LinkedList *jogos, LinkedList *equipas, int NL); /* s Altera a pontuacao (_score_) de um jogo. */
void g(LinkedList equipas_list ,int NL);/*  g Encontra as equipas que venceram mais jogos. */
void atualiza_score(LinkedList *equipas, Key vencedor, int change);
char *encontra_vencedor(Jogo *jogo);
LinkedList findMaxVitorias(LinkedList equipas);
void findMax(LinkedList equipas, LinkedList sortedMaxEquipas, int max);

#endif