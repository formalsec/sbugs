#ifndef HASH_JOGOS
#define HASH_JOGOS

#include "hashtable_equipas.h"
#include "listajogos.h"

typedef struct item_hash_jogo {
    linkjg pno;
    struct item_hash_jogo *next, *prev;
} *item_hash_jg;

item_hash_jg* HashJogos_inic();
item_hash_jg encontra_jogo(item_hash_jg* hash_jogos, char* nome);
void HashJogos_insere(item_hash_jg* hash_jogos, linkjg pno);

#endif