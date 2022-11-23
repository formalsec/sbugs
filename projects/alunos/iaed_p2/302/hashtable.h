#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct { /*hashtable de equipas*/
   node_equipa **tb; /*tabela*/
   size_t capacidade; /*capacidade*/
} hash_table_equipa;

typedef struct { /*hashtable de jogos*/
   node_jogo **tb; /*tabela*/
   node_jogo *last; /*ponteiro para o ultimo jogo inserido*/
   size_t capacidade; /*capacidade*/
} hash_table_jogo;

size_t hash(const char *s, size_t capacidade);

hash_table_jogo *mk_hash_table_jg(int capacidade);

hash_table_equipa *mk_hash_table_eq(int capacidade);

void insere_jogo_hash(hash_table_jogo *table, node_jogo *jogo);

void insere_eq_hash(hash_table_equipa *table, node_equipa *equipa);

node_jogo *encontra_hash_jg(hash_table_jogo *table, char *nome);

node_equipa *encontra_hash_eq(hash_table_equipa *table, char *nome);

void remove_jogo_hash(hash_table_jogo *table, char *nome);

void free_hashtable_jg(hash_table_jogo *table);

void free_hashtable_eq(hash_table_equipa *table);

void diminui_vitorias(node_equipa *hash_eq);

void aumenta_vitorias(node_equipa *hash_eq);

#endif
