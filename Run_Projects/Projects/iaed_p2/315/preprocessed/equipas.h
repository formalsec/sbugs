#ifndef EQUIPAS_H
#define  EQUIPAS_H

    
	#include "comuns.h"

/************/
/*Estruturas*/
/************/


/*Esta estrutura define um node que contem um nome de uma equipa e o 
numero de vitorias. As vitorias sao inicializadas a 0.*/

typedef struct stru_node_equipa {
    struct stru_node_equipa *next;
    char *nome_equipa;
    int vitorias;
} *node_equipa;

/*Esta estrutura define os nos da hash table, sendo no_e um ponteiro
para um node pertencente a lista ligada de equipas.*/

typedef struct stru_no_equipa{
	struct stru_no_equipa *next;
	node_equipa no_e;
} *no;


/*Esta estrutura define uma hash table e as suas carateristicas,
sendo *table a hash table em si e cap o numero de elementos que
pode guardar.*/

typedef struct stru_hash_equipa{
	no *table;
	int cap;
}*hash_table_team;

/*Esta estrutura define uma lista ligada de no de equipas, tal que
head e a cabeca da lista ligade e n_el o numero de elementos da lista.*/

typedef struct stru_lista{
	node_equipa head;
}lista;

/*********************************************/
/****************funcoes equipas**************/
/*********************************************/


/***********************/
/*Operacos lista ligada*/
/***********************/

node_equipa criar_node_equipa(char *nome);

node_equipa insert_equipa(node_equipa head, char *equipa);

node_equipa adicionar_ordem_alfabetica(node_equipa head,char* equipa);

/**********************/
/*Operacoes hash table*/
/**********************/

void init_hash_table_equipas(hash_table_team hash_table,int lim);

no equipa_insert(no head);

void hash_insert_equipas(hash_table_team hash_table,char *equipa,lista *equipas);

no hash_search_equipas(hash_table_team hash_table,char*equipa);

/*********************/
/*libertar estruturas*/
/*********************/

void libertar_lista_teams(node_equipa head);

void libertar_elemento_hash(no head);

void libertar_hash_equipas(hash_table_team hash_table);


#endif  /*EQUIPAS_H*/
