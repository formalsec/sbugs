#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "jogos.h"

/*definicao do tipo para hash tables para jogos*/
typedef List_Games** ht_games;

/*---------------------------------------------------------------------------------------*/

/*inicia uma hash table de jogos*/
ht_games init_ht_g(int m);

/*calcula em que posicao da hash table de jogos se deve inserir um jogo*/
int hash(char * nome, int m);

/*insere um jogo numa hash table de jogos*/
void insert_ht_g(ht_games l, char * jogo, char * eq1, char * eq2, int sc1, int sc2);

/*procura um jogo numa hash table de jogos, segundo o nome*/
Game * search_ht_g(ht_games l, char * nome);

/*altera o score de um jogo numa hash table de jogos*/
void change_sc_ht_g(ht_games l, char * nome, int score1, int score2);

/*elimina um jogo da hash table de jogos*/
void remove_ht_g(ht_games l, char * nome);

/*elimina uma hash table de jogos*/
void destroy_ht_g(ht_games hash_table);

#endif
