#ifndef _COMANDOS_
#define _COMANDOS_

#include "listas.h"
#include "tabelas_dispersao.h"


/* Chama a funcao do respectivo comando recebido */
void seleciona_funcao(char, lista_ponteiro*, tabela_equipa*, tabela_jogo*, \
                        int M, int MJ, int NL);

/* a: Adiciona um novo jogo. */
void a(lista_ponteiro* lp, tabela_equipa*, tabela_jogo*, int M, int MJ, int NL);

/* A: Adiciona uma nova equipa. */
void A(tabela_equipa*, int M, int NL);

/* l: Lista todos os jogos pela ordem em que foram introduzidos. */
void l(lista_ponteiro* lp, int NL);

/* p: Procura um jogo. */
void p(tabela_jogo*, int MJ, int NL);

/* P: Procura uma equipa. */
void P(tabela_equipa*, int M, int NL);

/* r: Apaga um jogo. */
void r(lista_ponteiro* lp, tabela_equipa*, tabela_jogo*, int M, int MJ, int NL);

/* s: Altera a pontuacao (score) de um jogo. */
void s(tabela_equipa*, tabela_jogo*, int M, int MJ, int NL);

/* g: Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica. */
void g(tabela_equipa* TB_equipa, int M, int NL);


#endif
