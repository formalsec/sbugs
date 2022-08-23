#ifndef STRUCTS_H
#define STRUCTS_H
#define MAX_NOME 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "geral.h"

/*------------------------ESTRUTURAS-------------------------*/
typedef struct game
{
    struct game *next,*previous;
    char *winner;
    char *nome;
    char *equipa1,*equipa2;
    int score1,score2;
}*pJogo; 

typedef struct eq
{
    char *nome;
    int vitorias;
}*Equipas;

typedef struct node_jogo
{
    Equipas equipa;
    pJogo match;
    struct node_jogo *next;
}*Node_jogos;

typedef struct node_eq
{
    Equipas equipa;
    struct node_eq *next;
}*Node_eq;

typedef struct hash_eq
{
    Node_eq *heads;
    int M;
}*table_eq;   /*HASH TABLE DAS EQUIPAS*/

typedef struct hash_jogos
{
    Node_jogos *heads;
    int M;
}*table_jogos; /*HASH TABLE DOS JOGOS*/

/*estrutura necessaria para a listagem de todos os
 jogos existentes*/
typedef struct lst
{
    struct game * head, * tail;
}*listagem;

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