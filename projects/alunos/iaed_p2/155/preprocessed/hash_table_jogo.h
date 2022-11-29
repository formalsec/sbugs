#ifndef _HASH_TABLE_JOGO_
#define _HASH_TABLE_JOGO_

#define MAX_STRING 1024
#define HASH_SIZE 2000

#include <stdio.h>

typedef struct jogo 
{
    struct jogo* next;
    char *nome_jogo;
    char *equipa_1;
    char *equipa_2;
    int score_1;
    int score_2;
}jogo;


jogo * init_hash_table_jogo(jogo *hash[HASH_SIZE]);

jogo * hash_table_jogo_insert(jogo *j, jogo *hash[HASH_SIZE]);

jogo * hash_table_jogo_lookup(char *nome, jogo *hash[HASH_SIZE]);

jogo * hash_table_jogo_delete(char *nome, jogo *hash[HASH_SIZE]);

#endif