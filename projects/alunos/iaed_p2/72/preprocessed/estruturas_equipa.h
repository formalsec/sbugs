#ifndef ESTRUTURAS_EQUIPA_H_INCLUDE
#define ESTRUTURAS_EQUIPA_H_INCLUDE

/*INCLUDES*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "auxiliares.h"
#include "equipa.h"

/*tamanho da hash table*/
#define M_equipas 5059

/*ESTRUTURAS*/

/*
  No_Equipa: Jogo, No_Equipa, No_Equipa
  Ponteiro para um no que consiste num apontador para uma equipa
  um apontador para o prox elemento inserido na hashtable
  e um apontador para o proximo elemento inserido
*/
typedef struct no_equipa{
    Equipa equipa;
    
    struct no_equipa* prox;

    struct no_equipa* prox_inserido;
} *No_Equipa;


/*
  Tablela de vetores de nos - hash table
*/
typedef No_Equipa Equipas_HT[M_equipas];

/*
  Equipas: No_Equipa, No_Equipa, Equipas_HT
  Estrutura que guarda todas as estruturas necessarias para gerir equipas
  Constituido por um apontador para o primeiro elemento inserido
  e para o ultimo da lista e uma hashtable
*/
typedef struct equipas{
    No_Equipa primeiro;
    No_Equipa ultimo;

    Equipas_HT ht;
} *Equipas;

/*PROTOTIPOS*/

Equipas init_equipas();

void insere_equipa(Equipas equipas, Equipa equipa);
No_Equipa push_equipa(No_Equipa atual, Equipa equipa);

Equipa procura_equipa(Equipas equipas, char* nome);
Equipa procura_ht_equipas(No_Equipa no, char* nome);

Equipa remove_equipas(Equipas equipas, char* nome);

void destroi_equipas(Equipas equipas);

void print_vencedores(Equipas equipas, unsigned int NL);

#endif
