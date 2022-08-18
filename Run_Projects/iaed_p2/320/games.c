#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "teams.h"

#define N_HASH_TABLE 1500	/* numero de listas da hashtable */

/* devolve um ponteiro para um novo jogo com o nome recebido */
game * new_game(char * g_name, char * name_t1, char * name_t2, int score1, int score2){
	game * p_g = malloc(sizeof(game));
	p_g->g_name = string_alloc(g_name);
	p_g->name_t1 = string_alloc(name_t1);
	p_g->name_t2 = string_alloc(name_t2);
	p_g->score1 = score1;
	p_g->score2 = score2;
	return p_g;
}

/* free jogo apontado pelo ponteiro recebido */
void free_game(game * p_g){
	free(p_g->g_name);
	free(p_g->name_t1);
	free(p_g->name_t2);
	free(p_g);
}

/* devolve um ponteiro para uma lista de jogos duplamente ligada vazia */
dlist_games * mk_dlist_games(){
	dlist_games * dl = malloc(sizeof(dlist_games));
	dl->head = NULL;
	dl->last = NULL;
	return dl;
}

/* free node apontado pelo ponteiro recebido */
void free_node_dlist_games(node_dlist_games * n_dl){
	if(n_dl->other != NULL) free_game(n_dl->p_g);
	free(n_dl);
}

/* free lista de jogos duplamente ligada */
void free_dlist_games(dlist_games * dl){
	node_dlist_games * n_dl = dl->head, * next;
	while(n_dl != NULL){
		next = n_dl->next;
		free_node_dlist_games(n_dl);
		n_dl = next;
	}
	free(dl);
}

/* remove um node de uma lista duplamente ligada de jogos */
void rm_node_dlist_games(dlist_games * dl, node_dlist_games * n_dl){
	if(n_dl->prev == NULL) dl->head = n_dl->next;
	else n_dl->prev->next = n_dl->next;
	if(n_dl->next == NULL) dl->last = n_dl->prev;
	else n_dl->next->prev = n_dl->prev;
	free_node_dlist_games(n_dl);
}

/* adiciona um node ao fim da lista de jogos */
node_dlist_games * addlast_dlist_games(dlist_games * dl, game * p_g){
	node_dlist_games * n_dl = malloc(sizeof(node_dlist_games));
	n_dl->prev = dl->last;
	n_dl->next = NULL;
	n_dl->other = NULL;
	n_dl->p_g = p_g;
	if(dl->last != NULL) dl->last->next = n_dl;
	else dl->head = n_dl;
	dl->last = n_dl;
	return n_dl;
}

/* inicializa a hashtable de jogos */
dlist_games ** init_hasht_games(){
	int i;
	dlist_games ** hasht_g = malloc(sizeof(dlist_games *) * N_HASH_TABLE);
	for(i = 0; i < N_HASH_TABLE; i++) hasht_g[i] = mk_dlist_games();
	return hasht_g;
}

/* inicializa a lista de jogos ordenada */
dlist_games * init_dlist_games(){
	dlist_games * dl_g = mk_dlist_games();
	return dl_g;
}

/* insere um jogo a hashtable de jogos */
void insert_hasht_g(dlist_games ** hasht_g, game * p_g, node_dlist_games * other){
	int h = hashf(p_g->g_name);
	node_dlist_games * n_dl = addlast_dlist_games(hasht_g[h], p_g);
	n_dl->other = other;
}

/* devolve um node com o jogo */
node_dlist_games * search_hasht_g(dlist_games ** hasht_g, char * g_name){
	int h = hashf(g_name);
	node_dlist_games * n_dl = hasht_g[h]->head;
	while(n_dl != NULL){
		if(!strcmp(n_dl->p_g->g_name, g_name)) return n_dl;
		n_dl = n_dl->next;
	}
	return NULL;
}

/* free hashtable e lista ordenada das equipas */
void free_games(dlist_games ** hasht_g, dlist_games * dl_g){
	int i;
	for(i = 0; i < N_HASH_TABLE; i++) free_dlist_games(hasht_g[i]);
	free_dlist_games(dl_g);
	free(hasht_g);
}