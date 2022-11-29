#ifndef _TEAM_HASHTABLE_H_
#define _TEAM_HASHTABLE_H_ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team.h"

typedef struct team_hashtable {
	int size;
	int count;
	Team *team_table;
} Team_Hashtable;



/*
Inicializa cada uma das posicoes da hashtable relativa a 'team'.
Retorno: vazio.
*/
void init_team_hashtable_table(Team_Hashtable *TH);


/*
Inicializa a hashtable com o tamanho atual.
Retorno: ponteiro para hashtable relativa a 'team'.
*/
Team_Hashtable *init_team_hashtable(int team_hashtable_size);


/*
Insere a referencia para a equipa na hashtable, dado o nome como argumento.
Retorno: vazio.
*/
void insert_team_hashtable(Team_Hashtable *TH, Team team);


/*
Expande o tamanho da hashtable relativa a 'team'.
Retorno: vazio.
*/
void expand_team_hashtable(Team_Hashtable *TH);


/*
Procura a referencia da equipa, dado o nome como argumento.
Retorno: ponteiro para a equipa.
*/
Team search_team_hashtable(Team_Hashtable *TH, char *name);


/*
Liberta na hashtable relativa a 'team', o espaco alocado pela posicao dada como argumento.
Retorno: vazio.
*/
void free_team_hashtable_table(Team_Hashtable *TH, int index);


/*
Liberta o espaco alocado pela hashtable relativa a 'team'.
Retorno: vazio.
*/
void free_teams_hashtable(Team_Hashtable *TH);

#endif