#ifndef JOGOS_H
#define JOGOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAP 1031
#define MAX_NOME 1024

typedef struct node_jogos 								/* Estrutura que contem as carateristicas de um jogo(node), primeira parte da lista duplamente ligada*/
{
	struct node_jogos *next, *previous;
	char *jogo;
	char *equipa1;
	char *equipa2;
	int sc1;
	int sc2;
} node_jogos;

typedef struct 											/* Estrutura que contem a segunda parte da lista duplamente ligada*/					
{
	node_jogos *head, *last;
} lista_jogos;

typedef struct hash_node_jogos 							/* Estrutura que contem o pointer para o node da lista dos jogos*/
{
	struct hash_node_jogos *next;
	node_jogos *pointer;
} hash_node_jogos;

typedef struct  										/* Estrutura que contem a hashtable dos jogos*/
{
	hash_node_jogos ** tb;
	size_t capacity;
} hashtable_jogos;

int hash(char *string, int capacity);					/* Prototipos das funcoes defenidas em jogos.c*/
hashtable_jogos *mk_hash_table_j();
hash_node_jogos *make_hashnode_j(hash_node_jogos *head, node_jogos *node);
lista_jogos *mk_list();
void make_node_j(char *jogo, char *equipa1, char *equipa2, int sc1, int sc2, lista_jogos *jogos);
void lib_espaco_jogos(hashtable_jogos *h_jogos);
void free_node(node_jogos *n);
void free_list(lista_jogos *l);
void a(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas);
void p(int NL, hashtable_jogos *h_jogos);
void s(int NL, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas);
void l(int NL, lista_jogos *jogos);
void r(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas);
#endif