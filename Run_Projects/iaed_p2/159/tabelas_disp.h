#ifndef TABELAS
#define TABELAS

#include <stdlib.h>
#include "estruturas.h"

/* HASH TABLE PARA JOGOS */

struct hash_table_jg
{
	Jogo *st;/*Vetor que guarda ponteiros para os jogos*/
	long M;/*Tamanho da tabela*/
	long N;/*Numero de elementos*/
};

typedef struct hash_table_jg * ST_jg;



/* HASH TABLE PARA EQUIPAS*/

struct hash_table_eq
{
	Equipa *st;/*Vetor que guarda ponteiros para as equipas*/
	long M;/*Tamanho da tabela*/
	long N;/*Numero de elementos*/
};

typedef struct hash_table_eq * ST_eq;


/* HASH FUNCTION */

long hash(char *v, long M);


/*FUNCOES DE MANIPULACAO DA HASH TABLE DOS JOGOS*/

ST_jg ST_jg_init(long max);
void ST_jg_insert(ST_jg T,Jogo jogo);
void ST_jg_delete(ST_jg T,Key value);
Jogo ST_jg_search(ST_jg T,Key value);

ST_jg expand_j(ST_jg Tj);
void free_HTj(ST_jg Tj);


/*FUNCOES DE MANIPULACAO DA HASH TABLE DAS EQUIPAS*/

ST_eq ST_eq_init(long max);
void ST_eq_insert(ST_eq T,Equipa equipa);
Equipa ST_eq_search(ST_eq T,Key value);

ST_eq expand_e(ST_eq Te);
void free_HTe(ST_eq Te);




#endif