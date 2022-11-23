#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_equipa.h"

/* inicializa uma hashtable de equipas */
linkE* InitEquipa(int M){
    int i;
    linkE* heads; /* hashtable */
    
    /* aloca memoria para M linkE em que M eh o tamanho da hashtable */
    heads = (linkE*)can_fail_malloc(M*sizeof(linkE));

    /* inicializa todos os elementos da hashtable a NULL */
    for (i=0; i<M; i++)
        heads[i]=NULL; 
    
    /* devolve a hashtable*/
    return heads;
}


/* insere uma equipa no inicio de uma lista */
linkE InsertEquipa(char *nome,linkE head){
    /* aloca memoria para um no novo */
    linkE new = (linkE)can_fail_malloc(sizeof(struct nodeE));
    /* atribui a equipa ao novo no */
    new->equipa=newEquipa(nome);
    /* a cabeca da lista passa a ser o novo no */
    new->next = head;
    /* devolve a nova cabeca da lista */
    return new;
}


/* procura uma equipa */
pEquipa SearchEquipa(char *nome,linkE head) {
    linkE x;
    /* x percorre a lista */
    for (x=head;x!=NULL;x=x->next){
        /* verifica se o nome da equipa de x corresponde ao nome dado */
        if (strcmp(x->equipa->nome,nome) == 0)
            return x->equipa;
    }
    /* devolve NULL caso a equipa nao exista na lista */
    return NULL;
}


/* liberta uma hashtable de equipas */
void FreeHashEquipa(int M,linkE * heads){
    linkE x,prev;
    int i;
    /* xpercorre todas as equipas da hashtable */
    for(i=0;i<M;i++){
        x=heads[i];
        while(x!=NULL){

            /* prev eh o jogo anterior a x */
            prev=x;
            x=x->next;

            /* liberta x e a equipa para a qual este aponta */
            freeEquipa(prev->equipa);
            free(prev);
        }
    }
    free(x); /* liberta x */
}