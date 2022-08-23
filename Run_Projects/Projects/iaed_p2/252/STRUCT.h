#ifndef STRUCT_H
#define STRUCT_H
#define DIM_STR 1024


/* Header file que contem as estruturas utilizadas no projeto */

/* Estrutura de uma equipa*/
typedef struct str_node_team 
{
	struct str_node_team *next, *previous, *collision;
	char* nome;
	int vitorias;

} Equipa;


/* Estrutura de um jogo*/
typedef struct str_node_game 
{
	struct str_node_game *next, *previous, *collision;
	char* nome;
	char* equipa1;
	char* equipa2;
	int score1, score2;
} Jogo;


/* Lista duplamente ligada: 
  Aponta para primeiro e ultimo elemento da lista e tambem para pointeiros da hashtable*/
typedef struct
{
	struct str_node_team *head, *last, **hashtable;

} team_list;


typedef struct
{
	struct str_node_game *head, *last, **hashtable;

} game_list;


#endif
