#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

#define M_HASH 1931

ht_games init_ht_g(int m) {
	int i;
	ht_games l;
	l = can_fail_malloc(m *sizeof(List_Games));
	for (i = 0; i < m; i++){
		l[i] = init_list();
	}
	return l;
}

int hash(char * nome, int m){
	int h = 0, a = 31415, b = 27183;
	for (; *nome != '\0'; nome++){
		a = a*b % m;
		h = (a*h + *nome) % m;
	}
	return h;
}

void insert_ht_g(ht_games l, char * jogo, char * eq1, char * eq2, int sc1, int sc2){
	int i;
	i = hash(jogo, M_HASH);
	add_end_game(l[i], jogo, eq1, eq2, sc1, sc2);
}

Game * search_ht_g(ht_games l, char * nome){
	int i;
	Game * n;
	i = hash(nome, M_HASH);
	n = search_game(l[i], nome);
	return n;
}

void change_sc_ht_g(ht_games l, char * nome, int score1, int score2){
	int i;
	i = hash(nome, M_HASH);
	change_score(l[i], nome, score1, score2);
}

void remove_ht_g(ht_games l, char * nome){
	int i;
	i = hash(nome, M_HASH);
	remove_game(l[i], nome);
}

void destroy_ht_g(ht_games hash_table){
	int i;
	for (i = 0; i < M_HASH; i++){
		free_all_games(hash_table[i]);
	}
	free(hash_table);
}
