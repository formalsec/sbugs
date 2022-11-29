#include <stdio.h>
#include "linkedlist.h"

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

typedef struct hashtable_jogos *Hashtable_JOGOS;
typedef struct hashtable_equipas *Hashtable_EQUIPAS;

/*hash table dos ponteiro para os jogos*/
struct hashtable_jogos {
    int M;
    linkPJogo *adj;
};

/*hash table dos ponteiro para as equipas*/
struct hashtable_equipas {
    int M;
    linkPEquipa *adj;
};

/*funcoes de hash tables dos ponteiro para os jogos*/
/*funcao de hash para os nomes de jogos*/
int hashU_JOGOS(char *v,  Hashtable_JOGOS HT);

/*funcao que inicia a hash table*/
Hashtable_JOGOS HashtableInit_JOGOS(int M);

/*funcao que insere nodo na hash table dos ponteiro para os jogos*/
void HashtableInsert_JOGOS(Hashtable_JOGOS HT, linkJogo j);

/*funcao que procura um nome de um jogo na hash table*/
int HashtableSearch_JOGOS (char *v, Hashtable_JOGOS HT);

/*funcao que apaga um nodo da hash table dos ponteiro para os jogos*/
void HashtableDelete_JOGOS (char *v, struct nodeJogo **head, Hashtable_JOGOS HT);

/*funcao que apaga toda a hash table*/
void HashtableDeleteAll_JOGOS (Hashtable_JOGOS HT, linkJogo *head);


/*funcoes de hash tables dos ponteiro para as equipas*/
/*funcao de hash para os nomes de equipas*/
int hashU_EQUIPAS(char *v, Hashtable_EQUIPAS HT);

/*funcao que inicia a hash table*/
Hashtable_EQUIPAS HashtableInit_EQUIPAS(int M);

/*funcao que insere nodo na hash table dos ponteiro para as equipas*/
void HashtableInsert_EQUIPAS(Hashtable_EQUIPAS HT, linkEquipa e);

/*funcao que procura um nome de uma equipa na hash table*/
int HashtableSearch_EQUIPAS (char *v, Hashtable_EQUIPAS HT);

/*funcao que apaga um nodo da hash table dos ponteiro para as equipas*/
void HashtableDelete_EQUIPAS (char *v, struct nodeEquipa **head, Hashtable_EQUIPAS HT);

/*funcao que apaga toda a hash table*/
void HashtableDeleteAll_EQUIPAS (Hashtable_EQUIPAS HT, linkEquipa *head);


#endif /*HASH_H_INCLUDED*/