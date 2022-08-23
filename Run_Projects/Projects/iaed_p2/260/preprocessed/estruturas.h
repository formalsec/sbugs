#ifndef estruturas_h
#define estruturas_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamanho_hash_table 5000


/* --------------------------- Estruturas para jogo -----------------------------*/

/* Estrutura do tipo jogo onde e guardado o nome do jogo, nome da equipa 1, 
	nome da equipa 2, o score da equipa 1, o score da equipa 2.
	Existe ainda um ponteiro para o jogo anterior e outro ponteiro para o jogo 
	seguinte. */

typedef struct struct_jogo{
	char *nome_jogo;
	char *equipa_1;
	char *equipa_2;
	int score_1;
	int score_2;
	struct struct_jogo *next;
	struct struct_jogo *prev;
} jogo;

/* Estrutura de uma lista duplamente ligada onde vao ser inseridos jogos havendo 
	a necessidade de haver um ponteiro que aponta para o primeiro jogo da lista e 
	outro que aponta para o ultimo jogo da lista. */

typedef struct lista_jogos{
	struct struct_jogo *head;
	struct struct_jogo *last;
} list_games;

/* Estrutura de um jogo dentro da hash table onde vai ser guardado um ponteiro de 
	um jogo presente na lista de jogos ( atraves da funcao auxialiar codigo_chave )
	e outro ponteiro que vai apontar para o proximo jogo presente nesta hash table. */

typedef struct jogo_hash{
	jogo *pointr_jogo;
	struct jogo_hash *next;
} jogo_hash;

/* Estrutura da hash table que vai guardar os jogos inseridos pelo usuario atraves 
	do comando a no stdin.
	Possui ainda um ponteiro que aponta para um jogo da hash table. */

typedef struct hash_table_jogos{
	struct jogo_hash *vetor[tamanho_hash_table];
} hash_table_jogos;

/* ---------------------------- Estruturas para equipas ------------------------- */

/* Estrutura do tipo equipa onde e guardado o nome da equipa inserida pelo usuario 
	atraves do comando A no stdin.
	Existe ainda um ponteiro para a equipa anterior e outro ponteiro para a equipa 
	seguinte. */

typedef struct struct_equipa{
	char *nome_equipa;
	int jogos_ganhos;
	struct struct_equipa *next;
	struct struct_equipa *prev;
} sist_equipas;

/* Estrutura de uma lista duplamente ligada onde vao ser inseridas equipas havendo 
	a necessidade de haver um ponteiro que aponta para a primeira equipa da lista e 
	outro que aponta para a ultima equipa da lista. */

typedef struct lista_equipas{
	struct struct_equipa *head;
	struct struct_equipa *last;
} list_teams;

/* Estrutura de uma equipa dentro da hash table onde vai ser guardado um ponteiro de
	uma equipa presente na lista de equipas ( atraves da funcao auxiliar codigo_chave )
	e outro ponteiro que  vai apontar para a proxima equipa presente nesta hash table. */

typedef struct equipa_hash{
	sist_equipas *pointr_equipa;
	struct equipa_hash *next; 
} equipa_hash;

/* Estrutura da hash table que vai guardar as equipas inseridos pelo usuario atraves 
	do comando A no stdin.
	Possui ainda um ponteiro que aponta para uma equipa da hash table. */

typedef struct hash_table_equipas{
	struct equipa_hash *vetor[tamanho_hash_table];
} hash_table_equipas;

#endif
