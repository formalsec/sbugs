#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"

/**************************/
/*Operacoes listas ligadas*/
/**************************/

jogo cria_jogo(char *nome1,char*nome_equipa1,char*nome_equipa2,int score_jogo[2]){
	/*Esta funcao recebe um nome do jogo, o nome de duas equipas e o score
	e devolve um jogo.*/
	jogo new;
	new.nome = can_fail_malloc(sizeof(char)*(strlen(nome1)+1));
	strcpy(new.nome,nome1);
	new.equipa1 = can_fail_malloc(sizeof(char)*(strlen(nome_equipa1)+1));
	strcpy(new.equipa1,nome_equipa1);
	new.equipa2 = can_fail_malloc(sizeof(char)*(strlen(nome_equipa2)+1));
	strcpy(new.equipa2,nome_equipa2);
	new.score0 = score_jogo[0];
	new.score1 = score_jogo[1];
	return new;
}

no_jogo cria_no_jogo(jogo novo_jogo){
	/*Esta funcao recebe um jogo e cria um no para a lista ligada dos jogos.*/
	no_jogo novo = can_fail_malloc(sizeof(struct stru_no_jogo));
	novo->next = NULL;
	novo->prev = NULL;
	novo->game = novo_jogo;
	return novo;
}

node_jogo cria_node_jogo(){
	/*Esta funcao cria um no para uma lista ligada na hash table dos jogos.*/
	node_jogo novo = can_fail_malloc(sizeof(struct node_jogos));
	novo->next = NULL;
	novo->prev = NULL;
	return novo;
}

void insert_end_list_jogos(lista_jogos *jogos,jogo novo_jogo){
	/*Esta funcao insere um jogo no final da lista ligada dos jogos.*/
	no_jogo node;
	if(jogos->head == NULL){
		node = cria_no_jogo(novo_jogo);
		node->prev = NULL;
		jogos->head = node;
		jogos->last = node;
	}else{
		node = cria_no_jogo(novo_jogo);
		jogos->last->next = node;
		node->prev = jogos->last;
		jogos->last = node;
	}
}

node_jogo insert_inicio_jogos(node_jogo head){
	/*Esta funcao recebe uma cabeca da hash table dos jogos, e devolve a nova cabeca.*/
	node_jogo novo = cria_node_jogo();
	if(head != NULL)
		head->prev = novo;
	novo->next = head;
	return novo;
}



void remove_jogo(no_jogo no){
	/*Esta funcao recebe um no da lista ligada de jogos e remove-o.
	Se o no for o primeiro elemento, o nome do jogo do no fica a NULL.*/
	libertar_jogo(no->game);
	if(no->prev == NULL){
		no->game.nome = NULL;
	}else if(no->next == NULL){
		no->prev->next = NULL;
		free(no);
	}else{
		no->prev->next = no->next;
		no->next->prev = no->prev;
		free(no);
	}
}


node_jogo search_list_jogos(node_jogo head, char *nome_jogo){
	/*Esta funcao,dado um nome, procura um jogo numa lista ligada e devolve-o.
	No caso de este nao existir devolve NULL.*/
	node_jogo aux;
	for(aux = head;aux != NULL;aux = aux->next)
		if(strcmp(aux->no_j->game.nome,nome_jogo) == 0)
			return aux;
	return NULL;
}

/**********************/
/*Operacoes hash table*/
/**********************/

hash_table_jogos init_hash_table_jogos(int lim){
	/*Esta funcao inicializa a hash table dos jogos.*/
    int i;
    hash_table_jogos hash_table = can_fail_malloc(sizeof(struct stru_hash_jogos));
    hash_table->cap =lim;
    hash_table->table = can_fail_malloc(lim*sizeof(node_jogo));
    for (i = 0; i < lim; i++) hash_table->table[i] = NULL;
   	return hash_table;
}


void hash_insert_jogos(hash_table_jogos hash_table,char* nome){
	/*Esta funcao insere um jogo na hash table.*/
	int h;
	h = hash(nome,hash_table->cap);
	if(hash_table->table[h] == NULL)
		hash_table->table[h] = cria_node_jogo();
	else
		hash_table->table[h] = insert_inicio_jogos(hash_table->table[h]);
	
}

node_jogo hash_search_jogos(hash_table_jogos hash_table, char *nome){
	/*Esta funcao,dado um nome, procura um jogo na hash table e devolve-o.
	No caso de este nao existir devolve NULL.*/
	int h;
	h = hash(nome,hash_table->cap);
	return search_list_jogos(hash_table->table[h],nome);
}

void remove_jogos(hash_table_jogos table_jogo, node_jogo node){
	/*Esta funcao remove um jogo do sistema.*/
	int h;
	h = hash(node->no_j->game.nome,table_jogo->cap);
	remove_jogo(node->no_j);
	if(node->prev == NULL){
		if(node->next == NULL)
			table_jogo->table[h] = NULL;
		else{
			table_jogo->table[h] = node->next;
			table_jogo->table[h]->prev = NULL;
		}
	}else if(node->next == NULL){
		node->prev->next = NULL;
	}else{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node);
}

/*********************/
/*libertar estruturas*/
/*********************/

void libertar_jogo(jogo game){
	/*Esta funcao liberta um jogo.*/
	free(game.nome);
	free(game.equipa1);
	free(game.equipa2);
}

void libertar_lista_hash(node_jogo head){
	/*Esta funcao liberta uma lista ligada pertencente a hash table dos jogos,
	ao mesmo tempo que elimina os jogos que estas apontam para a lista ligada de todos
	os jogos do sistema.*/
	node_jogo aux;
	while(head != NULL){
		aux = head;
		head = head->next;
		remove_jogo(aux->no_j);
		free(aux);
	}
}
void libertar_hash_jogos(hash_table_jogos hash_table){
	/*Esta funcao liberta a hash table e a lista ligada dos jogos do sistema.*/
	int i;
	for(i = 0;i<hash_table->cap;i++)
		if(hash_table->table[i] != NULL)
			libertar_lista_hash(hash_table->table[i]);
	free(hash_table->table);
	free(hash_table);
}
