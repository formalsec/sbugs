#ifndef COMUNS_H
#define COMUNS_H
#define MAX_NOME 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "geral.h"


/*-----INICIALIZACAO DA LISTA DUPLAMENTE LIGADA DE JOGOS-----*/
listagem list();

/*-----------INICIALIZACAO DE AMBAS AS HASH TABLES-----------*/
table_eq Init_eq(int m);
int hash_eq(char nome[],table_eq table);
table_jogos Init_jogo(int m);
int hash_jogos(char nome[],table_jogos table);

/*--------------------------COMUNS--------------------------*/

Equipas search_equipa(Node_eq head, char nome[]);
Equipas SearchEquipa(char nome[],table_eq table_eq);

pJogo search_jogo(Node_jogos head, char nome[]);
pJogo SearchJogo(char nome[],table_jogos table_jogos);

/*---------------------------FREES---------------------------*/
void liberta_no_eq(Node_eq node_eq);
void liberta_no_j(Node_jogos node_j);
void liberta_hash_eq(table_eq tab_eq);
void liberta_hash_j(table_jogos tab_j);

#endif