#ifndef __HTJOGOS__
#define __HTJOGOS__

#include "tab_disp.h"
#include "jogo.h"

/* insere e retira jogo */
void insere_tab_jogo(tab_disp ht, jogo e);
void retira_tab_jogo(tab_disp ht, char *nome);

/* liberta memoria da tabela */
void liberta_tab_jogos(tab_disp ht);

/* procura jogo na tabela */
jogo procura_tab_jogo(tab_disp ht, char *nome);

#endif

