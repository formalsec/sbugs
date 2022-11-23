#ifndef _HASHTEAM_H
#define _HASHTEAM_H

#include <stdio.h>
#include <stdlib.h>
#include "Team.h"
#define M 2371

typedef struct node* teamlink;

struct node {				
	TEAM TEAM;
	teamlink next;
};



teamlink push_team(teamlink head, TEAM i);				/*Adiciona a equipa i ao inicio da hashtable das equipas*/
teamlink remove_TEAM(teamlink head, teamKey k);			/*Remove a equipa com nome k da hashtable das equipas*/
TEAM search_list_team(teamlink heads, teamKey key);		/*Retorna a equipa com nome key caso presente na hashtable*/					
void destroy_list_team(teamlink head);					/*Apaga as equipas presentes numa coluna da Hashtable */
teamlink* HASHinit_team();								/*Inicializa a Hashtable das equipas alocando a memoria necessaria*/
int hash_team(char *v);									/*Funcao Hash presente nos Powerpoints*/
teamlink NEWNode_team(TEAM i, teamlink next);			/*Cria uma nova entrada,alocando a memoria necessaria para a estrutura teamlink*/
void DELETENode_team(teamlink node);					/*Apaga uma entrada da hashtable,libertando a memoria alocada para esta*/
void insert_team(teamlink* heads, TEAM TEAM);			/*Insere uma equipa no indice dado pela funcao Hash*/
TEAM search_team(teamlink* heads, teamKey k);			/*Retorna a equipa com nome k presente na hashtable*/					
void destroy_hash_team(teamlink* heads);				/*Apaga a Hashtable, libertando toda a memoria que foi alocada para esta*/

#endif