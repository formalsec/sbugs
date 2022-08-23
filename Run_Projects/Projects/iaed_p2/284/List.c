#include "List.h"
#include "constants.h"

#include <stdlib.h>
#include <string.h>

/* hash function para lista de caracteres */
long int hash(const char* s) {
	long int h, a = 124991, b = 24989;

	for (h = 0; *s; s++, a = a * b % (HASH_SIZE - 1))
		h = (a * h + *s) % HASH_SIZE;
	return h;
}

/* declaracao das funcoes da hash table */
void STinsert(link** heads, node* n);
void STdelete(link** heads, node* n);
void STfree(link** heads);


/*--------------------*\
 * Funcoes auxiliares *
\*--------------------*/

void free_game(game* g) {
	free(g->name);
	free(g);
}

void free_team(team* t) {
	free(t->name);
	free(t);
}


/*-----------------------*\
 * Funcoes sobre a lista *
\*-----------------------*/

/* todas as funcoes sobre uma lista modificam tambem a hash table
	correspondente a essa mesma lista */

/* cria uma lista nova e a sua hash table correspondente */
list* create_list() {
	list* lst = malloc(sizeof(list));

	lst->head = NULL; lst->last = NULL;
	lst->table = calloc(HASH_SIZE, sizeof(link*));

	return lst;
}

/* adiciona um novo elemento a lista */
void append(list* lst, node* n) {
	n->next = NULL;					/* n vai ser o ultimo elemento da lista */
	if (lst->head) {
		/* se a lista ja tiver elementos, adiciona n ao final */
		lst->last->next = n;
		n->prev = lst->last;
	}
	else {
		/*se a lista estiver vazia, adiciona 1o elemento (n) */
		lst->head = n;
		n->prev = NULL;
	}
	lst->last = n;

	/* adiciona o elemento a hash table correspondente a lista */
	STinsert(lst->table, n);
}

/* remove um elemento da lista */
void delete(list* lst, node* n) {

	/* verifica: */
	if (n->prev)
		/* se n nao e o 1o elemento */
		n->prev->next = n->next;
	else
		lst->head = n->next;
	if (n->next)
		/* se n nao e o ultimo elemento */
		n->next->prev = n->prev;
	else
		lst->last = n->prev;

	/* remove o elemento da hash table correspondente a lista */
	STdelete(lst->table, n);

	/* liberta a memoria do no */
	if (n->type == TEAM)
		free_team(n->d.t);
	else
		free_game(n->d.g);
	free(n);
}

/* liberta a memoria da lista */
void free_list(list* lst) {
	node* aux;
	node* head = lst->head;

	/* liberta a memoria da hash table */
	STfree(lst->table);
	if (head) {
		/* se a lista nao for vazia, vai libertando os elementos ate chegar ao ultimo */
		if (head->type == TEAM)
			while (head) {
				aux = head;
				head = head->next;
				free_team(aux->d.t);
				free(aux);
			}
		else
			while (head) {
				aux = head;
				head = head->next;
				free_game(aux->d.g);
				free(aux);
			}
	}
	free(lst);
}

/*----------------------------*\
 * Funcoes sobre a hash table *
\*----------------------------*/

/* procura uma lista de caracteres numa hash table.
	Devolve um ponteiro para o no correspondente */
node* STsearch(link** heads, char* text) {
	long int i = hash(text);
	link* head = heads[i];

	if (!head) return NULL;		/* a posicao i da tabela nao tem nenhum elemento */

	/* na posicao i da tabela, verifica todos os elementos
		ate encontrar o correspondente */
	if (head->n->type == TEAM) {
		while (head)
			if (!strcmp(head->n->d.t->name, text))
				return head->n;
			else
				head = head->next;
	}
	else {
		while (head)
			if (!strcmp(head->n->d.g->name, text))
				return head->n;
			else
				head = head->next;
	}

	/* percorreu todos os elementos e nao encontrou o correspondente */
	return NULL;
}

/* insere um novo elemento na hash table */
void STinsert(link** heads, node* n) {
	long int i;
	link* new_node = malloc(sizeof(link));

	if (n->type == TEAM)
		i = hash(n->d.t->name);
	else
		i = hash(n->d.g->name);

	/* cria um novo no e adiciona-o no inicio */
	new_node->n = n;
	new_node->next = heads[i];
	heads[i] = new_node;
}

/* remove um elemento da hash table */
void STdelete(link** heads, node* n) {
	long int i;
	link* head;
	link* aux;

	if (n->type == TEAM)
		i = hash(n->d.t->name);
	else
		i = hash(n->d.g->name);
	head = heads[i];

	if (head->n == n) {
		/* o 1o elemento e o que queremos */
		aux = head;
		heads[i] = head->next;
	}
	else {
		/* o 1o elemento nao e o que queremos, entao procura no resto da posicao i */
		while (head->next->n != n)
			head = head->next;
		aux = head->next;
		head->next = head->next->next;
	}

	/* liberta a memoria do no da hash table que correspondia ao no n*/
	free(aux);
}

/* liberta a memoria da hash table */
void STfree(link** heads) {
	int i;
	link* head;
	link* aux;

	/* percorre todos os elementos da hash table e liberta a memoria */
	for (i = 0; i < HASH_SIZE; i++) {
		head = heads[i];
		while (head) {
			aux = head;
			head = head->next;
			free(aux);
		}
	}
	free(heads);
}