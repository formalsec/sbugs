#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela_jogo.h"
#include "hash.h"


/*Esta funcao recebe a cabeca da lista e liberta a lista  */


void liberta_link(link head){
	link aux;
	while(head != NULL){
		aux = head;
		head = head->next;
		free_jogo(aux->jogo);
		free(aux);
	}
	free(head);
}


/*Inicializa a minha hash table de jogos com a funcao can_fail_calloc pondo as a 0 */


link *init() {
	link *table;
	table = can_fail_calloc(HASH_SIZE,sizeof(link));
	return table;
}


/*Encontra dentro da minha hash table de jogos um jogo pelo seu nome */


Jogo *encontra(link *table, char jogo[]){
	int hash_id;
	link aux;
	hash_id = hash(jogo);
	aux = table[hash_id];
	while(aux != NULL){
		if (strcmp(jogo,aux->jogo->nome_jogo)==0) return aux->jogo;
		aux = aux->next;
	}
	return NULL;

}


/*Introduz na minha hash table na sua lista respetiva do seu hash number um determinado jogo */



void introduz_table(link *table,Jogo *novo_jogo){
	int hash_id;
	link novo_link=can_fail_malloc(sizeof(struct link));
	novo_link->jogo=novo_jogo;
	hash_id = hash(novo_jogo->nome_jogo);
	novo_link->next = table[hash_id];
	table[hash_id]= novo_link;
}


/*Faz free de todas as listas ligadas e da hash table em si */



void liberta_table(link *table){
	int i;
	link *aux;
	aux = table;
	for(i=0;i<HASH_SIZE;i++) liberta_link(aux[i]);
	free(aux);
}


/*Remove da tabela um determinado jogo */



void Remove_table(link*table,Jogo *j){
	int hash_id;
	
	link tmp,tmp2;
	hash_id=hash(j->nome_jogo);
	tmp=table[hash_id];
	if (table[hash_id]==NULL) return;
	
	else if(table[hash_id]->next == NULL && strcmp(j->nome_jogo,tmp->jogo->nome_jogo)!=0) return;
	else if(table[hash_id]->next == NULL && strcmp(j->nome_jogo,tmp->jogo->nome_jogo)==0){
		table[hash_id] = table[hash_id]->next;
		free_jogo(tmp->jogo);
		free(tmp);
		return;
	}
	else {
		if (strcmp(tmp->jogo->nome_jogo,j->nome_jogo)==0){
			tmp2=tmp;
			table[hash_id]=table[hash_id]->next;
			free_jogo(tmp2->jogo);
			free(tmp2);
			return;
		}
		while (tmp->next != NULL){
			if (strcmp(j->nome_jogo,tmp->next->jogo->nome_jogo) == 0){
				tmp2 = tmp->next;
				tmp->next=tmp2->next;
				free_jogo(tmp2->jogo);
				free(tmp2);
				return;
			}
			tmp = tmp->next;
		}
		return;
	}
}








