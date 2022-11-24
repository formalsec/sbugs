#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "team_ht.h"

/* A hash function for teams. */
int hash_team(char * v, int M) {
	int h, a, b;

	a = HASH_NO_1;
	b = HASH_NO_2;

	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;

	return h;
}

/* Initializes a team hashtable. */
void team_ht_init(team_ht * teams, int max) {
	int i;

	teams->M = max;
	teams->N = 0;
	teams->ht = can_fail_malloc(teams->M * sizeof(team*));

	for (i = 0; i < teams->M; i++)
		teams->ht[i] = NULL;

	return;
}

void team_ht_expand(team_ht * teams);

/* Inserts a team into a hashtable. */
void team_ht_insert(team_ht * teams, team * team) {
	char * name = team_name(team);
	int i = hash_team(name, teams->M);

	while (teams->ht[i] != NULL)
		i = (i+1) % teams->M;

	teams->ht[i] = team;

	if ((teams->N)++ > teams->M/2)
		team_ht_expand(teams);

	return;
}

/* Deletes a team from a hashtable. */
team * team_ht_delete(team_ht * teams, char * name) {
	int j, i = hash_team(name, teams->M);
	team * aux, * v;

	while (teams->ht[i] != NULL)
		if (team_eq(name, team_name(teams->ht[i])))
			break;
		else i = (i+1) % teams->M;

	if (teams->ht[i] == NULL)
		return teams->ht[i];
	/* Stores the item to be removed in aux. */
	aux = teams->ht[i];

	teams->ht[i] = NULL;
	teams->N--;

	for (j = (i+1) % teams->M; teams->ht[j] != NULL; j = (j+1) % teams->M, teams->N--) {
		v = teams->ht[j];
		teams->ht[j] = NULL;
		team_ht_insert(teams, v);
	}

	return aux;
}

/* Searches for a team in a hashtable. */
team * team_ht_search(team_ht * teams, char * name) {
	int i = hash_team(name, teams->M);

	while (teams->ht[i] != NULL)
		if (team_eq(name, team_name(teams->ht[i])))
			return teams->ht[i];
		else
			i = (i+1) % teams->M;
	return NULL;
}

/* Finds and prints the teams that have won the most games in a hashtable. */
void team_ht_print_most_wins(int line, team_ht * teams) {
	team * t;
	team ** lst = can_fail_malloc(teams->N * sizeof(team *));
	int num = 0, i, max_wins = 0;

	/* Finds the teams that have won the most games. */
	for (i = 0; i < teams->M; i++) {
		if ((t = teams->ht[i])) {
			if (t->wins > max_wins) {
				max_wins = t->wins;
				num = 0;
			}
			if (t->wins == max_wins) {
				lst[num] = t;
				num ++;
			}
		}
	}

	/* Sorts them. */
	qsort(lst, num, sizeof(team *), team_cmp);

	/* Prints a list of the teams found. */
	if (num > 0)
		printf("%d Melhores %d\n", line, max_wins);
	for (i = 0; i < num; i++)
		printf("%d * %s\n", line, team_name(lst[i]));

	free(lst);
	return;
}

/* Espands a team hashtable. */
void team_ht_expand(team_ht * teams) {
	int i;
	team ** t = teams->ht;

	team_ht_init(teams, teams->M * 2);
	for (i = 0; i < teams->M/2; i++)
		if (t[i] != NULL)
			team_ht_insert(teams, t[i]);

	free(t);
}

/* Frees a team hashtable and the teams within. */
void team_ht_free(team_ht * teams) {
	int i;

	for (i = 0; i < teams->M; i++)
		if (teams->ht[i])
			free_team(teams->ht[i]);

	free(teams->ht);
	free(teams);

	return;
}