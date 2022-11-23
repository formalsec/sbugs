#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista_jogos.h"

/* inicializa a lista */
lista * InitLista(){
    lista * new;
    /* aloca espaco para uma lista */
    new=(lista*)can_fail_malloc(sizeof(lista));

    /* inicializa a head e a tail da lista a NULL */
    new->head=NULL;
    new->tail=NULL;
    
    return new;
}


/* insere um elemento no fim da lista */
lista* InsertEndLista(pJogo j,lista * l){

    /* aloca espaco para um nodeJ */
    linkJ new = (linkJ)can_fail_malloc(sizeof(struct nodeJ));

    new->jogo=j;
    new->next=NULL; 

    /* se a lista for vazia, a head e tail da lista vao ser o novo elemento */
    if (l->head==NULL){
        l->head=new;
        l->tail=new;
    }

    /* caso contrario, insere o elemento depois da tail */
    else {
        l->tail->next=new;
        l->tail=new; /* a tail passa a ser o novo elemento */
    }
    
    return l;
}


/* apaga um elemento da lista */
lista * DeleteLista(char *nome,lista *l){
    linkJ x,prev;

    prev=NULL; /* prev eh o elemento que antecede x */

    /* x percorre lista */
    for ( x=l->head; x!= NULL;x=x->next){

        /* verifica se o jogo de x eh o que esta ser procurado */
        if(strcmp(x->jogo->nome,nome) == 0){
            /* se x eh a head da lista, a head passa a ser o elemento seguinte */
            if (x==l->head) 
                l->head = x->next;

            /* se x eh a tail, a tail passa a ser o elemento anterior a x */
            else if (x==l->tail){
                l->tail=prev;
                l->tail->next=NULL;
            }
        
            else
                prev->next = x->next;

            /* liberta x */
            free(x); 
            /* sai do ciclo */
            break;          
        }
        /* atualiza prev */
        prev=x;
    }
    return l;
}


/* imprime a lista */
void printLista(lista * l,int nl){
    linkJ x;
    /* x percorre a lista */
    for(x=l->head;x!=NULL;x=x->next){
        /* imprime numero da linha */
        printf("%d ",nl);
        /* imprime o jogo */
        printJogo(x->jogo);
    }
}

/* liberta a lista */
void freeLista(lista *l){
    linkJ x;
    /* x percorre a lista */
    x = l->head;
    while (x!=NULL){
        /* atualiza a head da lista */
        l->head = l->head->next;

        /* liberta a head anterior */
        free(x);

        x=l->head;
    }

    /* a head e tail da lista passam a ser NULL */
    l->head=NULL;
    l->tail=NULL;
}