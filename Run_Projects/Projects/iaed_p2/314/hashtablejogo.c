#include "hashtablejogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*funcao hash que da em que slot vamos trabalhar*/
int hashj(char* v, int m){
	int h = 0, a = 127;
	for (; *v != '\0'; v++)
		h = (a * h + *v) % m;
	return h;
}

/*inicializo o hashtable*/
linkj* STiniciaj(int M) {
	int i;
	linkj* heads = malloc(M * sizeof(linkj));
	for (i = 0; i < M; i++) { /*coloco todas as posicoes da hashtable a NULL*/
		heads[i] = NULL;
	}
	return heads;
}

/*coloco um jogo no inicio de uma lista (funcao auxiliar)*/
linkj insereinicioListj(linkj head, jogo* jg) {
	linkj j = malloc(sizeof(struct nodej)); /*crio umnovo linkj*/
	j->jogo = jg;
	if (head == NULL){ /*se a lista ainda estiver vazia*/
	    j->next = NULL;
	    head = j;
	}
	else{ /*se ja existirem elementos na lista*/
    	j->next = head;
    	head = j;
	}
	return head;
}

/*coloco um jogo no inicio de uma lista*/
void STinserej(jogo* jg, int M, linkj* heads) {
	int i = hashj(jg->nome , M);
	heads[i] = insereinicioListj(heads[i], jg);
}

/*remove um jogo da lista (funcao auxiliar)*/
linkj removeItemListj(linkj head, jogo* jg) {
	linkj tmp = head;
	if (tmp == NULL) { /*se nao houver lista*/
		return head;
	}
	if (tmp != NULL && strcmp(tmp->jogo->nome, jg->nome) == 0) { /*se for o primeiro elemento*/
		free(tmp->jogo->nome);
		free(tmp->jogo);
		free(tmp);
		head = head->next;
		return head;
	}
	for (tmp = head; strcmp(tmp->next->jogo->nome, jg->nome) != 0; tmp = tmp->next); /*anda pelos jogos que nao me interessam*/
	free(tmp->next->jogo->nome); /*liberta a memoria quando encontra o jogo*/
	free(tmp->next->jogo);
	free(tmp->next);
	tmp->next = tmp->next->next; /*atualiza os ponteiros*/
	
	return head;
}

/*remove um jogo da lista*/
void STapagaj(jogo* jg, int M, linkj* heads) {
	int i = hashj(jg->nome, M);
	heads[i] = removeItemListj(heads[i], jg);
}

/*procura um jogo na lista (funcao auxiliar)*/
jogo* procuraListj(linkj head, char* nome) {
	linkj tmp = head;
	if (tmp == NULL) { /*se a lista estiver vazia*/
		return NULL;
	}
	while (tmp != NULL && strcmp(tmp->jogo->nome, nome) != 0) { /*anda na lista enquanto nao encontra o jogo que quero*/
		tmp = tmp->next;
	}
	if (tmp != NULL && strcmp(tmp->jogo->nome, nome) == 0) { /*quando encontra o jogo que queremos retorno esse jogo*/
		return tmp->jogo;
	}
	return NULL; /*se nao o encontrar*/
}

/*procura um jogo na lista*/
jogo* STprocuraj(char* nome, int M, linkj* heads) {
	int i = hashj(nome, M);
	return procuraListj(heads[i], nome);
}

/*liberto toda a memoria de um linkj*/
void STfree_listhtj(linkj head) {
	linkj tmp;
	while (head) {
		tmp = head->next;
		free(head->jogo->nome);
		free(head->jogo);
		free(head);
		head = tmp;
	}
}

/*liberta toda a memoria usada na hashtable*/
void STfree_htj(int M, linkj* heads) {
	int i;
	for (i = 0; i < M; i++) { /*liberto cada uma das listas da hashtable*/
		STfree_listhtj(heads[i]);
	}
	free(heads);
}