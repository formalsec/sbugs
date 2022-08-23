#include <stdio.h>
#include <stdlib.h>
#include "doublelinked.h"


GameLinkedList list_init() {
	GameLinkedList list = malloc(sizeof(struct MasterNode)); /*aloca memoria para a estrutura MasterNode*/
	list->n_elementos = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}


Link add_node(Link prev, Link next, GAME game) {
	Link new = malloc(sizeof(struct Node)); /*aloca memoria para um node*/
	new->Game = game;
	new->prev = prev;						/*inicializa os parametros*/
	new->next = next;
	if (prev != NULL) prev->next = new;
	if (next != NULL) next->prev = new;
	return new;
}

void delete_node(Link node) {
	free(node);
}

int is_empty(GameLinkedList list) {
	return get_n_elementos(list) == 0; /*retorna 1 caso seja nula e 0 caso nao seja*/
}

GAME get_GAME(Link h) {
	if(h != NULL) return h->Game;
	return NULL;
}

int get_n_elementos(GameLinkedList list) {
	if (list != NULL) return list->n_elementos;
	return 0;
}

Link search_list(GameLinkedList list, gameKey key) {
	Link current;
    for (current = list->head; current != NULL; current = current->next) {
		if (eqgame(keygame(get_GAME(current)), key)) return current;
	}
	return NULL;
}



/*Adiciona ao fim da lista*/
void append(GameLinkedList list, GAME i) {
	Link newNode = add_node(list->tail, NULL, i);
	list->tail = newNode;
	if (list->head == NULL) list->head = newNode;
	list->n_elementos++;
}

/*Remove do inicio da lista*/
void pop(GameLinkedList list) {
    Link oldHead;
	if (list->head == NULL || is_empty(list)) return;
	oldHead = list->head;
	list->head = oldHead->next;
	if(list->head != NULL) list->head->prev = NULL;
	else list->tail = NULL;
	delete_node(oldHead);
	list->n_elementos--;
}

/*Remove do fim da lista*/
void remove_last(GameLinkedList list) {
    Link oldTail;
	if (list == NULL || is_empty(list)) return;
	oldTail = list->tail;
	list->tail = oldTail->prev;
	if (list->tail != NULL) list->tail->next = NULL;
	else list->head = NULL;
	delete_node(oldTail);
	list->n_elementos--;
}

/*Remove jogo com gameKey k*/
void remove_Game_list(GameLinkedList list, gameKey k) {
    Link current;
	
	if (list == NULL || is_empty(list)) return;
	
    current = search_list(list, k);
	
	if (current == list->head) pop(list);
	else if (current == list->tail) remove_last(list);
	else {
		
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete_node(current);
		list->n_elementos--;
		
	}
}

/*Apaga lista*/
void destroy_list(GameLinkedList list) {
	Link current, aux;
	if (list == NULL) return;
	if (list->n_elementos != 0)
    {
        for (current = list->head, aux = list->head->next; current != NULL; aux = current->next, delete_node(current), current = aux){}
	}
	free(list);	
}

