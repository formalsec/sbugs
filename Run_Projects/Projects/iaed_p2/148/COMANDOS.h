#ifndef COMANDOS_H
#define COMANDOS_H

/* ---------------------------------------------------- BIBLIOTECAS -------------------------------------------------- */

#include <stdio.h>
#include "JOGOS.h"
#include "EQUIPAS.h"

/* ----------------------------------------------------- COMANDOS ---------------------------------------------------- */
/* a - adiciona um novo jogo                                                                                           */
/* A - adiciona uma nova equipa                                                                                        */
/* l - lista todos os jogos pela ordem em que foram introduzidos                                                       */
/* p - procura um jogo                                                                                                 */
/* P - procura uma equipa                                                                                              */
/* r - apaga um jogo                                                                                                   */
/* s - altera a pontuacao de um jogo                                                                                   */
/* g - encontra as equipas que venceram mais jogos                                                                     */
/* x - termina o programa                                                                                              */
/* ------------------------------------------------------------------------------------------------------------------- */

/* ------- PROTOTIPOS COMANDOS -------- */

void novo_jogo(int nl, linkJ headsJ[], linkE headsE[], lista *lst); /* comando a - adiciona um novo jogo */
void lista_jogos(int nl, lista *lst); /* comando l - lista todos os jogos pela ordem em que foram introduzidos */
void procura_jogo(int nl, linkJ headsJ[]); /* comando p - procura um jogo */
void apagar_jogo(int nl, linkJ headsJ[], lista *lst, linkE headsE[]); /* comando r - apaga um jogo */
void altera_score(int nl, linkJ headsJ[], linkE headsE[]); /* comando s - altera a pontuacao de um jogo */
void nova_equipa(int nl, int *contadorequipas, linkE headsE[]); /* comando A - adiciona uma nova equipa */
void procurar_equipa(int nl, linkE headsE[]); /* comando P - procura uma equipa */
void lista_equipas(int nl, int *contadorequipas, linkE headsE[]); /* comando g - encontra as equipas com mais vitorias */
void sair(linkE headsE[], linkJ headsJ[], lista *l); /* libertar a memoria associada as hashs e a lista */

#endif