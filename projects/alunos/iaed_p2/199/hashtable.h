#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "item.h"

/*Estrutura de dados - No de lista de Games*/
typedef struct nodeG {
	Game* game;
	struct nodeG *next;
}*pGame; 

/*Estrutura de dados - No de lista de Teams*/
typedef struct nodeT {
	Team* team;
	struct nodeT *next;
}*pTeam;

/*Calcula a posicao*/
int hash(char* name, int m);

/*Prototipos de funcoes - Game*/
pGame* initG(int m);
int insertG(pGame* heads, Game* game, int m);
int deleteG(pGame* heads, char* name, int m);
Game* searchG(pGame* heads, char* name, int m);
void freeG(pGame* heads, int m);

/*Prototipos de funcoes - Team*/
pTeam* initT(int m);
int insertT(pTeam* heads, Team* team, int m);
Team* searchT(pTeam* heads, char* name, int m);
void freeT(pTeam* heads, int m);
void printTable(pGame* heads, int m);
void printTableT(pTeam* heads, int m);

#endif