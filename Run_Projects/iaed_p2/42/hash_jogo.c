#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_jogo.h"


/* incializa uma hashtable de jogos */
linkJ* InitJogo(int M){
    int i;
    linkJ* heads; /* hashtable */
    
    /* aloca memoria para M linkJ em que M eh o tamanho da hashtable */
    heads = (linkJ*)malloc(M*sizeof(linkJ));

    /* inicializa todos os elementos da hashtable a NULL */
    for (i=0; i<M; i++)
        heads[i]=NULL;

    /* devolve a hashtable */ 
    return heads;
}



/* insere um jogo no inicio de uma lista */
linkJ InsertJogo(pJogo j,linkJ head){

    /* aloca memoria para um novo no */
    linkJ new = (linkJ)malloc(sizeof(struct nodeJ));

    /* atribui o jogo ao novo no */
    new->jogo=j; 

    /* coloca o novo no no inicio da lista */
    new->next = head;
    new->prev = NULL;

    /* se a lista nao for vazia, new passa a ser o jogo anterior a antiga cabeca */
    if ( head != NULL )
        head->prev = new;

    /* devolve a nova cabeca da lista */
    return new;
}



/* apaga um jogo */
linkJ DeleteJogo(linkJ j,linkJ head){
    /*j eh o jogo que vai ser apagado */

    /* se j eh a cabeca, a cabeca passa a ser no a seguir a j */
    if (j==head){ 
        head = j->next;

        /* atualiza o prev da nova cabeca */
        if (head != NULL) 
            head->prev=NULL;
    }

    else{
        /* retira j da lista */
        j->prev->next = j->next; /* atualiza o no anterior */
        if (j->next!=NULL) 
            j->next->prev = j->prev; /* atualiza o no seguinte */
    }

    /* liberta j e o jogo para o qual este aponta */
    freeJogo(j->jogo);
    free(j); 

    return head;
}



/* procura um jogo */
linkJ SearchJogo(char *nome,linkJ head) {
    linkJ x;
    /* x percorre a lista */
    for (x=head;x!=NULL;x=x->next){
        /* verifica se o nome do jogo corresponde ao nome dado */
        if (strcmp(x->jogo->nome,nome) == 0)
            return x;
    }
    /* devolve NULL caso nao encontre nenhum jogo com o nome dado */
    return NULL;
}



/* liberta uma hashtable de jogos */
void FreeHashJogo(int M,linkJ * heads){
    linkJ x,prev;
    int i;
    /* x percorre todos os jogos da hashtable*/
    for(i=0;i<M;i++){
        x = heads[i];
        while(x!=NULL){

            /* prev eh o jogo anterior a x */
            prev=x;
            x=x->next;

            /* liberta prev e o jogo para o qual este aponta */
            freeJogo(prev->jogo);
            free(prev);
        }
    }

    free(x); /* liberta x */    
}