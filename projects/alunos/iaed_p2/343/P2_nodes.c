#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "nodes.h"

/* Pilhas de equipas */
/* Guarda uma nova equipa na pilha */
node_eq push_eq(node_eq head, eq *equipa){
	node_eq new;
	new = can_fail_malloc(sizeof(struct node_eq));
	new->equipa = equipa;
	new->next = head;
	head = new;
	return head;
}

/* Verifica se uma lista de nos de equipas esta vazia */
int l_eq_empty(node_eq head){
	return head == NULL;
}

/* Verifica se a equipa existe e se sim, devolve-a */
eq *search_eq(node_eq head, char *nome){
	node_eq t;
	for (t = head; t != NULL; t = t->next){
		if (strcmp(t->equipa->des, nome) == 0)
			return t->equipa;
	}
	return NULL;
}

/* Pilhas de jogos */
/* Guarda um novo jogo na pilha */
node_jg push_jg(node_jg head, jg *jogo){
	node_jg new;
	new = can_fail_malloc(sizeof(struct node_jg));
	new->jogo = jogo;
	new->next = head;
	head = new;
	return head;
}

/* Verifica se uma lista de nos de equipas esta vazia */
int l_jg_empty(node_jg head){
	return head == NULL;
}

/* Verifica se o jogo existe e se sim, devolve-o */
jg *search_jg(node_jg head, char *nomep){
	node_jg t;
	for (t = head; t != NULL; t = t->next){
		if (strcmp(t->jogo->nome, nomep) == 0)
			return t->jogo;
	}
	return NULL;
}

/* Funcao que remove o jogo da hash table */
node_jg remove_jg(node_jg head, jg *jogo){
	node_jg atual = head, temp;
	if (atual->jogo == jogo){
			head = head->next;
			free(atual);
			return head;
		}
	for (atual = head; atual != NULL; atual = atual->next){
		if (atual->next->jogo == jogo){
			temp = atual->next->next;
			free(atual->next);
			atual->next = temp;
			return head;
		}
	}
	return head;
}

/* Funcoes que tratam da lista para o comando l */
/* Adiciona o novo jogo ao final da lista */
void push_before(link *lista, jg *jogo){
	node_jg new = can_fail_malloc(sizeof(struct node_jg));
	new->jogo = jogo;
	new->next = NULL;
	lista->tail->next = new;
}

/* Verifica se e necessario dar update a cabeca da lista (caso esteja vazia), ou a cauda (caso tenha 1 ou mais elementos)*/
void push_lista(link *lista, jg *njogo){
	node_jg new;
	if (l_jg_empty(lista->head)){
		new = can_fail_malloc(sizeof(struct node_jg));
		new->jogo = njogo;
		new->next = NULL;
		lista->head = new;
		lista->tail = new;
		return;
	}
	push_before(lista, njogo);
	lista->tail = lista->tail->next;
}

/* Funcao que remove o jogo da lista para o comando l */
void remove_lista(link *lista, jg *jogo){
	node_jg atual = lista->head;
	node_jg temp;
	if (atual->jogo == jogo){
		lista->head = lista->head->next;
		free(atual);
		return;
	}
	for (atual = lista->head; atual->next != NULL; atual = atual->next){
		if (atual->next->jogo == jogo && atual->next == lista->tail){
			lista->tail = atual;
			free(atual->next);
			lista->tail->next = NULL;
			return;
		}
		else if (atual->next->jogo == jogo){
			temp = atual->next->next;
			free(atual->next);
			atual->next = temp;
			return;
		}
	}
}