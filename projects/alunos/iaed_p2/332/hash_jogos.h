#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef HASH_JOGOS_H
#define HASH_JOGOS_H

#include "jogos.h"

/* numero maximo de jogos na hash table */
#define MAX_TABELA_JG 32911

/* funcoes relacionadas com a hash table dos jogos */
jogo * init_tab_jogos();
void tab_insert_jg(jogo jg, jogo * ht);
int procura_jogo(char * key, jogo * ht);
void free_tabela_jg(jogo * ht);
void tab_delete_jg(jogo jg, jogo * ht_jg);
void reposicionar(jogo jg, jogo * ht_jg);
void apaga_jogo(int nl, jogo * ht_jg, equipa * ht_eq);

#endif