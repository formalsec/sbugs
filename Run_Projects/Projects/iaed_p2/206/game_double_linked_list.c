#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game_double_linked_list.h" 

Game_List *init_game_list() {

	Game_List *GL = malloc(sizeof(Game_List));
	/* Coloca a head e o last da lista a NULL (lista vazia). */
	GL->head = GL->last = NULL;
	return GL;
}

void add_last_game_list(Game_List *GL, Game game) {

	Game_Node *new_game_node = malloc(sizeof(Game_Node));
	/* Faz referencia ao elemento como sendo o ultimo da lista. */
	new_game_node->previous = GL->last;
	new_game_node->next = NULL;
	/* Aloca a memoria necessaria para o no do tipo 'game'. */
	new_game_node->game = malloc(sizeof(struct game_node));
	new_game_node->game->name = malloc(sizeof(char) * (strlen(game->name) + 1));
	new_game_node->game->team1 = malloc(sizeof(char) * (strlen(game->team1) + 1));
	new_game_node->game->team2 = malloc(sizeof(char) * (strlen(game->team2) + 1));
	new_game_node->game = game;

	if (GL->last != NULL) {
		/* Se existir outros nos na lista, adiciona o novo no a seguir do ultimo no da lista. */
		GL->last->next = new_game_node;
	} else {
		/* Caso contrario, adiciona o no na head da lista. */
		GL->head = new_game_node;
	}

	GL->last = new_game_node;
}

void remove_game_list(Game_List *GL, char *name) {

	/* Criacao de um no axuliar que aponta para a head da lista. */
	Game_Node *aux_game_node = GL->head;

	while (aux_game_node != NULL) {

		/* Enquanto a lista tiver nos, compara o nome dado com o nome do no. */
		if (strcmp(name, aux_game_node->game->name) == 0) {

			/* Se coincidir, faz o processo de remocao do no: */
			/* Se o no corresponder a head, a head passa a corresponder ao no seguinte. */
			if (aux_game_node->previous == NULL) {
				GL->head = aux_game_node->next;
			/* Caso contrario, o next do no anterior a ser removido passa a apontar para o next do 
			no seguinte.*/
			} else {
				aux_game_node->previous->next = aux_game_node->next;
			}

			/* Se o no corrsponder ao last da lista, o last passa a corresponder ao no anterior. */
			if (aux_game_node->next == NULL) {
				GL->last = aux_game_node->previous;
			/* Caso contrario, o previous do no seguinte a ser removido passa a apontar para o
			previous do no anterior. */
			} else {
				aux_game_node->next->previous = aux_game_node->previous;
			}

			/* Liberto a memoria do no auxiliar. */
			free_game_node(aux_game_node);

			/* So ha um no com o nome dado na lista. */
			break;

		/* Avanca para o no seguinte. */
		} else {
			aux_game_node = aux_game_node->next;
		}
	}
	return;
}

void free_game_node(Game_Node *game_node) {

	free(game_node);
}

void free_games_list(Game_List *GL) {

	while (GL->head) {
		Game_Node *aux_game_node = GL->head->next;
		free_game_node(GL->head);
		GL->head = aux_game_node;
	}

	free(GL);
}