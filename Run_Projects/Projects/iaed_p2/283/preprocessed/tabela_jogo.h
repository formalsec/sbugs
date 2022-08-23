#ifndef __TABELAJOGO__
#define __TABELAJOGO__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"

#define SIZE_STRING 1024
#define HASH_SIZE 1551


/*Representa a lista ligada de jogos na hash table correspondente  */


typedef struct link {
	Jogo *jogo;
	struct link *next;
} *link;

void liberta_link(link head);

link *init();

Jogo *encontra(link *table, char jogo[]);

void introduz_table(link *table,Jogo *novo_jogo);

void liberta_table(link *table);

void Remove_table(link*table,Jogo *j);



#endif