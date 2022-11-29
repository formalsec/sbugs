#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipas.h"

List_Teams * init_list_t(){
	List_Teams * l;
	l = can_fail_malloc(sizeof(List_Teams));
	l->head = NULL;
	l->last = NULL;
	return l;
}

Team * new_team(char * eq){
	Team * new;
	new = can_fail_malloc(sizeof(Team));
	new->nome_eq = can_fail_malloc(sizeof(char)*(strlen(eq) + 1));
	strcpy(new->nome_eq, eq);
	new->vitorias = 0;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

Team * add_end_team(List_Teams * l, char * eq){
	Team * new;
	new = new_team(eq);
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


Team * search_team(List_Teams * l, char * nome){
	Team * t = l->head;
	while(t != NULL){
		if (!strcmp(t->nome_eq, nome)){
			return t;
		}
		t = t->next;
	}
	return NULL;
}


void change_wins(List_Teams * l, char * eq, int v){
	Team * n;
	n = search_team(l, eq);
	n->vitorias = n->vitorias + v;
}

void free_team(Team * n){
	free(n->nome_eq);
	free(n);
}

void remove_team(List_Teams * l, char * eq){
	Team * t;
	t = search_team(l, eq);
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
	free_team(t);
}

Team * remove_first_team(Team * head){
	Team * aux;
	aux = head->next;
	free_team(head);
	return aux;
}

void free_all_teams(List_Teams * l){
	while(l->head != NULL){
		l->head = remove_first_team(l->head);
	}
	free(l);
}

void print_team(Team * n){
	printf("%s %i\n", n->nome_eq, n->vitorias);
}
