#ifndef HASH_TABLE_EQ_H
#define HASH_TABLE_EQ_H

#include "equipas.h"

/*definicao do tipo para hash tables para jogos*/
typedef List_Teams** ht_teams;

/*---------------------------------------------------------------------------------------*/

/*inicia uma hash table de equipas*/
ht_teams init_ht_t(int m);

/*insere uma equipa numa hash table de equipas*/
void insert_ht_t(ht_teams l, char * nome);

/*procura uma equipa numa hash table de equipas, segundo o nome*/
Team * search_ht_t(ht_teams l, char * nome);

/*altera o numero de vitorias de uma equipa numa hash table de equipas*/
void change_wins_ht_t(ht_teams l, char * nome, int v);

/*elimina uma hash table de equipas*/
void destroy_ht_t(ht_teams hash_table);

/*calcula qual o maior numero de vitorias alcancadas pelas equipas da hash table*/
int max_wins(ht_teams lst_eq);

#endif
