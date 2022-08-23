#include "hash_equipa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M;
equipa **head_hash_e;
jogo **head_hash_j;

int hash(char *v, int M){
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

void init_hash_equipa(int m){
    int i;
    M=m;
    head_hash_e=malloc(M*sizeof(equipa*));
    for (i = 0; i < M; i++)
        head_hash_e[i] = NULL;
}

void init_hash_jogo(int m){
    int i;
    M=m;
    head_hash_j=malloc(M*sizeof(jogo*));
    for (i = 0; i < M; i++)
        head_hash_j[i] = NULL;
}

void hash_equipa_insert(equipa*p){
    int i = hash(p->nome,M);
    while(head_hash_e[i]!=NULL)
        i=(i+1)%M;
    head_hash_e[i]=p;
}

void hash_jogo_insert(jogo*p){
    int i = hash(p->nome,M);
    while(head_hash_j[i]!=NULL)
        i=(i+1)%M;
    head_hash_j[i]=p;
}

void hash_delete_j(char*id){
    int j, i = hash(id,M);
    jogo*v;
    while (head_hash_j[i] != NULL)
        if (strcmp(head_hash_j[i]->nome,id)==0)
            break;
        else
            i = (i+1) % M;
    head_hash_j[i] = NULL;
    for (j = (i+1) % M; head_hash_j[j] != NULL; j = (j+1) % M){
        v = head_hash_j[j];
        head_hash_j[j] = NULL;
        hash_jogo_insert(v);
    }
}
