#ifndef comandos_h
#define comandos_h

#define MAX_PAL 1023
#define MAX_EQUIPAS_VITORIAS 100

#include "equipas.h"
#include "jogos.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_EXISTE 0
#define EXISTE 1
#define EXIT 0

/* le os comandos do input ate ao comando x que termina */
int le_comandos(link_equi *equipas,link_jogo * jogos_hashtable, Lista_jogos jogos_ls);

/* Adiciona um novo jogo. */
void a_executa(int NL,link_jogo * jogos_hashtable,Lista_jogos jogos_ls,link_equi* equipas);

/* Lista todos os jogos introduzidos. */
void l_executa(int NL,Lista_jogos jogos_ls);

/* Procura um jogo com o nome dado. */
void p_executa(int NL,link_jogo * jogos_hashtable);

/*  Apaga um jogo dado um nome. */
void r_executa(int NL, link_jogo * jogos_hashtable,link_equi* equipas);

/* Altera o score de um jogo dado o nome.  */
void s_executa(int NL, link_jogo * jogos_hashtable,link_equi* equipas);

/* Adiciona uma nova equipa. */
void A_executa(int NL,link_equi *equipas,int tamanho);

/*  Procura uma equipa dado um nome. */
void P_executa(int NL,link_equi *equipas, int tamanho);

/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa). */
void g_executa(int NL,link_equi *equipas);



#endif /* comandos_h */
