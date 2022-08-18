#include <stdio.h>

#include "jogo.h"

/* Declaracao de funcoes */
int compara_nomes(const void *a, const void *b);

void novaEquipa(ht_equipas *hashtable, int NL);
void procuraEquipa(ht_equipas *hashtable, int NL);
void novoJogo(ht_jogo *ht_jogos, ll_jogos **ll_head, ht_equipas *hashtable_equipas, int NL);
void apagaJogo(ht_jogo *ht_jogos, ll_jogos **ll_head, ht_equipas *hashtable_equipas, int NL);
void alteraScore(ht_jogo *ht_jogos,ht_equipas *hashtable_equipas, int NL);
void procuraJogo(ht_jogo *ht_jogos, int NL);
void tabScoresEquipas(ht_equipas *hashtable_equipas, int NL);
void listaJogos(ll_jogos *ll_head, int NL);
void free_hashtable(ht_jogo *ht_jogos);
void free_hashtable_equipas(ht_equipas *hashtable_equipas);
