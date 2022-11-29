#ifndef _LISTA_EQUIPA_
#define _LISTA_EQUIPA_

/*tamanho da hashtable*/
#define HEADS_EQUIPAS 977

#define TRUE 1
#define FALSE 0
#define key(A) A
#define eq(A,B) strcmp(A,B)==0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*estrutura que define a equipa:
--> uma string
--> n. de jogos ganhos*/
typedef struct equipa
{
    char *nome;
    int jogos_ganhos;
}Equipa;

/*no' da lista composto por uma equipa e um ponteiro para
o proximo elemento*/
typedef struct node{
    Equipa *equipa;
    struct node *next;
}Node;
typedef Node* link;



int hash(char* n,int m);
link* inicializa(int m);
link novo_el(char*buffer);
link insere_el(link head,char *text);
void destroi_hash_equipa(link* heads,int M);
void insere_na_lista(link*heads,char *nome);
int existe_el(link*heads,char *nome);
Equipa* procura_equipa(link*heads,char *nome);
Equipa* encontra_equipa(link head,char* nome);




#endif