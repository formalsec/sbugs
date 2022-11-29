#include "teams.h"

#ifndef IAED_P2_FINAL_MATCHES_H
#define IAED_P2_FINAL_MATCHES_H

#define HASH_CAP_M 1000
#define MAX_CHARS_M 1024

/* Estrutura de no de um jogo */
typedef struct stru_node_match {
    struct stru_node_match *next, *prev;
    struct stru_node_team *team1, *team2;
    char *desc;
    int score[2];
} node_match;

/* Estrutura de lista ligada dos jogos */
typedef struct l_match {
    struct stru_node_match *head, * last;
} linked_list_matches;

/* Estrutura de no da hash table dos jogos */
typedef struct hash_node_match{
    struct stru_node_match *node;
    struct hash_node_match *next, *prev;
} ptr_match;

/* Estrutura de hash table dos jogos */
typedef struct hash_matches{
    struct hash_node_match *nodes[HASH_CAP_M];
} hash_table_matches;

/* cria um no de um jogo, adiciona-o a lista ligada de jogos e devolve esse no */
node_match * add_linked_list_match(linked_list_matches * linked_matches, char desc[], node_team *team1, node_team *team2, int score[2]);

/* cria um ptr_match que aponta para o no n, e coloca-o na hash table dos jogos */
void add_hash_table_match(hash_table_matches * hash_matches, node_match* n);

/* procura um ptr_match que aponta para o no com a descricao d e devolve esse ptr_match */
ptr_match * search_match(hash_table_matches * hash_matches, char d[]);

/* remove o ptr_match ptr_n da hash tables dos jogos e devolve o no para o qual estava a apontar */
node_match * remove_match_hash_table(hash_table_matches *hash_matches, ptr_match *ptr_n);

/* remove o no n da lista ligada de jogos */
void remove_match(linked_list_matches * linked_matches, node_match * n);

/* destroi a hash table do jogos, fazendo free do seu conteudo */
void destroy_hash_matches(hash_table_matches *hash_matches);

/* destroi a lista ligada do jogos, fazendo free do seu conteudo */
void destroy_linked_matches(linked_list_matches *linked_matches);

#endif

