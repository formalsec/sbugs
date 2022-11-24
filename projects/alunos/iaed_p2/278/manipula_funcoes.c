#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "declaracoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Funcao responsavel por determinar o indice nas hashtables*/
int hash(char *v, int M){

	int h = 0, a = 127;

	for (; *v != '\0'; v++)

		h = (a*h + *v) % M;

	return h;
}

/*Procura na hashtable do jogo, o nome passado por argumento*/
link_j pesquisa_jogo(link_j* heads_j, char* nome){

	int i = hash(nome, HASHTABLESIZE_J);
	link_j t;

	for(t = heads_j[i]; t; t = t->next)
		if(compara(t->j->nome, nome) == 0)
			return t;
	return NULL;
}

/*Procura na hashtable da equipa, o nome passado por argumento*/
link_e pesquisa_equipa(link_e* heads_e, char* nome){

	int i = hash(nome, HASHTABLESIZE_E);
	link_e t;

	for(t = heads_e[i]; t; t = t->next)
		if(compara(t->e.nome, nome) == 0)
			return t;
	return NULL;
}

/*Aloca memoria para criar um no para a hashtable do jogo e passa por referencia na funcao adiciona_fim o
 endereco do jogo que cada ponteiro da estrutura da lista duplamente ligada vai apontar*/
link_j cria_jogo_node(lista * ls, char* buffer_nome, char* buffer_equipa1,char* buffer_equipa2,int p1, int p2){

	jogo* jogo;

	link_j x = can_fail_malloc(sizeof(struct node_jogo));

	x->j = can_fail_malloc(sizeof(struct jogo));

	x->j->nome = can_fail_malloc(sizeof(char)*(strlen(buffer_nome)+1));
	copia(x->j->nome, buffer_nome);

	x->j->equipa1 = can_fail_malloc(sizeof(char)*(strlen(buffer_equipa1)+1));
	copia(x->j->equipa1, buffer_equipa1);

	x->j->equipa2 = can_fail_malloc(sizeof(char)*(strlen(buffer_equipa2)+1));
	copia(x->j->equipa2, buffer_equipa2);

	x->j->p1 = p1;

	x->j->p2 = p2;

	x->next = NULL;

	jogo = x->j; /*Endereco da estrutura jogo*/

	adiciona_fim(ls, jogo);

	return x;
}

/*Aloca memoria para criar um no para a hashtable da equipa*/
link_e cria_equipa_node(char* buffer_nome){

	link_e x = can_fail_malloc(sizeof(struct node_equipa));

	x->e.nome = can_fail_malloc(sizeof(char)*(strlen(buffer_nome)+1));
	copia(x->e.nome, buffer_nome);

	x->e.vitorias = 0;

	x->next = NULL;

	return x;
}

/*Retorna o ponteiro para a estrura do no criada*/
link_j insere_jogo_inicio(lista * ls, link_j head, char* nome, char* equipa1, char* equipa2, int p1, int p2){

	link_j x = cria_jogo_node(ls, nome, equipa1, equipa2, p1, p2);
	
	x->next = head;
	
	return x;
}

/*Retorna o ponteiro para a estrura do no criada*/
link_e insere_equipa_inicio(link_e head, char* nome){

	link_e x = cria_equipa_node(nome);
	
	x->next = head;
	
	return x;
}

/*Adiciona os novos nos ao fim da lista*/
void adiciona_fim(lista * l, jogo* j){

	node_j * nn = can_fail_malloc(sizeof(node_j));
	nn->previous = l->last;
	nn->next = NULL;

	nn->j = j;

	if(l->last)
		l->last->next = nn;
	else
		l->head = nn;

	l->last = nn;

}

/*Apaga um no de um jogo*/
link_j apaga_node_jogo(link_j head, char* nome){

	link_j t, prev;

	for(t = head, prev = NULL; t; prev = t, t = t->next){
		if(compara(t->j->nome, nome) == 0) {
			if(t == head)
				head = t->next;
			else
				prev->next = t->next;
			apaga(t->j->nome);
			apaga(t->j->equipa1);
			apaga(t->j->equipa2);
			apaga(t->j);
			apaga(t);
			return head;
		}
	}
	return head;
}

/*Remove um no da lista, libertando o ponteiro para o no*/
void remove_node(lista *l, node_j *n){

	if(n->previous == NULL)
		l->head = n->next;
	 else
		n->previous->next = n->next;
	
	if(n->next == NULL)
		l->last = n->previous;
	 else
		n->next->previous = n->previous;
	
	apaga(n);
}

/*Funcao comparadora para o algoritmo de ordenacao quicksort*/
int comparador(const void *a, const void *b){

    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return compara(*ia, *ib); 
} 