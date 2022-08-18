#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"

/***********************/
/*Operacos lista ligada*/
/***********************/

node_equipa criar_node_equipa(char *nome){
	/*Esta funcao recebe um ponteiro para uma string
    e devolve um node contendo esse ponteiro.*/
	node_equipa novo = malloc(sizeof(struct stru_node_equipa));
	novo->next = NULL;
	novo->vitorias = 0;
	novo->nome_equipa = malloc((strlen(nome)+1)*sizeof(char));
	strcpy(novo->nome_equipa,nome);
	return novo;
}

node_equipa insert_equipa(node_equipa head, char *equipa){
	/*Esta funcao recebe uma cabeca e o nome de uma equipa,
    e devolve a nova cabeca que contem essa equipa.*/
	node_equipa novo = criar_node_equipa(equipa);
	novo->next = head;
	return novo;
}


node_equipa adicionar_ordem_alfabetica(node_equipa head,char* equipa){
	/*Esta funcao adiciona uma equipa a uma lista ligada
	por ordem lexicografica*/
	if(head == NULL){
		node_equipa new = criar_node_equipa(equipa);
		return new;
	}
	else if (strcmp(head->nome_equipa,equipa)>0){
		node_equipa new = criar_node_equipa(equipa);
		new->next = head;
		return new;
	}else{
		node_equipa aux;
		for(aux = head;aux->next!=NULL;aux = aux->next){
			if(strcmp(aux->next->nome_equipa,equipa)>0){
				node_equipa team,aux2;
				team = criar_node_equipa(equipa);
				aux2 = aux->next;
				aux->next = team;
				team->next = aux2;
				break;
			}
		}
		if(aux->next == NULL){
			node_equipa team = criar_node_equipa(equipa);
			aux->next = team;
		}
		return head;
	}
}


/**********************/
/*Operacoes hash table*/
/**********************/

void init_hash_table_equipas(hash_table_team hash_table, int lim){
	/*Esta funcao inicializa uma hash table de equipas.*/
    int i;
    hash_table->cap = lim;
    hash_table->table = malloc(lim*sizeof(no)); 
    for (i = 0; i < lim; i++) hash_table->table[i] = NULL;
}

no equipa_insert(no head){
	/*Esta funcao recebe uma cabeca e devolve uma nova cabeca.*/
	no novo = malloc(sizeof(struct  stru_no_equipa));
	novo->next = head;
	return novo;
}


void hash_insert_equipas(hash_table_team hash_table,char *equipa,lista *equipas){
	/*Esta funca recebe uma hash table equipas, um nome de uma equipa e 
	uma lista de equipas e insere a nova equipa na hash table.*/
	int h,h1;
	h = hash(equipa,hash_table->cap);
	h1 = hash1(equipa,hash_table->cap);
	while (hash_table->table[h] != NULL) h = (h+h1) % hash_table->cap;
	hash_table->table[h] = equipa_insert(hash_table->table[h]);
	hash_table->table[h]->no_e = equipas->head;
}

no hash_search_equipas(hash_table_team hash_table,char*equipa){
	/*Esta funcao porcura uma equipa na hash table e devolve-a.
    No caso da equipa nao existir devolve NULL.*/
	int h,h1;
	h = hash(equipa,hash_table->cap);
	h1 = hash1(equipa,hash_table->cap);
	
	while (hash_table->table[h] != NULL)
		if (strcmp(hash_table->table[h]->no_e->nome_equipa,equipa)==0)
			return hash_table->table[h];
		else
			h = (h+h1) % hash_table->cap;
	return NULL;
}

/*********************/
/*libertar estruturas*/
/*********************/

void libertar_lista_teams(node_equipa head){ 
	/*Esta funcao liberta a lista ligada que contem todas as equipas
	adicionadas ao sistema.*/
	node_equipa aux;
	while(head != NULL){
		aux = head;
		head = head->next;
		free(aux->nome_equipa);
		free(aux);
	}
}

void libertar_elemento_hash(no head){ 
	/*Esta funcao liberta um elemento da hash table das equipas.*/
	free(head->no_e->nome_equipa);
	free(head->no_e);
	free(head);
}

void libertar_hash_equipas(hash_table_team hash_table){
	/*Esta funcao liberta a hash table das equipas.*/
	int i;
	for(i = 0;i<hash_table->cap;i++)
		if(hash_table->table[i] != NULL)
			libertar_elemento_hash(hash_table->table[i]);
	free(hash_table->table);
	free(hash_table);
}


