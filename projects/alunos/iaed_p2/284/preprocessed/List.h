#ifndef LIST_H
#define LIST_H

#include "Team.h"
#include "Game.h"

/* enum para utilizar na estrutura do no da lista */
enum Type { TEAM, GAME };

/*------------*\
 * Estruturas *
\*------------*/

/* estrutura do no da lista */
typedef struct stru_node {
	enum Type type;					/* tipo do no (jogo ou equipa) */
	union {
		team* t;					/* ponteiro para a estrutura da equipa */
		game* g;					/* ponteiro para a estrutura do jogo */
	} d;
	struct stru_node *prev, *next;	/* ponteiro para o no anterior/proximo */
} node;

/* estrutura do no da hash table */
typedef struct hash_node {
	node* n;						/* ponteiro para o no que esta representa */
	struct hash_node* next;			/* ponteiro para o proximo no da hash table */
} link;

/* estrutura de uma lista.
 * cada lista tem uma hash table associada */
typedef struct {
	node *head, *last;				/* ponteiros para os nos inicial e final */
	link** table;					/* lista de ponteiros
									(a hash table correspondente a lista */
} list;


/*--------------------*\
 * Funcoes principais *
\*--------------------*/

list* create_list();
void append(list* lst, node* text);
void delete(list* lst, node* n);
void free_list(list* lst);
node* STsearch(link** heads, char* text);

#endif /* LIST_H */

