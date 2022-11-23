#ifndef _DLINKED_H
#define _DLINKED_H

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"


typedef struct Node *Link;

struct Node {						/*Cada node da lista ligada contem Jogos*/
	GAME Game;
	Link next;
	Link prev;
};

typedef struct MasterNode {
	int n_elementos;			/*numero de elementos presentes na lista*/
	Link head;
	Link tail;
}* GameLinkedList;

GameLinkedList list_init();						/*inicializa a lista duplamente ligada, alocando a memoria da estrutura "MasterNode"*/
void delete_node(Link node);						/*apaga uma entrada da lista, libertando a sua memoria alocada*/
int get_n_elementos(GameLinkedList list); 			/*Retorna o numero de elementos presentes na lista list */
int is_empty(GameLinkedList list);					/*Retorna se a lista e ou nao vazia*/
GAME get_GAME(Link h);								/*Recebe um node e retorna o Jogo caso presente*/
Link search_list(GameLinkedList list, gameKey key);/*Procura um node onde o jogo com gameKey key esteja presente */
void append(GameLinkedList list, GAME i);				/*Junta o jogo i no final da lista list*/
void pop(GameLinkedList list);							/*Apaga o jogo presente no inicio da lista*/
void remove_last(GameLinkedList list);					/*Apaga o jogo presente no final da lista*/
void remove_Game_list(GameLinkedList list, gameKey k);	/*Apaga o jogo com gameKey k*/
void destroy_list(GameLinkedList list);					/*Apaga a lista, libertando a sua memoria alocada */

#endif