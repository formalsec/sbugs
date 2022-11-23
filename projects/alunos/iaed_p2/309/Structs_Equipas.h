#ifndef STRUCTS_EQUIPAS_H
#define STRUCTS_EQUIPAS_H
#include "Structs_Jogos.h"

typedef struct stru_node {

        struct stru_node * next;
        char * nome;
        int cont_ganhos;

} Equipa;

typedef struct hash_node{

	Equipa * pointer;
	struct hash_node * next;

} hash_node;

typedef struct hashtable{

	hash_node ** heads;

} hashtable;


/*****************Funcoes da Hashtable das Equipas*********************/

int Hashcode(char *nome);
hashtable * CreateHash();
hash_node * AddNode(Equipa * new, hash_node * next);
void DestroyH(hashtable * tb);

/**********************************************************************/

/**********Funcoes da Lista Simplesmente Ligada das Equipas************/

int CheckTeam(hashtable * tb, char * buffer, int key);
Equipa * AddTeam(int NL, Equipa * headE, hashtable * hash);
void SearchTeam(int NL, hashtable * hash);
void FindTeamsWithMaxVictories(int NL, Equipa * headE);
void DestroyE(Equipa * headE);

/**********************************************************************/

#endif