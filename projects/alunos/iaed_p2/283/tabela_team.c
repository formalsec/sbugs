#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela_team.h"
#include "hash.h"



/*Esta funcao recebe a cabeca da lista e liberta a lista  */


void liberta_link_t(link_t head){
	link_t aux;
	while(head != NULL){
		aux = head;
		head = head->next;
		free_team(aux->team);
		free(aux);
	}
	free(head);
}


/*Inicializa a minha hash table de equipas com a funcao can_fail_calloc pondo as a 0 */


link_t *init_t() {
	link_t *table;
	table = can_fail_calloc(HASH_SIZE,sizeof(link_t));
	return table;
}


/*Encontra dentro da minha hash table de equipas uma equipa pelo seu nome */


Team *encontra_t(link_t *table, char team[]){
	int hash_id;
	link_t aux;
	hash_id = hash(team);
	aux = table[hash_id];
	while(aux != NULL){
		if (strcmp(team,aux->team->name_team)==0) return aux->team;
		aux = aux->next;
	}
	return NULL;

}


/*Introduz na minha hash table na sua lista respetiva do seu hash number uma determinada equipa */


void introduz_table_t(link_t *table,Team *new_team){
	int hash_id;
	link_t novo_link;
	novo_link = can_fail_malloc(sizeof(struct link_t));
	hash_id = hash(new_team->name_team);
	novo_link -> team = new_team;
	novo_link->next = table[hash_id];
	table[hash_id]= novo_link;
}


/*Faz free de todas as listas ligadas e da hash table em si */


void liberta_table_t(link_t *table){
	int i;
	link_t *aux;
	aux = table;
	for(i=0;i<HASH_SIZE;i++) liberta_link_t(aux[i]);
	free(aux);
}


/*Remove da tabela uma determinada equipa */


void Remove_table_t(link_t *table,Team *t){
	int hash_id;
	link_t tmp,tmp2;
	hash_id = hash(t->name_team);
	tmp = table[hash_id];
	if (table[hash_id]==NULL) return;
	else if(table[hash_id]->next == NULL && strcmp(t->name_team,tmp->team->name_team)!=0);
	else if(table[hash_id]->next == NULL && strcmp(t->name_team,tmp->team->name_team)==0){
		table[hash_id] = table[hash_id]->next;
		free_team(tmp->team);
		free(tmp);
		return;
	}
	else {
		if (strcmp(tmp->team->name_team,t->name_team)==0){
			tmp2=tmp;
			table[hash_id]=table[hash_id]->next;
			free_team(tmp2->team);
			free(tmp2);
			return;
		}
		while (tmp->next != NULL){
			if (strcmp(t->name_team,tmp->next->team->name_team) == 0){
				tmp2 = tmp->next;
				tmp->next=tmp2->next;
				free_team(tmp2->team);
				free(tmp2);
				return;
			}
			tmp = tmp->next;
		}
		return;
	}
} 


/*Indentifica o maior numero de wins de uma equipa percorrendo toda a hash table */


int ve_maior(link_t *table){
	int i,maior=0;
	link_t tmp;
	for(i=0;i<HASH_SIZE;i++){
		if (table[i]==NULL) continue; 
		else{
			tmp=table[i];
			while(tmp!=NULL){
				if(tmp->team->numero_wins > maior) maior=tmp->team->numero_wins;	
			tmp=tmp->next;
			}
		}
	}
	return maior;
}


/* Identifica todas as equipas com o maior numero de wins passando o seu nome para um vetor e retorna quantas equipas tem esse numero*/


int teams_maiores(link_t *table,char **vec,int maior){
	int i,cont_teams=0;
	link_t tmp;
	for(i=0;i<HASH_SIZE;i++){
		if(table[i]!=NULL){
			tmp=table[i];
			while(tmp!=NULL){
				if(tmp->team->numero_wins == maior) {
					strcpy(vec[cont_teams],tmp->team->name_team);
					cont_teams++;
				}
			tmp=tmp->next;
			}
		}
	}
	return cont_teams;
}


/*Ordena lexicograficamente as equipas com o algoritmo merge sort */


void merge(char **aux,char**aux1,int l,int m,int r){
	int i, j, k;
	for (i= m+1; i>l ; i--) aux1[i-1] = aux[i-1];		
	for (j = m; j < r; j++) aux1[r+m-j] = aux[j+1];		
	for (k=l; k<= r; k++){
		if (strcmp(aux1[j],aux1[i])<0) aux[k] = aux1[j--];				
		else aux[k] = aux1[i++];
	}

}


/*Estrutura principal do algortimo merge sort */


void merge_principal(char **aux,char**aux_1,int l, int r){
	int m = (r+l)/2;		
	if (r <= l) return;		
	merge_principal(aux,aux_1,l,m);		
	merge_principal(aux,aux_1,m+1,r);		
	merge(aux,aux_1,l, m, r);		
}




