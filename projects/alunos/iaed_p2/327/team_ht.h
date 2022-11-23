#ifndef TEAM_HT_H
#define TEAM_HT_H

#include "team.h"

/* Constants used in hash functions. */
#define HASH_NO_1 27183
#define HASH_NO_2 31415

typedef struct {
	int M, N;
	team ** ht;
} team_ht;

/* A hash function for teams. */
int hash_team(char * name, int M);
/* Initializes a team hashtable. */
void team_ht_init(team_ht * teams, int max);
/* Inserts a team into a hashtable. */
void team_ht_insert(team_ht * teams, team * team);
/* Deletes a team from a hashtable. */
team * team_ht_delete(team_ht * teams, char * name);
/* Searches for a team in a hashtable. */
team * team_ht_search(team_ht * teams, char * name);
/* Finds and prints the teams that have won the most games in a hashtable. */
void team_ht_print_most_wins(int NL, team_ht * teams);
/* Espands a team hashtable. */
void team_ht_expand(team_ht * teams);
/* Frees a team hashtable and the teams within. */
void team_ht_free(team_ht * teams);

#endif