#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _EQUIPAS_
#define _EQUIPAS_
#define DIM 10001
#define DIMJOGOS 13009

typedef struct equipas    /*estrutura equipa*/
{
    char *name;
    int vitorias;
} * equipas;

typedef struct node   /*estrutura dum ponteiro para equipa*/
{
    equipas equipa;
    struct node *next, *previous;
} * link;


typedef struct hash   /*estrura da Hastable*/
{
    link *heads;
} Hash;



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/*funcao que recebe uma string e devolve um numero fruto da funcao feita*/
int hashU(char *v, int m);

/*malloc e string copy*/
char *strdup(const char *palavra);

/*incializacao da hash equipas*/
Hash *STinit(int m);

/*percorre a lista para encontrar dar search do nome, auxiliar da search*/
link lookup(link head, char *name);

/*faz search na hashtable de um nome*/
link STsearch(Hash *HashTable, char name[], int m);

/*cria uma estrutura do novo elemento, auxiliar da insertBegin*/
equipas NEW(char *buffer);

/*auxiliar da STinsert permite adicionar nova equipa na hash, auxiliar da STinsert*/
link insertBegin(link head, char text[]);

/*funcao que permite inserir uma equipa dado um nome*/
void STinsert(Hash *HashTable, char name[], int m);

/*funcao de comparacao para ordenacao da g*/
int comparator(const void *p, const void *q);

/*apagar equipas auxiliar*/
void delete (link head);

/*apagar equipas*/
void STdelete(Hash *HashTable, int tamanhohash);


#endif
