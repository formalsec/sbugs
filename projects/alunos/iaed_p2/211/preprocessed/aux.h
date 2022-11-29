#include "teams.h"
#include "matches.h"
#ifndef IAED_P2_FINAL_AUX_H
#define IAED_P2_FINAL_AUX_H

/* inicializa as hash tables e listas ligadas dos jogos e equipas */
void inicialize_lists(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams * linked_teams, linked_list_matches * linked_matches);

/* devolve o indice da hash table atraves de uma string */
int hash(char *desc, int M);

/* altera as vitorias de duas equipas, com base no score antigo e no score novo */
void change_victories(node_team *n_team1, node_team *n_team2, int old_score[2], int new_score[2]);

/* algortimo merge sort */
void merge_sort(node_team *a[], node_team *aux[], int l, int r);

/* faz merge de dois vetores ordenados */
void merge(node_team *a[], node_team *aux[], int l, int m, int r);

/* devolve 1 se x for alfabeticamente menor que y e 0 caso contrario */
int less(char x[], char y[]);

/* destroi as hash tables e listas ligadas dos jogos e equipas */
void destroy(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams *linked_teams, linked_list_matches *linked_matches);

#endif
