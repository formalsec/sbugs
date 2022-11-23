#ifndef JOGOS_HASH_file
#define JOGOS_HASH_file

#include "jogos_structs.h"

JOGO_HASH ** init_hash_jogos();

void add_jogo_hash(JOGO_HASH ** hashtable_jogos, JOGO * jogo);

JOGO * procura_jogo(JOGO_HASH ** hashtable_jogos, char * nome);

void remove_jogo_hash(JOGO_HASH ** hashtable_jogos, char * nome);

void altera_score(JOGO_HASH ** hashtable_jogos, char * nome, int score1, int score2);

char * maior_score_jogo(JOGO_HASH ** hashtable_jogos, char * nome);

void destroy_jogos_hash(JOGO_HASH ** hashtable_jogos);

#endif