#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "funcoes.h"



/* Cria um novo no*/
NODE new_node(JOGO j) {
	NODE new;
	new = malloc(sizeof(struct node_jogo));
	new->jogo = malloc(sizeof(struct jogo));
	new->jogo->nome = strdup(j->nome);
	new->jogo->equipa1 = strdup(j->equipa1);
	new->jogo->equipa2 = strdup(j->equipa2);
	new->jogo->score1 = j->score1;
	new->jogo->score2 = j->score2;
	new->next = NULL;
	return new;
}


/* Adiciona novo no a lista ligada */
NODE insert_node(NODE head, JOGO j) {
	NODE x;
	if (head == NULL)
		return new_node(j);
	for (x = head; x->next != NULL; x = x->next);
	x->next = new_node(j);
	return head;
}


/* procura um no na lista ligada */
NODE procura_node(NODE head, JOGO j) {
	NODE t;
	for (t = head; t != NULL; t = t->next)
		if (strcmp(t->jogo->nome, j->nome) == 0)
			return t;
	return NULL;
}

/* apaga um no da lista ligada */
NODE delete_node(NODE head, char* nome) {
	NODE t, prev;
	for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if(strcmp(t->jogo->nome, nome) == 0) {
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			FREEnode(t);
			break;
		}
	}
	return head;
}

/* Liberta a memoria de um no */
void FREEnode(NODE t) {
	free(t->jogo->nome);
	free(t->jogo->equipa1);
	free(t->jogo->equipa2);
	free(t);
} 

/* Liberta a memoria de uma lista ligada */
void freeList(NODE head) {
   NODE tmp;

   while (head != NULL)
    {
        tmp = head;
        head = head->next;
		free(tmp->jogo->nome);
		free(tmp->jogo->equipa1);
		free(tmp->jogo->equipa2);
		free(tmp->jogo);
        free(tmp);
    }

}