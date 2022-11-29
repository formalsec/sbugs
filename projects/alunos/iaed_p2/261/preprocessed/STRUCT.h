#ifndef STRUCT_H
#define STRUCT_H

/* Header file que contem as estruturas utilizadas no projeto */


typedef struct str_node
{
	struct str_node *next, *previous, *collision;
	char* nome;
	char* equipa1;
	char* equipa2;
	int resultado1;
	int resultado2;
} jogo;


typedef struct
{
	struct str_node *head, *last, **hashtable;

} list;


typedef struct equipaTable
{
	struct equipaTable* collision;
	char* equipa;                   /* equipas no sistema */
	int jogosGanhos;
	int bucketCheio;                /* numero de equipas dentro do bucket */
} equipaHash;

#endif