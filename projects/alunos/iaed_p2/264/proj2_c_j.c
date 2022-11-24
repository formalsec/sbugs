#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2_h.h"

int M;
hash_link_j *head_h_j;
hash_link_e *head_h_e;

list_j *mk_list_j(){			/*Criar lista duplamente ligada para os jogos*/
    list_j *l = can_fail_malloc(sizeof(list_j));
	l->head =l->last=NULL;
    return l;
}

void insertEnd_j(list_j* ls_j, char* n,link_e e1,link_e e2,int s1,int s2){	/*Inserir jogo na lista*/
    	link_j x = can_fail_malloc(sizeof(struct jogo));

	x->nome = can_fail_malloc(sizeof(char)*(strlen(n)+1));
	strcpy(x->nome, n);

	x->equ1 = e1;
	x->equ2 = e2;
	x->sco1 = s1;
	x->sco2 = s2;

	x->next = NULL;
	x->prev = ls_j->last;

	if (ls_j->last)
        ls_j->last->next = x;
    else ls_j->head=x;
    ls_j->last=x;
}

void Init_hash_j(int m) {		/*Criar hashtable para os jogos*/
    int i;
    M = m;
    head_h_j = can_fail_malloc(M*sizeof(hash_link_j));
    for (i = 0; i < M; i++)
        head_h_j[i] = NULL;
}

void insert_h_j(link_j j) {		/*Inserir jogo na hashtable*/
    int i = hash_s(j->nome, M);
    hash_link_j t;
    t = can_fail_malloc(sizeof(struct node_j));
    t->jo=j;
    t->next = head_h_j[i];
    head_h_j[i]= t;
}

link_j lookup_j(char *v) {		/*Procurar na hashtable por um jogo com esse nome*/
    int i=hash_s(v, M);
    hash_link_j t;

    for(t = head_h_j[i]; t != NULL; t = t->next)
		if(strcmp(t->jo->nome, v) == 0)
			return t->jo;

    return NULL;
}

void delete_h_j(link_j j) {		/*Apagar jogo da hashtable*/
    int i = hash_s(j->nome, M);
    hash_link_j t, prev;

    for(t = head_h_j[i], prev = NULL; t != NULL;prev = t, t = t->next){
        if(strcmp(t->jo->nome, j->nome) == 0) {
            if(t == head_h_j[i])
                head_h_j[i] = t->next;
            else
                prev->next = t->next;
			free(t);
			break;
        }
    }
}

void delete_j(list_j* ls_j, link_j j) {	/*Apagar jogo da lista duplamente ligada*/
    if(j == ls_j->head)
        ls_j->head = j->next;
    else
        j->prev->next = j->next;
    if(j == ls_j->last)
        ls_j->last = j->prev;
    else
        j->next->prev = j->prev;

    free(j->nome);
    free(j);
}
