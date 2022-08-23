#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"


/*Cria um jogo para adicionar na ultima posicao da lista ligada */ 


Node *New(Jogo *j){
	Node *x = malloc(sizeof(Node));
	x->jogo=j;
	x->next = NULL;
	return x;
}


/*Adiciona um jogo na ultima posicao da lista ligada */


Node *add_last(Node*head,Jogo *j){
	Node *x;
	if (head==NULL) return New(j);

	for(x=head;x->next!=NULL; x=x->next);

	x->next = New(j);
	return head;

}


/*Nao elimina o jogo mas sim altera o ponteiro do jogo anterior para apontar para o a seguir ao jogo a excluir . A sua eliminacao ocorre sim nas funcoes da hash table dos jogos no comando apaga jogo*/


Node *Modifica_next_jogo(Node *head,char name[]){
	Node *t,*prev;
	for(t=head,prev=NULL; t != NULL; prev = t,t=t->next){
		if (strcmp(t->jogo->nome_jogo,name)==0){
			if (t==head) head = t->next;
			else prev->next = t->next;
			free(t);
			break;
		}
	}
	return head;

}


/*Liberta toda a minha lista de jogos percorrendo a desde a cabeca ate ao ultimo elemento */ 


void free_list_jogos(Node*head){
	Node *aux;
	while(head!=NULL){
		aux=head->next;
		free(head);
		head = aux;
	}
}


/*Esta funcao printa todos os jogos do nosso sitema por ordem de insercao no formato pedido pelo comando 'l' */

void print_lista(Node *head,int contador){
	Node *aux;
	aux = head;
	while(aux!=NULL){
		printf("%d %s %s %s %d %d\n",contador,aux->jogo->nome_jogo,aux->jogo->equipa_1,aux->jogo->equipa_2,aux->jogo->score_1,aux->jogo->score_2);
		aux = aux->next;
	}
}





