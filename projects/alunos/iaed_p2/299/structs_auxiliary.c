#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utilities.h"
#include "structs_auxiliary.h"


games *new_game_at_end(games **list) {
	games *new = can_fail_calloc(1, sizeof(games));

	/* if the list is null, the new game becomes it */
	if (*list == NULL) {

		*list = new;
		(*list)->last = new;
	}
		/* else, make the new game the new last */
	else {

		new->prev = (*list)->last;
		(*list)->last->next = new;
		(*list)->last = new;
	}
	return new;
}


teams *new_team_at_end(teams **list) {
	teams *current = *list;

	/* If the head is null, allocate memory to it and return it */
	if (current == NULL) {
		*list = can_fail_calloc(1, sizeof(teams));
		return *list;
	}

	/* Iterate through the list until the end is found */
	for (; 1; current = current->next) {

		if (current->next == NULL) {

			current->next = can_fail_calloc(1, sizeof(teams));
			return current->next;
		}
	}
}

void new_name(char *name, game_names **name_list) {
	game_names *new_last = can_fail_calloc(1, sizeof(game_names));

	new_last->name = can_fail_malloc((strlen(name)+1) * sizeof(char));
	strcpy(new_last->name, name);

	/* if the list is null, just make the new name its head */
	if (*name_list == NULL) {

		*name_list = new_last;
		(*name_list)->last = new_last;
		return;
	}

	/* the new name's previous is the old last */
	new_last->prev = (*name_list)->last;

	/* the old last's next is the new  IT CHANGES HERE*/
	(*name_list)->last->next = new_last;
	/* make the new name the last of the list*/
	(*name_list)->last = new_last;
}


void elim_game(games *game, games **head, game_names **names_pt) {
	teams *winner;

	/* remove the game from the linked list of games */
	if (game->prev == NULL) {
		*head = game->next;

		/* if the new head isn't null, make its previous null */
		if ((*head) != NULL) {
			(*head)->last = game->last;
		}
	}
	else {
		game->prev->next = game->next;

		if (game->next == NULL){
			(*head)->last = game->prev;
		}
	}

	if (game->next != NULL)
		game->next->prev = game->prev;

	winner = get_winner(game);

	if (winner != NULL)
		winner->wins--;

	/* free all the memory occupied by the game */
	free_game_pt(game, names_pt);
}


void del_name(game_names *name, game_names **name_list) {
	game_names *name_to_del = name;

	/* if it is the head of the name list */
	if (name_to_del->prev == NULL) {
		*name_list = name_to_del->next;

		/* if it is not the only name in the list, the next becomes the new head */
		if (*name_list != NULL) {

			(*name_list)->prev = NULL;
			/* pass pointer to last to the next name */
			(*name_list)->last = name_to_del->last;
		}
	}
	else {
		/* since it is not the head, change the previous' next */
		name_to_del->prev->next = name_to_del->next;

		/* if it is the last name, its previous becomes the new last */
		if (name_to_del->next == NULL) {
			(*name_list)->last = name_to_del->prev;
		}
			/* do not change the next if it is NULL */
		else {
			name_to_del->next->prev = name_to_del->prev;
		}
	}

	/* free the memory  */
	free(name_to_del->name);
	free(name_to_del);
}


void free_game_pt(games *game, game_names **name_list) {

	del_name(game->name, name_list);
	free(game);
}
