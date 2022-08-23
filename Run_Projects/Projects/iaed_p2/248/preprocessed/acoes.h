#ifndef _ACOES_
#define _ACOES_

/*
 * Libraries
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "equipa.h"

/*
 * Defines
*/

#define LIM_INPUT 1024

/*
 * Functions
*/

/* Function that adds a new game to the system. */
void a(Lista_jogo *jogos, Hashtable_jogo *jogos_hashtable,
 Hashtable_equipa *equipas, int linha_input);

/* Function that lists all the games of the system. */
void l(Lista_jogo *jogos, int linha_input);

/* Function that searches for a game. */
void p(Hashtable_jogo *jogos, int linha_input);

/* Function that deletes a game. */
void r(Lista_jogo *jogos, Hashtable_jogo *jogos_hashtable,
 Hashtable_equipa *equipas, int linha_input);

/* Function that changes the scores of a game. */
void s(Hashtable_jogo *jogos, Hashtable_equipa *equipas, int linha_input);

/* Function that adds a new team to the system. */
void A(Hashtable_equipa *equipas, int linha_input);

/* Function that searches for a team. */
void P(Hashtable_equipa *equipas, int linha_input);

/* Function that compares two teams by the name. */
int compara(const void *x, const void *y);

/* Function that searches for the teams who have more victories. */
void g(Hashtable_equipa *equipas, int linha_input);

#endif
