#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla.h"

#define MAX_TABELA 1000

/*funcao que insere um elemento no fim da lista*/

void insere_fim_lista(char *el,node_lista **inicio,node_lista **fim) {
    /*cria um no para a lista*/
    node_lista *node = can_fail_malloc(sizeof(node_lista)*1); 
    node->nome = el;
    node->prev = NULL;
    node->next = NULL;

   /*se for o primeiro elemento a adicionar*/
    if(*inicio == NULL) { 
        *inicio = node;
        *fim = node;
        return;
    }

   /*caso contrario*/
   else { 
       /*atualiza a cauda*/
       (*fim)->next = node;
       /*atualiza o membro anterior*/
       node->prev = *fim; 
       *fim = node;
   }

}

/*funcao que remove um elemento da lista*/

void remove_el_lista(char *nome,node_lista **inicio,node_lista **fim) {
    /*iniciar no inicio da lista*/
    node_lista *atual = *inicio;

    while (atual != NULL && atual->nome != nome) {
    /*percorrer lista ate encontra o elemento a remover*/
        atual = atual->next;
    }

    /*se for o primeiro elemento da lista*/
    if (atual->prev == NULL) {
        /*se o elemento for unico*/
        if (atual->next == NULL) {
            *inicio = NULL;
            *fim = NULL;
        } 
        
        /*se houver mais elementos*/
        else {
            *inicio = atual->next;
            (*inicio)->prev = NULL;
        }

        free(atual);
        return;
    }
    
    /*se for o ultimo elemento da lista*/
    else if (atual->next == NULL) {
        atual->prev->next = NULL;
        *fim = atual->prev;

        free(atual);
        return;
    }
    
    /*se for um elemento no meio da lista*/
    else if (atual->prev != NULL && atual->next != NULL) {
        atual->prev->next = atual->next;
        atual->next->prev = atual->prev;

        free(atual);
        return;
    }
}


/*funcao que liberta toda a memoria utilizada para criar os nos da lista*/

void apaga_mem_lista(node_lista **inicio) {
    node_lista *atual = *inicio;
    while(atual != NULL) {
        node_lista *proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}

