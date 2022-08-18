#ifndef PROJ_H
#define PROJ_H

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

/****************************
 * Declaracao de Constantes *
 ****************************/

#define MAXNOME 1024 /*numero maximo de caracteres para a string correspondente ao nome*/
#define MAXTEAM 1024 /*numero maximo de caracteres para a string correspondente a uma das equipas*/
#define MAXSCORE 4 /*numero maximo de caracteres para a string correspondente a uma das pontuacoes*/
#define HASHTABLE_SIZE 2000 /*tamanho das hashtables , valor a certar depois*/

/*****************************
 * Declaracao das Estruturas *
 *****************************/

/* Estrutura Jogo:
 *
 * Contem os ponteiros que armazenam os enderecos do anterior e proximo node da
 * doubly linked list, ponteiro para o proximo node na hashtable dos jogos
 * e ainda toda a informacao relativa aos jogos inseridos.
 */

typedef struct jogo {
	struct jogo *next, *previous, *next_HashTable_Jogo;
	char *nome, *team1, *team2, *score1, *score2;
} jogo;


/* Estruturas Listas:
 *
 * Armazena toda a informacao relativa ao inicio e fim da doubly linked list
 * (mais concretamente os seus enderecos) e ainda as respetivas hashtables para
 * os jogos e as equipas.
 */

typedef struct {
	struct jogo *head, *last, *HashTable_Jogo[HASHTABLE_SIZE];
} lista;

typedef struct {
	struct equipas *head2, *last2,*HashTable_Equipas[HASHTABLE_SIZE];
} lista2;

/* Estrutura Equipas
 *
 * Contem o ponteiro para o proximo node na hashtable equipas, alem do numero
 * de vitorias que cada equipa tem e ainda um ponteiro para o nome dessa equipa.
 */

typedef struct equipas {
	struct equipas *next2, *previous2, *next_HashTable_Equipas;
	int contador;
	char *nomeE;
	char nomeTeam[MAXTEAM];
} equipas;

/**********************************************
 * Funcoes usadas no projeto (file ./proj2.c) *      
 **********************************************/

void inicia_listas();
jogo * procura_jogo(char *Nome);
equipas * procura_equipa(char *Equipa);
void free_jogo(jogo *j);
void free_equipas(equipas *e);
void lista_jogos(jogo *j);
void lista_equipa(equipas *e);
void lista_equipas_vencedoras(equipas *e);
void adiciona_Node_jogo(char *Nome, char *Equipa1, char *Equipa2, char *Score1, char *Score2);
void remove_Node_jogo(jogo *j);
void adiciona_Node_equipas(char *Equipa);
void remove_Node_equipas(equipas *e);
int hash(char *v);
void adiciona_HashTable_Jogo(char *Nome);
void remove_HashTable_Jogo(char *Nome);
void adiciona_HashTable_Equipas(char *Equipa);
int compararNome (const void *a, const void *b);

#endif