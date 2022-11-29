#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashTeam.h"

/* Add team to teams' hash table's head. */
LinkTeam push_team(LinkTeam head, ItemTeam item){
	LinkTeam aux = new_node_team(item, head);
	return aux;
}

/* Returns pointer to the team with the given name from a teams' hash table's
   head. */
ItemTeam search_list_team(LinkTeam head, char* name){
	LinkTeam t;
	for(t = head; t != NULL; t = t->next){
		if(strcmp(t->item->name, name) == 0){
			return t->item;
		}
	}
	return NULL;
}

/* Deletes a given name from a teams' hash table's head. */
void destroy_list_team(LinkTeam head){
	LinkTeam t, aux;
	if(head == NULL){
		return;
	}
	for(t = head, aux = head->next; t != NULL;
		aux = t->next, delete_node_team(t), t = aux){}
	}

/* Initializes teams' hash table. */
LinkTeam* HASHinit_team(){
	int i;
	LinkTeam* heads = can_fail_malloc(MH * sizeof(LinkTeam));
	for(i = 0; i < MH; i++){
		heads[i] = NULL;
	}
	return heads;
}

/* Games' hash table's hash function. */
int hash_team(char* v){
	int h = 0;
	for(; *v != '\0'; v++){
		h = (CH*h + *v) % MH;
	}
	return h;
}

/* Creates team in teams' hash table's head. */
LinkTeam new_node_team(ItemTeam item, LinkTeam head){
	LinkTeam x = can_fail_malloc(sizeof(NodeTeam));

	x->item = item;
	x->next = head;
	return x;
}

/* Deletes team from a teams' hash table's head. */
void delete_node_team(LinkTeam nodeTeam){
	deleteItem_team(nodeTeam->item);
	free(nodeTeam);
}

/* Inserts a given team in the teams' hash table. */
void insert_team(LinkTeam* heads, ItemTeam item){
	int i = hash_team(item->name);
	heads[i] = push_team(heads[i], item);
}

/* Returns pointer to the team with the given name from teams' hash table. */
ItemTeam search_team(LinkTeam* heads, char* name){
	int i = hash_team(name);
	return search_list_team(heads[i], name);
}

/* Deletes teams' hash table. */
void destroy_hash_team(LinkTeam* heads){
	int i;
	for(i = 0; i < MH; i++) {
		destroy_list_team(heads[i]);
	}
	free(heads);
}
