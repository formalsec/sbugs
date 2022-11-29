#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

void insere_lista(Item jogo, link * head) { 

    link novo_no = (link) can_fail_malloc (sizeof(struct node)); /* Cria no */
    novo_no -> jogo = jogo; 
    
    /* Coloca no inicio */
    novo_no -> next = (*head); 
    novo_no -> prev = NULL;
    
    if ((*head) != NULL) /* Verifica se a lista nao esta vazia */
        (*head) -> prev = novo_no;

    (*head) = novo_no; 

} 


void apaga_lista(Item jogo, link * head) { 

    link node;
  
    for (node = *head; node -> next != NULL; node = node -> next) /* Encontra no a apagar */
        if (eq(key(node -> jogo), key(jogo)))
            break; 
  
    /* Altera prev do no seguinte se o no a apagar nao for o ultimo elemento */
    if (node -> next != NULL) 
        (node -> next) -> prev = node -> prev; 
  
    /* Altera next do no anterior se o no a apagar nao for o primeiro elemento */
    if (node -> prev != NULL) 
        (node -> prev) -> next = node -> next; 

    /* Altera head se o no a apagar for o primeiro elemento */
    if (*head == node) 
        *head = node -> next; 

    free(node);

} 


void imprime_lista(int NL, link head) {

    link node;
    
    for (node = head; node -> next != NULL; node = node -> next) /* Encontra ultimo elemento */
        ;

    while (node != NULL) { /* Imprime lista do fim para o inicio */
        imprime_jogo(node -> jogo, NL);
        node = node -> prev;
    }
}


void liberta_lista(link head) {

    link node = head, aux = NULL;

    if (node != NULL)
        while (node != NULL) {
            aux = node;
            node = node -> next;
            free(aux);
            /* Nao e preciso libertar Item guardado no no pois ja o foi em liberta_hash */
        }

    free(node);

}

