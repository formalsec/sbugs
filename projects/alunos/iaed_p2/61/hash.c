#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

struct _hash{
    int M;
    table_ptrs tabela;

};

hashtable* criahash(int M){

    hashtable* new;
    new = (hashtable*)can_fail_malloc(sizeof(hashtable));
    new->M = M;
    new->tabela=(table_ptrs)can_fail_calloc(M,sizeof(list*));

    return new;
}

int hash(char *v, int M){

    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1)){

        h = (a*h + *v) % M;
    } 

    return h;
}

void inserehash(hashtable* st,Item elemento,char* nome){

    int indice;
    indice = hash(nome, st->M);

    /*verificar se a lista do indice esta vazia, se sim cria lista*/
    if(st->tabela[indice]==NULL){

        st->tabela[indice] = crialista();
        
    }

    /*caso ja haja uma lista no indice dado, adiciona elemento a lista*/
    adicionalista(st->tabela[indice], elemento);
    return;

}

void removehash(hashtable* st,Item elemento,char* nome){
    int indice;
    indice = hash(nome, st->M);

    /*se nao houver lista, nao faz nada*/
    if(st->tabela[indice] == NULL){
        return;
    }
    
    /*remove elemento da lista do indice dado*/
    removelista(st->tabela[indice],elemento);
    return;

}

list* lehash(hashtable* st, char* nome){
    int indice;
    indice = hash(nome, st->M);
    return st->tabela[indice];

}


void freehash(hashtable* st, int M, int controlo, void freeitem(Item)){
    int i;
    /*free das listas de cada indice da hashtable*/
    for(i=0; i<M; i++){

        if(st->tabela[i]!=NULL){
            freelista(st->tabela[i], controlo, freeitem);
        }

    }
    
    free(st->tabela);

    free(st);

    return;

}

list* indice_hastable(hashtable* st, int i){
    return st->tabela[i];
}

