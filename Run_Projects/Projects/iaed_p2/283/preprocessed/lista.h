#ifndef __LISTA__
#define __LISTA__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"

/*Estrutura da minha lista ligada de jogos */ 

typedef struct node {
	Jogo *jogo;
	struct node *next;
} Node;


Node *New(Jogo *j);

Node *add_last(Node*head,Jogo *j);

Node *Modifica_next_jogo(Node *head,char name[]);

void free_list_jogos(Node*head);

void print_lista(Node *head,int contador);

#endif