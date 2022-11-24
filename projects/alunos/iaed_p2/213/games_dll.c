#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "games_dll.h"


/* Cria uma nova lista */
dlst mk_list() {
	dlst list = can_fail_malloc(sizeof(struct dl_list));
	list->head = list->last = NULL;
	return list;
}


/* Encontra o nodo que contem o jogo */
dl_node find_node(dlst list, Game game) {
	dl_node aux = list->head;

	while (aux) {

		/* Encontrado */
		if (eq(aux->game->name, game->name))
			return aux;

		aux = aux->next;
	}

	return NULL;
}


/* Remove o jogo da lista */
void rm_node(dlst list, Game game) {
	dl_node n = find_node(list, game);

	/* Jogo e o primeiro nodo da lista */
	if (n->previous == NULL)
		list->head = n->next;

	else
		n->previous->next = n->next;

	/* Jogo e o ultimo nogo da lista */
	if (n->next == NULL)
		list->last = n->previous;

	else
		n->next->previous = n->previous;

	free(n);
}


/* Adiciona jogo ao fim da lista */
void add_last(dlst list, Game game) {
	dl_node nn = can_fail_malloc(sizeof(struct stru_node));

	nn->previous = list->last;
	nn->next = NULL;
	nn->game = game;

	if (list->last)
		list->last->next = nn;

	/* Lista esta vazia */
	else 
		list->head = nn;

	list->last = nn;
}


/* Faz print de todos os jogos pela ordem em que foram introduzidos */
void printGames(dlst list, int c) {
	dl_node temp = list->head;

	while(temp) {
		printGame(temp->game, c);
		temp = temp->next;
	}
}


/* Destroi a lista, libertando a memoria */
void dll_destroy(dlst list) {

	while(list->head) {
		dl_node temp = list->head->next;
		free(list->head);
		list->head = temp;
	}
	
	free(list);
}
