#ifndef GAMES_DLL
#define GAMES_DLL

#include "game.h"


/* Nodo da lista */
typedef struct stru_node {
	struct stru_node * next, * previous;
	Game game;
} * dl_node;

/* Lista */
typedef struct dl_list {
	dl_node head, last;
} * dlst;


/* Funcoes relacionadas com a lista */
dlst mk_list();
dl_node find_node(dlst list, Game game);
void rm_node(dlst list, Game game);
void add_last(dlst list, Game game);
void printGames(dlst list, int c);
void dll_destroy(dlst list);

#endif