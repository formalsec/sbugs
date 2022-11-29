#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table_eq.h"
#include "hash_table.h"

#define M_HASH 1931

ht_teams init_ht_t(int m) {
	int i;
	ht_teams l;
	l = can_fail_malloc(m *sizeof(List_Teams));
	for (i = 0; i < m; i++){
		l[i] = init_list_t();
	}
	return l;
}

void insert_ht_t(ht_teams l, char * nome){
	int i;
	i = hash(nome, M_HASH);
	add_end_team(l[i], nome);
}

Team * search_ht_t(ht_teams l, char * nome){
	int i;
	Team * n;
	i = hash(nome, M_HASH);
	n = search_team(l[i], nome);
	return n;
}

void change_wins_ht_t(ht_teams l, char * nome, int v){
	int i;
	i = hash(nome, M_HASH);
	change_wins(l[i], nome, v);
}

void destroy_ht_t(ht_teams hash_table){
	int i;
	for (i = 0; i < M_HASH; i++){
		free_all_teams(hash_table[i]);
	}
	free(hash_table);
}


int max_wins(ht_teams lst_eq){
	int max = 0, i;
	Team * eq;
	for (i = 0; i < M_HASH; i++){
		if (lst_eq[i]){
			eq = lst_eq[i]->head;
			while (eq){
				if (eq->vitorias > max){
					max = eq->vitorias;
				}
				eq = eq->next;
			}
		}
	}
	return max;
}
