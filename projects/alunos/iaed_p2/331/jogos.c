#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogos.h"

List_Games * init_list(){
	List_Games * l;
	l = can_fail_malloc(sizeof(List_Games));
	l->head = NULL;
	l->last = NULL;
	return l;
}

Game * new_game(char * j, char * eq1, char * eq2, int sc1, int sc2){
	Game * new;
	new = can_fail_malloc(sizeof(Game));
	new->jogo_nome = can_fail_malloc(sizeof(char)*(strlen(j) + 1));
	strcpy(new->jogo_nome, j);
	new->nome_eq1 = can_fail_malloc(sizeof(char)*(strlen(eq1) + 1));
	strcpy(new->nome_eq1, eq1);
	new->nome_eq2 = can_fail_malloc(sizeof(char)*(strlen(eq2) + 1));
	strcpy(new->nome_eq2, eq2);
	new->score1 = sc1;
	new->score2 = sc2;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

Game * add_end_game(List_Games * l, char * j, char * eq1, char * eq2, int sc1, int sc2){
	Game * new;
	new = new_game(j, eq1, eq2, sc1, sc2);
	new->prev = l->last;
	if (l->last){
		l->last->next = new;
	}
	else{
		l->head = new;
	}
	l->last = new;
	return new;
}


Game * search_game(List_Games * l, char * nome_j){
	Game * t = l->head;
	while(t != NULL){

		if (!strcmp(t->jogo_nome, nome_j)){
			return t;
		}
		t = t->next;
	}
	return NULL;
}

void change_score(List_Games * l, char * jogo, int score1_new, int score2_new){
	Game * n;
	n = search_game(l, jogo);
	n->score1 = score1_new;
	n->score2 = score2_new;
}

void free_game(Game * n){
	free(n->jogo_nome);
	free(n->nome_eq1);
	free(n->nome_eq2);
	free(n);
}

void remove_game(List_Games * l, char * jogo){
	Game * t;
	t = search_game(l, jogo);
	if (t->prev == NULL){
		l->head = t->next;
	}
	else{
		t->prev->next = t->next;
	}
	if (t->next == NULL){
		l->last = t->prev;
	}
	else{
		t->next->prev = t->prev;
	}
	free_game(t);
}

Game * remove_first_game(Game * head){
	Game * aux;
	aux = head->next;
	free_game(head);
	return aux;
}

void free_all_games(List_Games * l){
	while(l->head != NULL){
		l->head = remove_first_game(l->head);
	}
	free(l);
}

void print_game(Game * n){
	printf("%s %s %s %i %i\n", n->jogo_nome, n->nome_eq1, n->nome_eq2, n->score1, n->score2);
}
