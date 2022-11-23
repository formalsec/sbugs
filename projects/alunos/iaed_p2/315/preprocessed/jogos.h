#ifndef JOGOS_H
#define  JOGOS_H

    
	#include "comuns.h"

/*Esta estrutura define um jogo, sendo:*/
typedef struct stru_jogo{
    char *nome;      /*nome do jogo*/
    char *equipa1;   /*nome da primeira equipa*/
    char *equipa2;   /*nome da segunda equipa*/
    int score0;      /*pontuacao da primeira equipa*/
    int score1;      /*pontuacao da segunda equipa*/
}jogo;

/*Esta estrutura define um no que contem um jogo.*/
typedef struct stru_no_jogo{
	struct stru_no_jogo *next;
	struct stru_no_jogo *prev;
    jogo game;
}*no_jogo;

/*Esta estrutura define os nos da hash table dos jogos,
sendo um no constituido por um ponteiro para um no_jogo(no_j).*/
typedef struct node_jogos {
    struct node_jogos *next;
    struct node_jogos *prev;
    no_jogo no_j;
} *node_jogo;

/*Esta estrutura define a hash table dos jogos, sendo *table
a hash table em si e cap a capacidade da mesma.*/
typedef struct stru_hash_jogos{
	int cap;
	node_jogo *table;
}*hash_table_jogos;

/*Esta estrutura define a lista ligada que contem todos os jogos
do sistema.*/
typedef struct stru_list_jogos{
	no_jogo head;
	no_jogo last;
}lista_jogos;

/*********************************************************************/
/****************************funcoes jogos****************************/
/*********************************************************************/

/**************************/
/*Operacoes listas ligadas*/
/**************************/

jogo cria_jogo(char *nome1,char*nome_equipa1,char*nome_equipa2,int score_jogo[2]);

no_jogo cria_no_jogo(jogo novo_jogo);

node_jogo cria_node_jogo();

void insert_end_list_jogos(lista_jogos *jogos,jogo novo_jogo);

node_jogo insert_inicio_jogos(node_jogo head);

void remove_jogo(no_jogo no);

node_jogo search_list_jogos(node_jogo head, char *nome_jogo);

/**********************/
/*Operacoes hash table*/
/**********************/

hash_table_jogos init_hash_table_jogos(int lim);

void hash_insert_jogos(hash_table_jogos hash_table,char* nome);

node_jogo hash_search_jogos(hash_table_jogos hash_table, char *nome);

void remove_jogos(hash_table_jogos table_jogo, node_jogo node);

/*********************/
/*libertar estruturas*/
/*********************/

void libertar_jogo(jogo game);

void libertar_lista_hash(node_jogo head);

void libertar_hash_jogos(hash_table_jogos hash_table);


#endif  /*JOGOS_H*/
