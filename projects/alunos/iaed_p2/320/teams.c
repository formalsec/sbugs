#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "teams.h"

#define N_HASH_TABLE 1500	/* numero de listas da hashtable */

/* hashfunction copiada dos slides das aulas teoricas */
int hashf(char * string){
	int h, a = 31415, b = 27183;
	for(h = 0; * string != '\0'; string ++, a = a * b % (N_HASH_TABLE - 1)) h = (a * h + * string) % N_HASH_TABLE;
	return h;
}

/* devolve uma string igual a recebida mas apenas com o tamanho necessario */
char * string_alloc(char * string){
	int len = strlen(string), i;
	char * str_alloc = can_fail_malloc(sizeof(char) * (len + 1));
	for(i = 0; i <= len; i++) str_alloc[i] = string[i];
	return str_alloc;
}

/* devolve um ponteiro para uma nova equipa com o nome recebido */
team * new_team(char * t_name){
	team * p_t = can_fail_malloc(sizeof(team));
	p_t->t_name = string_alloc(t_name);
	p_t->n_wins = 0;
	return p_t;
}

/* free equipa apontada pelo ponteiro recebido */
void free_team(team * p_t){
	free(p_t->t_name);
	free(p_t);
}

/* devolve um ponteiro para uma lista de equipas duplamente ligada vazia */
dlist_teams * mk_dlist_teams(){
	dlist_teams * dl = can_fail_malloc(sizeof(dlist_teams));
	dl->head = NULL;
	dl->last = NULL;
	return dl;
}

/* free node apontado pelo ponteiro recebido */
void free_node_dlist_teams(node_dlist_teams * n_dl){
	free_team(n_dl->p_t);
	free(n_dl);
}

/* free lista de equipas duplamente ligada */
void free_dlist_teams(dlist_teams * dl){
	node_dlist_teams * n_dl = dl->head, * next;
	while(n_dl != NULL){
		next = n_dl->next;
		free_node_dlist_teams(n_dl);
		n_dl = next;
	}
	free(dl);
}

/* remove um node de uma lista duplamente ligada de equipas */
void rm_node_dlist_teams(dlist_teams * dl, node_dlist_teams * n_dl){
	if(n_dl->prev == NULL) dl->head = n_dl->next;
	else n_dl->prev->next = n_dl->next;
	if(n_dl->next == NULL) dl->last = n_dl->prev;
	else n_dl->next->prev = n_dl->prev;
	free_node_dlist_teams(n_dl);
}

/* adiciona um node ao fim da lista de equipas */
node_dlist_teams * addlast_dlist_teams(dlist_teams * dl, team * p_t){
	node_dlist_teams * n_dl = can_fail_malloc(sizeof(node_dlist_teams));
	n_dl->prev = dl->last;
	n_dl->next = NULL;
	n_dl->p_t = p_t;
	if(dl->last != NULL) dl->last->next = n_dl;
	else dl->head = n_dl;
	dl->last = n_dl;
	return n_dl;
}

/* inicializa a hashtable de equipas */
dlist_teams ** init_hasht_teams(){
	int i;
	dlist_teams ** hasht_t = can_fail_malloc(sizeof(dlist_teams *) * N_HASH_TABLE);
	for(i = 0; i < N_HASH_TABLE; i++) hasht_t[i] = mk_dlist_teams();
	return hasht_t;
}

/* insere uma equipa a hashtable de equipas */
void insert_hasht_t(dlist_teams ** hasht_t, team * p_t){
	int h = hashf(p_t->t_name);
	addlast_dlist_teams(hasht_t[h], p_t);
}

/* devolve um node com a equipa */
node_dlist_teams * search_hasht_t(dlist_teams ** hasht_t, char * t_name){
	int h = hashf(t_name);
	node_dlist_teams * n_dl = hasht_t[h]->head;
	while(n_dl != NULL){
		if(!strcmp(n_dl->p_t->t_name, t_name)) return n_dl;
		n_dl = n_dl->next;
	}
	return NULL;
}

/* free hashtable das equipas */
void free_teams(dlist_teams ** hasht_t){
	int i;
	for(i = 0; i < N_HASH_TABLE; i++) free_dlist_teams(hasht_t[i]);
	free(hasht_t);
}