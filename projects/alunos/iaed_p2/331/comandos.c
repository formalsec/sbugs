#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"

void cmd_a(int NL, char * j_nome, char * eq1_nome, char * eq2_nome, int s1, int s2, ht_games ht_j, 
	ht_teams ht_eq, List_Names * jogos_introduzidos){
	Game * n;
	Team * eq1, * eq2;
	n = search_ht_g(ht_j, j_nome);
	eq1 = search_ht_t(ht_eq, eq1_nome);
	eq2 = search_ht_t(ht_eq, eq2_nome);
	if (n){
		printf("%i Jogo existente.\n", NL);
	}
	else if (eq1 == NULL || eq2 == NULL) {
		printf("%i Equipa inexistente.\n", NL);
	}
	else {
		insert_ht_g(ht_j, j_nome, eq1_nome, eq2_nome, s1, s2);
		add_end_name(jogos_introduzidos, j_nome);
		if (s1 > s2){
			eq1->vitorias += 1;
		}
		else if (s2 > s1){
			eq2->vitorias += 1;
		}
	}
}

void cmd_A(int NL, char * nome, ht_teams ht_eq){
	Team * n;
	n = search_ht_t(ht_eq, nome);
	if (n) {
		printf("%i Equipa existente.\n", NL);
	}
	else{
		insert_ht_t(ht_eq, nome);
	}
}

void cmd_l(int NL, List_Names * j, ht_games ht_j){
	Name * t;
	Game * n;
	t = j->head;
	while (t){
		n = search_ht_g(ht_j, t->jogo);
		printf("%i ", NL);
		print_game(n);
		t = t->next;
	}
}

void cmd_p(int NL, char * nome, ht_games ht_j){
	Game * n;
	n = search_ht_g(ht_j, nome);
	if (n == NULL){
		printf("%i Jogo inexistente.\n", NL);
	}
	else{
		printf("%i ", NL);
		print_game(n);
	}
}

void cmd_r(int NL, char * nome, ht_games ht_j, List_Names * l_jogos, ht_teams ht_eq){
	Game * n;
	n = search_ht_g(ht_j, nome);
	if (n == NULL){
		printf("%i Jogo inexistente.\n", NL);
	}
	else {
		if (n->score1 > n->score2){
			change_wins_ht_t(ht_eq, n->nome_eq1, -1);
		}
		else if (n->score1 < n->score2){
			change_wins_ht_t(ht_eq, n->nome_eq2, -1);
		}
		remove_ht_g(ht_j, nome);
		remove_name(l_jogos, nome);
	}
}

void cmd_s(int NL, char * nome, int s1, int s2, ht_games ht_j, ht_teams ht_eq){
	Game * n;
	n = search_ht_g(ht_j, nome);
	if (n == NULL){
		printf("%i Jogo inexistente.\n", NL);
	}
	else {
		if (n->score1 > n->score2 && s1 < s2){
			change_wins_ht_t(ht_eq, n->nome_eq1, -1);
			change_wins_ht_t(ht_eq, n->nome_eq2, 1);
		}
		else if (n->score1 < n->score2 && s1 > s2){
			change_wins_ht_t(ht_eq, n->nome_eq1, 1);
			change_wins_ht_t(ht_eq, n->nome_eq2, -1);
		}
		else if (n->score1 > n->score2 && s1 == s2){
			change_wins_ht_t(ht_eq, n->nome_eq1, -1);
		}
		else if (n->score1 < n->score2 && s1 == s2){
			change_wins_ht_t(ht_eq, n->nome_eq2, -1);
		}
		else if (n->score1 == n->score2 && s1 > s2){
			change_wins_ht_t(ht_eq, n->nome_eq1, 1);
		}
		else if (n->score1 == n->score2 && s1 < s2){
			change_wins_ht_t(ht_eq, n->nome_eq2, 1);
		}
		change_sc_ht_g(ht_j, nome, s1, s2);
	}
}

void cmd_P(int NL, char * nome, ht_teams ht_eq){
	Team * eq;
	eq = search_ht_t(ht_eq, nome);
	if (eq == NULL) {
		printf("%i Equipa inexistente.\n", NL);
	}
	else {
		printf("%i ", NL);
		print_team(eq);
	}
}

void cmd_g(int NL, ht_teams ht_eq){
	int max, num;
	List_Names * res;
	if (!check_empty_ht_t(ht_eq)){
		max = max_wins(ht_eq);
		res = init_list_n();
		search_ht_t_wins(ht_eq, res, max);
		num = number_elem(res);
		mergesort(res, 0, num - 1);
		printf("%i Melhores %i\n", NL, max);
		print_teams(NL, res);
		free_all_names(res);
	}
}
