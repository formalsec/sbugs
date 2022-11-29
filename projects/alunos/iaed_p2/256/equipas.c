#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash_equipa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M;
equipa **head_hash_e;
jogo **head_hash_j;

lista_e*  mk_lista_e(){
    lista_e*l=can_fail_malloc(sizeof(lista_e));
    l->head = l->last = NULL;
    return l;
}

lista_j*  mk_lista_j(){
    lista_j*l=can_fail_malloc(sizeof(lista_j));
    l->head = l->last = NULL;
    return l;
}

void free_list_equipa(lista_e*l){
    while(l->head){
        equipa*tmp=l->head->next;
        free(l->head->nome);
        free(l->head);
        l->head=tmp;
    }
    free(l);
}

void free_list_jogo(lista_j*l){
    while(l->head){
        jogo*tmp=l->head->next;
        free(l->head->nome);
        free(l->head);
        l->head=tmp;
    }
    free(l);
}

void add_last_equipa(lista_e*l,const char*n){
    equipa*nn=can_fail_malloc(sizeof(equipa));
    nn->prev=l->last;
    nn->next=NULL;
    nn->nome=can_fail_malloc(sizeof(char)*(strlen(n)+1));
    strcpy(nn->nome,n);
    nn->vitorias=0;
    if(l->last) l->last->next=nn;
    else l->head =nn;
    l->last=nn;
}

void add_last_jogo(lista_j*l,const char*n, equipa *e1, equipa *e2, int o, int i){
    jogo*nn=can_fail_malloc(sizeof(jogo));
    nn->prev=l->last;
    nn->next=NULL;
    nn->nome=can_fail_malloc(sizeof(char)*(strlen(n)+1));
    strcpy(nn->nome,n);
    nn->e1=e1;
    nn->e2=e2;
    nn->resultado1=o;
    nn->resultado2=i;
    if(l->last) l->last->next=nn;
    else l->head =nn;
    l->last=nn;
}

void rm_equipa(lista_e*l,equipa*n){
    if(n->prev==NULL){
        l->head=n->next;
    }else{
        n->prev->next=n->next;
    }
    if(n->next==NULL){
        l->last=n->prev;
    }else{
        n->next->prev=n->prev;
    }
    free(n->nome);
    free(n);
}

void rm_jogo(lista_j*l,jogo*n){
    if(n->prev==NULL){
        l->head=n->next;
    }else{
        n->prev->next=n->next;
    }
    if(n->next==NULL){
        l->last=n->prev;
    }else{
        n->next->prev=n->prev;
    }
    free(n->nome);
    free(n);
    n=NULL;
}

equipa* lookup_e(char* text) {
    int i=hash(text,M);
    equipa *t;
    for(t =head_hash_e[i]; t != NULL; i=(i+1)%M,t=head_hash_e[i])
        if(strcmp(t->nome, text) == 0)
        return t;
     return NULL;
}

jogo* lookup_j(char* text) {
    int i=hash(text,M);
    while(head_hash_j[i]!=NULL)
        if(strcmp(head_hash_j[i]->nome,text)==0)
            return head_hash_j[i];
        else
            i=(i+1)%M;
    return NULL;
}
