#ifndef EQUIPAS_H
#define EQUIPAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAP 1031
#define MAX_NOME 1024

typedef struct node_equipas 							/* Estrutura que contem as carateristicas de uma equipa*/
{
	struct node_equipas *next;
	char *equipa;
	int pontos;
} node_equipas;

typedef struct hash_node_equipas 						/* Estrutura que contem o pointer para o node da lista das equipas*/
{
	struct hash_node_equipas *next;
	node_equipas *pointer;
} hash_node_equipas;

typedef struct  										/* Estrutura que contem a hashtable das equipas*/
{
	hash_node_equipas ** tb;
	size_t capacity;
} hashtable_equipas;

int hash(char *string, int capacity);					/* Prototipos das funcoes defenidas em equipas.c*/
hashtable_equipas *mk_hash_table_e();
hash_node_equipas *make_hashnode_e(hash_node_equipas *head, node_equipas *node);
node_equipas *make_node_e(char *equipa, node_equipas *n_equipas);
void lib_espaco_equipas(node_equipas *n_equipas, hashtable_equipas *h_equipas);
node_equipas * A(int NL, node_equipas *n_equipas, hashtable_equipas *h_equipas);
void P(int NL, hashtable_equipas *h_equipas);
void g(int NL, hashtable_equipas *h_equipas);
int checkins(char *equipa, hashtable_equipas *h_equipas, int hash);

#endif