#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2_h.h"

int M;
hash_link_j *head_h_j;
hash_link_e *head_h_e;

list_e *mk_list_e(){			/*Criar lista duplamente ligada para as equipas*/
    list_e *l = can_fail_malloc(sizeof(list_e));
    l->head =l->last=NULL;
    return l;
}

void insertEnd_e(list_e* ls_e, char* n){	/*Inserir equipa na lista*/
	link_e x = can_fail_malloc(sizeof(struct equipa));

	x->nome = can_fail_malloc(sizeof(char)*(strlen(n)+1));
	strcpy(x->nome, n);
    x->jogos_ganhos=0;
	x->next = NULL;
	x->prev = ls_e->last;

	if (ls_e->last)
        ls_e->last->next = x;
    else
        ls_e->head=x;
    ls_e->last=x;
}

void Init_hash_e(int m) {		/*Criar hashtable para as equipas*/
    int i;
    M = m;
    head_h_e = can_fail_malloc(M*sizeof(hash_link_e));
    for (i = 0; i < M; i++)
        head_h_e[i] = NULL;
}

void insert_h_e(link_e e) {		/*Inserir equipa na hashtable*/
    int i = hash_s(e->nome, M);
    hash_link_e t;
    t = can_fail_malloc(sizeof(struct node_e));
    t->eq=e;
    t->next = head_h_e[i];
    head_h_e[i]= t;
}

link_e lookup_e(char *v) {		/*Procurar na hashtable por uma equipa com esse nome*/
    int i=hash_s(v, M);
    hash_link_e t;

    for(t = head_h_e[i]; t != NULL; t = t->next)
		if(strcmp(t->eq->nome, v) == 0)
			return t->eq;

    return NULL;
}

void delete_h_e(link_e e) {		/*Apagar equipa da hashtable*/
    int i = hash_s(e->nome, M);
    hash_link_e t, prev;

    for(t = head_h_e[i], prev = NULL; t != NULL;prev = t, t = t->next){
        if(strcmp(t->eq->nome, e->nome) == 0) {
            if(t == head_h_e[i])
                head_h_e[i] = t->next;
            else
                prev->next = t->next;
            free(t);
			break;
        }
    }
}

void delete_e(list_e* ls_e, link_e e) {	/*Apagar equipa da lista duplamente ligada*/
    if(e == ls_e->head)
        ls_e->head = e->next;
    else
        e->prev->next = e->next;
    if(e == ls_e->last)
        ls_e->last = e->prev;
    else
        e->next->prev = e->prev;

    free(e->nome);
    free(e);
}
