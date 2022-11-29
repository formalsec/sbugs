#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Esta e a estrutura do no presente em jogos e equipas.
* Composto por nome, equipa1, equipa2, resultado1, resultado2 e numero de jogos ganhos.
* Existe ainda um ponteiro para um no seguinte e outro para o anterior. */
typedef struct node{

	char *name;
	char *team1;
	char *team2;
	int score1;
	int score2;
	int won;
	struct node *next, *previous;
	
} node;


/*Estrutura da Lista.
* Composta por nos topo e fim da lista sendo cada um deles um ponteiro.*/
typedef struct list{

	struct node *head, *end;

} list;


/*Estrutura dos nos da HashTable.
* Composta por um no ponteiro que permite aceder as informacoes de um no
e ainda um ponteiro no de hash para o proximo no.*/
typedef struct hashNode{

	node *point;
	struct hashNode *next;

}hashNode;


/*Estrutura da HashTable.
* Composta por apenas um ponteiro hashNode topo que acede a um no da hashTable.*/
typedef struct hashTable{

	struct hashNode *head;

}hashTable;

#endif