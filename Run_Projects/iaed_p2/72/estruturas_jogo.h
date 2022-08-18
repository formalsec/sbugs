#ifndef ESTRUTURAS_JOGO_H_INCLUDE
#define ESTRUTURAS_JOGO_H_INCLUDE

/*INCLUDES*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jogo.h"
#include "equipa.h"

/*tamanho da hash table*/
#define M_jogos 5059

/*ESTRUTURAS*/

/*
  No_Jogo: Jogo, No_Jogo, No_Jogo, No_Jogo
  Ponteiro para um no que consiste num apontador para um jogo
  um apontador para o prox elemento inserido na hashtable
  e apontadores para o prox e para o anterior elemento inserido
*/
typedef struct no_jogo{
    Jogo jogo;
    
    struct no_jogo* prox;

    struct no_jogo* prox_inserido;
    struct no_jogo* ant_inserido;
} *No_Jogo;

/*
  Tablela de vetores de nos - hash table
*/
typedef No_Jogo Jogos_HT[M_jogos];

/*
  Jogos: No_Jogo, No_Jogo, Jogos_HT
  Estrutura que guarda todas as estruturas necessarias para gerir jogos
  Constituido por um apontador para o primeiro elemento inserido
  e para o ultimo (double linked list) e uma hashtable
*/
typedef struct jogos{
    No_Jogo primeiro;
    No_Jogo ultimo;
    
    Jogos_HT ht;
} *Jogos;

/*PROTOTIPOS*/

Jogos init_jogos();

void insere_jogo(Jogos jogos, Jogo jogo);
No_Jogo push_jogo(No_Jogo atual, Jogo jogo);

Jogo procura_jogo(Jogos jogos, char* nome);
Jogo procura_ht_jogos(No_Jogo no, char* nome);

Jogo remove_jogos(Jogos jogos, char* nome);

void print_todos_jogos(Jogos jogos, unsigned int NL);

void destroi_jogos(Jogos jogos);

#endif
