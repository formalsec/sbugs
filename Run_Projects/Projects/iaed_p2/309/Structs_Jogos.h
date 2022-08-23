#ifndef STRUCTS_JOGOS_H
#define STRUCTS_JOGOS_H
#include "Structs_Equipas.h"

#define C_MAX 1024		/* Numero maximo de caracteres. */
#define HASH_SIZE 1997  /* Dimensao das Hashtables. */


typedef struct stru_node2 {

	struct stru_node2 * next2, *previous2;
	char * nomej;
	char * equipa1;
	char * equipa2;
	int score1;
	int score2;

} Node_Jogo;

typedef struct {

	Node_Jogo * head, * last;

} Jogo;

typedef struct hash_node2{

	Node_Jogo * pointer2;
	struct hash_node2 * next2;

} hash_node2;

typedef struct hashtable2{

	hash_node2 **heads2;

} hashtable2;


/*****************Funcoes da Hashtable dos Jogos***********************/

hashtable2 * CreateHash2();
hash_node2 * AddNode2(Node_Jogo * new, hash_node2 * next);
void DeleteNode2(hashtable2 * hash2, hash_node2 * n, int key);
void DestroyH2(hashtable2 * tb);

/**********************************************************************/

/***********Funcoes da Lista Duplamente Ligada das Equipas*************/

Jogo * CreateGameList();
int CheckGame(hashtable2 * tb, char * buffer, int key);
void AddGame(int NL, Jogo * headJ, hashtable * hash, hashtable2 * hash2);
void SearchGame(int NL, hashtable2 * hash2);
void ChangeScore(int NL, hashtable * hash, hashtable2 * hash2);
void DeleteGame(int NL, Jogo * headJ, hashtable * hash, hashtable2 * hash2);
void PrintGames(int NL, Jogo * headJ);
void DestroyJ(Jogo * headJ);

/**********************************************************************/

#endif