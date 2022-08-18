#include "hash_table.h"
#include "hash_equipa.h"
#include "lista_dupla.h"


#ifndef COM
#define COM

#define MAX_TABELA 1000


void adiciona_jogo(int NL,jogo *tabela_hash[MAX_TABELA], \
equipa *tabela_hash_equipa[MAX_TABELA],node_lista **inicio,node_lista **fim);

void adiciona_equipa(int NL,equipa *tabela_hash_equipa[MAX_TABELA]);

void lista_jogos(int NL,jogo *tabela_hash[MAX_TABELA],node_lista **inicio);

void procura_jogo(int NL,jogo *tabela_hash[MAX_TABELA]);

void procura_equipa(int NL,equipa *tabela_hash_equipa[MAX_TABELA]);

void apaga_jogo(int NL,jogo *tabela_hash[MAX_TABELA], \
equipa *tabela_hash_equipa[MAX_TABELA],node_lista **inicio,node_lista **fim);

void altera_score(int NL,jogo *tabela_hash[MAX_TABELA],equipa *tabela_hash_equipa[MAX_TABELA]);

void equipas_mais_jogos(int NL,equipa *tabela_hash_equipa[MAX_TABELA]);


#endif
