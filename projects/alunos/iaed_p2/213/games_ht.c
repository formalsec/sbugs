#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include "games_ht.h"


/* Inicializa hashtable de jogos */
Game * G_init() {
	int i;

	/* Aloca memoria para a tabela de jogos */
	Game * games = can_fail_malloc(SIZE_HT*sizeof(Game));

	/* Inicializa ponteiros para jogos a NULL */
	for (i = 0; i < SIZE_HT; i++)
		games[i] = NULL;

	return games;
}


/* Insere jogo na tabela de jogos */
void G_insert(Game * games, Game g) {
	int i = hash(g->name, SIZE_HT);

	/* Coloca no espaco livre seguinte */
	while (games[i])
		i = (i+1) % SIZE_HT;

	games[i] = g;
}


/* Funcao auxiliar: Procura jogo na tabela e devolve o indice */
int G_index(Game * games, char * name) {
	int i = hash(name, SIZE_HT);

	/* Procura nos espacos seguintes */
	while (games[i]) {

		/* Encontrou jogo */
		if (eq(games[i]->name, name))
			return i;

		else
			i = (i+1) % SIZE_HT;
	}

	/* Nao encontrou jogo */
	return -1;
}


/* Procura jogo na tabela e devolve o endereco */
Game G_search(Game * games, char * name) {
	int i = G_index(games, name);

	if (i != -1)
		return games[i];

	/* Nao existe o jogo */
	else
		return NULL;
}


/* Elimina jogo da tabela */
void G_delete(Game * games, char * name) {
	Game aux;
	int j;

	/* Encontra o jogo na hashtable */
	int i = G_index(games, name);

	/* Nao existe jogo */
	if (i == -1)
		return;

	/* Liberta memoria */
	freeGame(games[i]);
	games[i] = NULL;

	/* Re-insere elementos seguintes */
	for (j = (i+1) % SIZE_HT; games[j]; j = (j+1) % SIZE_HT) {
		aux = games[j];
		games[j] = NULL;
		G_insert(games, aux);
	}
}


/* Destroi tabela e liberta espaco */
void G_destroy(Game * games) {
	int i;
	for (i = 0; i < SIZE_HT; i++)
		if (games[i])
			freeGame(games[i]);

	free(games);
}
