#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utilities.h"
#include "structs_auxiliary.h"

/* Adds a new game to the system */
void new_game(games **games_ht, game_names **name_list, teams **teams_ht, int inp);

/* Lists the names of all games, along with the
 * participating teams and their respective scores */
void list_games(game_names *names, int inp);

/* Lists the same information as list_games,
 * but only of a specific game, if it exists*/
void find_game(games **games_ht, int inp);

/* Eliminates a game from the system */
void del_game(games **games_ht, game_names **names, int inp);

/* Changes the scores in a game */
void change_score(games **games_ht, int inp);

/* Adds a new team to the system */
teams **new_team(teams **teams_ht, teams **teams_contiguous,
				 int *teamc, int *teams_sz, int inp);

/* Lists the name and the number of wins of a team */
void find_team(teams **teams_ht, int inp);

/* Lists the name of the teams with the highest
 * number of wins, along with this number */
void best_teams(teams **team_contig, int teamc, int inp);


/* Provides the commands that perform each main function */
int main() {
	int inp=0, teamc=0, *teamc_pt = &teamc,
		teams_sz = TEAMS_SZ, *teams_sz_pt = &teams_sz; /* size of teams_contiguous */

	games **games_ht = can_fail_calloc(GAMES_SZ, sizeof(games *)); /* hash table for games*/
	game_names *names = NULL, **names_pt = &names; /* linked list of games */
	teams **teams_ht = can_fail_calloc(TEAMS_SZ, sizeof(teams *)), /* hash table for teams */
			/* stores the teams contiguously */
		  **teams_contiguous = can_fail_calloc(TEAMS_SZ, sizeof(teams *));
	char command;

	while ((command = getchar()) != 'x') {

		switch(command) {

			case 'a':
				inp++;
				new_game(games_ht, names_pt, teams_ht, inp);
				break;

			case 'l':
				inp++;
				list_games(names, inp);
				break;

			case 'p':
				inp++;
				find_game(games_ht, inp);
				break;

			case 'r':
				inp++;
				del_game(games_ht, names_pt, inp);
				break;

			case 's':
				inp++;
				change_score(games_ht, inp);
				break;

			case 'A':
				inp++;
				teams_contiguous = new_team(teams_ht, teams_contiguous,
											teamc_pt, teams_sz_pt, inp);
				break;

			case 'P':
				inp++;
				find_team(teams_ht, inp);
				break;

			case 'g':
				inp++;
				best_teams(teams_contiguous, teamc, inp);
				break;
		}
	}
	clear_system(games_ht, names_pt, teams_ht, teams_contiguous, teamc_pt);

	return 0;
}


void new_game(games **games_ht, game_names **name_list, teams **teams_ht, int inp) {
	int hash_id, sc1, sc2;
	char name[NAME_SIZE], t1[NAME_SIZE], t2[NAME_SIZE];
	games *new;
	teams *team1, *team2, *winner;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, t1, t2, &sc1, &sc2);

	if (search_game(name, games_ht) != NULL) {
		printf("%d Jogo existente.\n", inp);
		return;
	}

	if ( ((team1 = search_team(t1, teams_ht)) == NULL) ||
		 ((team2 = search_team(t2, teams_ht)) == NULL) ) {
		printf("%d Equipa inexistente.\n", inp);
		return;
	}

	hash_id = hash(name, GAMES_SZ);
	/* the new game will be at the end of the linked list in the hashtable */
	new = new_game_at_end(&games_ht[hash_id]);

	/* create the game's name */
	new_name(name, name_list);
	/* add the last created name to the new game */
	new->name = (*name_list)->last;
	new->name->game = new;

	/* Link the teams and the game with each other */
	new->team1 = team1;
	new->team2 = team2;

	/* Set the scores */
	new->sc[0] = sc1;
	new->sc[1] = sc2;

	winner = get_winner(new);

	if (winner != NULL)
		winner->wins++;
}	


void list_games(game_names *names, int inp) {

	/* Iterate through the list of names, accessing
	 * the corresponding game on the hashtable */
	for (; names != NULL; names = names->next) {
		games *game = names->game;

		printf("%d %s %s %s %d %d\n", inp, game->name->name, game->team1->name,
				game->team2->name, game->sc[0], game->sc[1]);
	}
}


void find_game(games **games_ht, int inp) {
	char name[NAME_SIZE];
	games *game;

	scanf(" %[^:\n]", name);

	if ((game = search_game(name, games_ht)) == NULL) {
		printf("%d Jogo inexistente.\n", inp);
		return;
	}

	printf("%d %s %s %s %d %d\n", inp, game->name->name, game->team1->name,
			game->team2->name, game->sc[0], game->sc[1]);
}


void del_game(games **games_ht, game_names **names_pt, int inp) {
	int hash_id;
	char name[20];
	games *game, **head;

	scanf(" %[^\n]", name);

	/* Find the game and the head of its linked list, to then delete it*/
	game = search_game(name, games_ht);

	if (game == NULL) {
		printf("%d Jogo inexistente.\n", inp);
		return;
	}

	hash_id = hash(name, GAMES_SZ);
	head = &games_ht[hash_id];
	elim_game(game, head, names_pt);
}


void change_score(games **games_ht, int inp) {
	int sc1, sc2;
	char name[NAME_SIZE];
	games *game;
	teams *winner;

	scanf(" %[^:\n]:%d:%d", name, &sc1, &sc2);

	if ((game = search_game(name, games_ht)) == NULL) {
		printf("%d Jogo inexistente.\n", inp);
		return;
	}

	winner = get_winner(game);

	if (winner != NULL)
		winner->wins--;

	game->sc[0] = sc1;
	game->sc[1] = sc2;

	winner = get_winner(game);

	if (winner != NULL)
		winner->wins++;
}


teams **new_team(teams **teams_ht, teams **teams_contiguous, int *teamc,
				 int *teams_sz, int inp) {
	int hash_id;
	char name[NAME_SIZE];
	teams *new;

	scanf(" %[^:\n]", name);

	if (search_team(name, teams_ht) != NULL) {
		printf("%d Equipa existente.\n", inp);
		return teams_contiguous;
	}

	hash_id = hash(name, TEAMS_SZ);
	/* place the new team the end of the linked list in the table */
	new = new_team_at_end(&teams_ht[hash_id]);
	new->name = can_fail_malloc((strlen(name)+1) * sizeof(char));
	strcpy(new->name, name);

	/* If the number of games is larger than
	 * the array's current capacity, expand it */
	if (*teamc >= *teams_sz) {
		(*teams_sz) *= 2;
		teams_contiguous = can_fail_realloc(teams_contiguous, (*teams_sz) * sizeof(teams *));
	}
	/* store the team into an array that holds them contiguously */
	teams_contiguous[(*teamc)++] = new;

	return teams_contiguous;
}


void find_team(teams **teams_ht, int inp) {
	char name[NAME_SIZE];
	teams *team;

	scanf(" %[^:\n]", name);

	if ((team = search_team(name, teams_ht)) == NULL) {
		printf("%d Equipa inexistente.\n", inp);
		return;
	}

	printf("%d %s %d\n", inp, name, count_wins(team));
}


void best_teams(teams **teams_contig, int teamc, int inp) {
	/* bestc holds the number of teams with the most wins */
	int i, k, most_wins=0, bestc=0, *team_wins;
	int *best;

	/* print nothing if there are no teams */
	if (teamc == 0)
		return;

	/* holds the number of wins of each team in **teams */
	team_wins = can_fail_malloc(teamc * sizeof(int));

	/* count the number of teams with the most wins */
	for (i=0; i<teamc; i++) {
		int winc;

		/* if the team has more than the largest amount of wins found so far,
		 * reset the counter and set the new highest */
		if ((winc = count_wins(teams_contig[i])) > most_wins) {

			most_wins = winc;
			bestc = 1;
		}
		/* if it has as many as the highest amount, increment the counter */
		else if (winc == most_wins) {
			bestc++;
		}

		team_wins[i] = winc;
	}

	/* holds the "IDs" of the teams with most wins */
	best = can_fail_malloc(bestc * sizeof(int));

	for (i=0, k=0; k<bestc; i++) {

		/* if this team has the most wins, put it in *best */
		if (team_wins[i] == most_wins)
			best[k++] = i;
	}

	merge_sort(best, teams_contig, 0, bestc-1, ab_ordered);
	printf("%d Melhores %d\n", inp, most_wins);

	for (i=0; i<bestc; i++)
		printf("%d * %s\n", inp, teams_contig[best[i]]->name);

	free(team_wins);
	free(best);
}
