#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nome_jogos.h"

#define key_desc(A) A
#define less_desc(A, B) (strcmp(key_desc(A), key_desc(B)) < 0)
#define M_HASH 1931

List_Names * init_list_n(){
	List_Names * l;
	l = malloc(sizeof(List_Names));
	l->head = NULL;
	l->last = NULL;
	return l;
}

Name * new_name(char * j){
	Name * new;
	new = malloc(sizeof(Name));
	new->jogo = malloc(sizeof(char)*(strlen(j) + 1));
	strcpy(new->jogo, j);
	new->next = NULL;
	new->prev = NULL;
	return new;
}

Name * add_end_name(List_Names * l, char * j){
	Name * new;
	new = new_name(j);
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

Name * search_name(List_Names * l, char * nome_j){
	Name * t = l->head;
	while(t != NULL){
		if (!strcmp(t->jogo, nome_j)){
			return t;
		}
		t = t->next;
	}
	return NULL;
}

void free_name(Name * n){
	free(n->jogo);
	free(n);
}

void remove_name(List_Names * l, char * jogo){
	Name * t;
	t = search_name(l, jogo);
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
	free_name(t);
}

Name * remove_first_name(Name * head){
	Name * aux;
	aux = head->next;
	free_name(head);
	return aux;
}

void free_all_names(List_Names * l){
	while(l->head != NULL){
		l->head = remove_first_name(l->head);
	}
	free(l);
}

void print_teams(int NL, List_Names * l){
	Name * eq;
	eq = l->head;
	while(eq) {
		printf("%i * %s\n", NL, eq->jogo);
		eq = eq->next;
	}
}

void search_teams_wins(List_Teams * lst_eq, List_Names * l, int max){
	Team * eq;
	if (lst_eq){
		eq = lst_eq->head;
		while (eq){
			if (eq->vitorias == max){
				add_end_name(l, eq->nome_eq);
			}
			eq = eq->next;
		}
	}	
}

void search_ht_t_wins(ht_teams l, List_Names * res, int max){
	int i;
	for (i = 0; i < M_HASH; i++){
		search_teams_wins(l[i], res, max);
	}
}

int check_empty_ht_t(ht_teams l){
	int i;
	for (i = 0; i < M_HASH; i++){
		if (l[i]->head != NULL){
			return 0;
		}
	}
	return 1;
}

Name * index_(List_Names * l, int ind){
	Name * x;
	int i;
	x = l->head;
	for (i = 0; i < ind; i++){
		x = x->next;
	}
	return x;
}

void merge(List_Names * lst, int l, int m, int r){
	int i, j, k;
	char * aux[M_HASH];
	/*construcao de vetor auxiliar*/
	for (i = m + 1; i > l; i--){
		aux[i - 1] = (index_(lst, i - 1))->jogo;
	}
	for (j = m; j < r; j++){
		aux[r + m - j] = (index_(lst, j + 1))->jogo;
	}
	/*ordenar os nomes por ordem alfabetica*/
	for (k = l; k <= r; k++){
		if (less_desc(aux[i], aux[j]) || j < m){
			(index_(lst, k))->jogo = aux[i];
			i++;
		}
		else {
			(index_(lst, k))->jogo = aux[j];
			j--;
		}
	}
}

void mergesort(List_Names * lst, int l, int r){
	int m;
	if (l < r){
		m = (r + l) / 2;
		mergesort(lst, l, m);
		mergesort(lst, m + 1, r);
		merge(lst, l, m, r);
	}
}

int number_elem(List_Names * l){
	int contador = 0;
	Name * n;
	n = l->head;
	while(n) {
		contador++;
		n = n->next;
	}
	return contador;
}
