#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "structs_auxiliary.h"


int hash(char *name, int sz) {
	int h, a = 31415, b = 27183;

	for (h = 0; *name != '\0'; name++, a = a*b % (sz-1))
		h = (a*h + *name) % sz;

	return h;
}


teams *get_winner(games *game) {
	teams *winner = NULL;

	if (game->sc[0] > game->sc[1]) {
		winner = game->team1;
	}
	else if (game->sc[1] > game->sc[0]) {
		winner = game->team2;
	}

	return winner;
}


games *search_game(char *name, games **games_ht) {
	int hash_id = hash(name, GAMES_SZ);
	games *curr = games_ht[hash_id];

	/* Move forward until NULL or the game with this name is found */
	while ((curr != NULL) && (strcmp(curr->name->name, name) != 0) )
		curr = curr->next;

	return curr;
}


teams *search_team(char *name, teams **teams_ht) {
	int hash_id = hash(name, TEAMS_SZ);
	teams *curr = teams_ht[hash_id];

	/* Move forward until NULL or the team with this name is found */
	while ((curr != NULL) && (strcmp(curr->name, name) != 0))
		curr = curr->next;

	return curr;
}


int count_wins(teams *team) {

	return team->wins;
}


short int ab_ordered(int t1, int t2, teams **teams_contig) {

	return strcmp(teams_contig[t1]->name, teams_contig[t2]->name) <= 0;
}


void merge_sort(int v[], teams **teams_contig, int l, int r,
				short int crit(int, int, teams**) ) {
	int m = (l+r)/2;

	/* Nothing to merge/sort if array size is < 2 */
	if (r-l+1<2)
		return;

	/* Split the array into 2, sorting each individually */
	merge_sort(v, teams_contig, l, m, crit);
	merge_sort(v, teams_contig, m+1, r, crit);
	merge(v, teams_contig, l, m, r, crit);
}


void merge(int v[], teams **teams_contig, int l, int m, int r,
		   short int crit(int, int, teams**) ) {
	int i=l, j=m+1, k=0;
	int	*aux = can_fail_malloc((r-l+1)*sizeof(int));
 
	/* Copy the values of v into aux, adding the smallest value between
	 * v[i] (first half) and v[j] (second half) in each iteration */
	for (; (i<=m) && (j<=r); k++) {

		if (crit(v[i], v[j], teams_contig))
			aux[k] = v[i++];
		else
			aux[k] = v[j++];
	}

	/* Insert the remaining values of the array into aux if
	 * the main cycle ended prematurely (due to i>m or j>r) */
	while (i<=m)
		aux[k++] = v[i++];

	while (j<=r)
		aux[k++] = v[j++];

	/* Copy the sorted values of aux back into the original array */
	for (i=0; i<r-l+1; i++)
		v[l+i] = aux[i];

	free(aux);
}


void clear_system(games **games_ht, game_names **names_pt, teams **teams_ht,
				  teams **teams_contiguous, int *teamc) {
	int i;

	if (*names_pt != NULL) {
		int hash_id;
		games *curr_game;
		game_names *curr_name = (*names_pt)->last->prev;

		/* free the memory reserved for each name and its
		 * respective game, traversing the list backwards */
		for (; curr_name != NULL; curr_name = curr_name->prev) {
			hash_id = hash(curr_name->next->name, GAMES_SZ);
			curr_game = curr_name->next->game;

			elim_game(curr_game, &games_ht[hash_id], names_pt);
		}

		/* last name/game to delete is the head of *names_pt */
		hash_id = hash((*names_pt)->name, GAMES_SZ);
		curr_game = (*names_pt)->game;
		elim_game(curr_game, &games_ht[hash_id], names_pt);
	}

	/* free the memory allocated for each team */
	for (i=0; i<*teamc; i++) {

		free(teams_contiguous[i]->name);
		free(teams_contiguous[i]);
	}

	/* free the memory reserved for the arrays of each structure */
	free(games_ht);
	free(teams_ht);
	free(teams_contiguous);
}