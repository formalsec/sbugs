#ifndef UTILITIES_H
#define UTILITIES_H

#include "structs.h"

/* Hash function for strings */
int hash(char *name, int sz);

/* Returns the team that won the game, if any */
teams *get_winner(games *game);

/* Returns the game with the given name.
 * If none exists, returns null */
games *search_game(char *name, games **games_ht);

/* Returns the team with the given name.
 * If none exists, returns null */
teams *search_team(char *name, teams **teams_ht);

/* Returns the # of victories of the team */
int count_wins(teams *team);

/* Checks if two teams are lexicographically ordered */
short int ab_ordered(int team1, int team2, teams **teams_contig);

/* Basic merge sort. Takes the sort criterion as last argument.
 * Teams_contig allows for access to the teams' names */
void merge_sort(int v[], teams **teams_contig, int l, int r,
				short int crit(int, int, teams**));

/* Merges the two (sorted) halves of the given array */
void merge(int v[], teams **teams_contig, int l, int m, int r,
		   short int crit(int, int, teams**));

/* Frees all memory dynamically allocated throoughout the program.
 * For use at exit */
void clear_system(games **games_ht, game_names **names_pt, teams **teams_ht,
				  teams **teams_contiguous, int *teamc);

#endif /* UTILITIES_H */
