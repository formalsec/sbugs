#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CHAR 1025
#define TABLE_SIZE 1579

/*Estruturas*/

/*Estrutura jogo*/
typedef struct Jogo
{
	char *nome;
	char *equipa_1;
	char *equipa_2;
	int   score_1;
	int   score_2;
	struct Jogo *next;

}Jogo;

/*Estrutura Equipa*/
typedef struct Equipa
{
	char *nome_equipa;
	int   vitorias;
	struct Equipa *next;

}Equipa;

/*Hashtable dos Jogos*/
Jogo *HashGames[TABLE_SIZE];

/*Hashtable das Equipas*/
Equipa *HashTeams[TABLE_SIZE];

/*Linked list auxiliar Jogos*/
typedef struct JogosOrd
{	
	Jogo *game;
	struct JogosOrd *prev;
	struct JogosOrd *next;

}JogosOrd;

/*Pointer global que guarda a head da linked list JogosOrd*/
JogosOrd *headgame;

/*Linked list auxiliar Equipas*/
typedef struct EquipasOrd
{
	Equipa *team;
	struct EquipasOrd *next;

}EquipasOrd;

/*Pointer global que guarda a head da linked list EquipasOrd*/
EquipasOrd *headteam;

/*Variavel global que guarda o numero de linha de input*/
int nl;

/*Prototipos das funcoes*/
void cmd_a();
void cmd_A();
void cmd_l();
void cmd_p();
void cmd_P();
void cmd_r();
void cmd_s();
void cmd_g();
void iniciar_HashGames();
void iniciar_HashTeams();
unsigned int hash(char *nome);
bool equipa_nao_existe(char *equipa);
void MergeSort(EquipasOrd** headteam);
EquipasOrd* SortedMerge(EquipasOrd* a, EquipasOrd* b);
void FrontBackSplit(EquipasOrd* source, EquipasOrd** frontRef, EquipasOrd** backRef);
void FreeMemory();

#endif