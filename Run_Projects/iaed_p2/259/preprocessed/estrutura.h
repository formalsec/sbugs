#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 1024
#define M_jogos 8059

/*
*****************************
****Estrutura das equipas****
*****************************
*/
typedef struct estrutura_equipa{
	struct estrutura_equipa * next;
	char * nome;
	int vitoria;
} equipa;


/*
*****************************
*****Estrutura dos jogos*****
*****************************
*/
typedef struct estrutura_jogo{
	struct estrutura_jogo * next;
	char * nome;
	equipa * equipa1, * equipa2;
	int golos1, golos2;
} jogo;


/*
*****************************
*******lista dos jogos*******
-----------------------------
***usada para imprimir os****
*jogos por ordem de insercao*
*****************************
*/
typedef struct jogo_l{
	struct jogo_l * next, * prev;
	jogo * jogo_lista;
} jogo_l;

typedef struct lista_jogo{
	jogo_l * head, * last;
} lista_jogo;


/*
*****************************
******lista das equipas******
-----------------------------
***usada no comando g para***
****ordenar lexicografica****
*********as equipas**********
*****************************
*/
typedef struct equipa_l{
	struct equipa_l * next, * prev;
	equipa * equipa_lista;
} equipa_l;

typedef struct lista_equipa{
	equipa_l * head, * last;
} lista_equipa;


/*
*****************************
****Funcoes da hash table****
**********dos jogos**********
*****************************
*/
void inic_hash_j(jogo * aux[]);
void free_no(jogo * aux);
void free_hash_j(jogo * heads[]);
int hash_s(char * nome);
jogo * adi_no(jogo * heads[], char nome[], equipa * equipa1, 
	        equipa * equipa2, int golos1, int golos2);
jogo * procura_j(jogo * heads[], char * nome);
void rem_no(jogo * heads[], char * nome);

/*
*****************************
****Funcoes da hash table****
*********das equipas*********
*****************************
*/
void inic_hash_e(equipa * aux[]);
void free_eq(equipa * aux);
void free_hash_e(equipa * heads[]);
void adi_eq(equipa * heads[], char nome[]);
equipa * procura_e(equipa * heads[], char * nome);
void rem_eq(equipa * heads[], char * nome);

/*
*****************************
**Funcoes da lista ordenada**
**********dos jogos**********
*****************************
*/
lista_jogo * inic_lista();
void free_lista(lista_jogo * lista);
void adiciona_fim(lista_jogo * lista, jogo * jogo);
jogo * elimina_jo(lista_jogo * lista, char * nome);


/*
*****************************
**Funcoes da lista ordenada**
*********das equipas*********
*****************************
*/
lista_equipa * inic_lista_e();
void free_lista_e(lista_equipa * lista);
int adiciona_lex(lista_equipa * lista, equipa * equipa);

#endif