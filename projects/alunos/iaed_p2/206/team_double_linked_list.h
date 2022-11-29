#ifndef _TEAM_DOUBLE_LINKED_LIST_H_
#define _TEAM_DOUBLE_LINKED_LIST_H_

#include "team.h"

typedef struct team_node {
	Team team;
	struct team_node *next, *previous;
} Team_Node;

typedef struct {
	Team_Node *head, *last;
} Team_List;


/*
Inicializa a lista duplamente ligada relativa a 'team'.
Retorno: ponteiro para a lista relativa a 'team'.
*/
Team_List *init_team_list();


/*
Adiciona a referencia para uma equipa, dado o nome como argumento, na ultima posicao da lista.
Retorno: vazio.
*/
void add_last_team_list(Team_List *TL, Team team);


/*
Calcula o tamanho da lista duplamente ligada relativa a 'team'.
Retorno: inteiro com o tamanho da lista.
*/
int length_team_list(Team_List *TL);


/*
Liberta o espaco da memoria ocupada pelo no 'team'.
Retorno: vazio.
*/
void free_team_node(Team_Node *team_node);


/*
Liberta o espaco da memoria ocupado pelo lista duplamente ligada relativa a 'team'.
Retorno: vazio.
*/
void free_teams_list(Team_List *TL);

#endif