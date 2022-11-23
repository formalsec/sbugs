#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "function_hashtable.h"
#include "game_hashtable.h"

void init_game_hashtable_table(Game_Hashtable *GH) {

	int i;
	/* Aloca a memoria necessaria para o conteudo das posicoes da hashtable. */
	GH->game_table = can_fail_malloc(sizeof(Game) * GH->size);

	/* Preenche todas as posicoes da hashtable a NULL. */
	for (i = 0; i < GH->size; i++) {
		GH->game_table[i] = NULL;
	}
}

Game_Hashtable *init_game_hashtable(int game_hashtable_size) {

	Game_Hashtable *GH = can_fail_malloc(sizeof(struct game_hashtable));
	GH->size = game_hashtable_size;
	GH->count = 0;
	init_game_hashtable_table(GH);

	return GH;
}

void insert_game_hashtable(Game_Hashtable *GH, Game game) {

	/* O index recebe a posicao da hashtable onde vai inserir a referencia para o jogo. */
	int index = HASH(game->name, GH->size), position = index;

	/* Se o contador de elementos atingir ao limite proposto, a hashtable aumenta o seu tamanho. */
	if (GH->count > EXPANDING_SIZE(GH)) {
		expand_game_hashtable(GH);
	}

	/* Procura a posicao na hashtable para inserir o elemento. */
	while (GH->game_table[position] != NULL) {
		position = (index++) % (GH->size);
	}

	GH->game_table[position] = game;
	GH->count++;
}

void expand_game_hashtable(Game_Hashtable *GH) {

	int i, old_size = GH->size;
	Game *aux_game_table = GH->game_table;

	GH->count = 0;
	GH->size = old_size * EXPAND_CONSTANT_VARIABLE;

	init_game_hashtable_table(GH);

	/* Insere os elementos antigos nas mesmas posicoes da hashtable. */
	for (i = 0; i < old_size; i++) {
		if (aux_game_table[i] != NULL) {
			insert_game_hashtable(GH, aux_game_table[i]);
		}
	}

	free(aux_game_table);
}

Game search_game_hashtable(Game_Hashtable *GH, char *name) {

	int index = HASH(name, GH->size), position = index;

	/* Procura na hashtable a referencia para o nome jogo dado como argumento. */
	while (GH->game_table[position] != NULL) {
		if (strcmp(GH->game_table[position]->name, name) == 0) {
			return GH->game_table[position];
		}

		/* Se nao encontrar a primeira, avanca para a proxima posicao. */
		position = (index++) % (GH->size);
	}

	return NULL;
}

void remove_game_hashtable(Game_Hashtable *GH, char *name) {

	int i, index = HASH(name, GH->size), position = index;
	Game aux_game;

	while (GH->game_table[position] != NULL) {

		if (strcmp(GH->game_table[position]->name, name) == 0) {
			
			/* Liberta o espaco ocupado na posicao da hashtable ocupada pelo jogo. */
			free_game_hashtable_table(GH, position);
			/* Coloca essa posicao a NULL. */
			GH->game_table[position] = NULL;

			/* Reeinsere os elementos seguintes uma posicao acima na hashtable. */
			for (i = position; GH->game_table[i] != NULL; i = (index++) % (GH->size)) {
				aux_game = GH->game_table[i];
				GH->game_table[i] = NULL;
				insert_game_hashtable(GH, aux_game);
			}

			break;

		} else {

			position = (index++) % (GH->size);
		}
	}

	if (GH->game_table[position] == NULL) {
		return;
	}
}

void free_game_hashtable_table(Game_Hashtable *GH, int index) {

	free(GH->game_table[index]->name);
	free(GH->game_table[index]->team1);
	free(GH->game_table[index]->team2);
	free(GH->game_table[index]);
}

void free_games_hashtable(Game_Hashtable *GH) {

	int i = 0;

	while(GH->game_table[i] != NULL) {
		free_game_hashtable_table(GH, i);
		i++;
	}

	free(GH->game_table);
	free(GH);
}