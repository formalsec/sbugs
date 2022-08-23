#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aux.h"
#include "hash_j.h"

/* Funcao que inicializa a hashtable dos jogos. */
hash_j init_hash_jogo(int m)
{
    int i;
    /* Ponteiro para a hashtable que vai ser inicializada e devolvida pela funcao. */
    hash_j hash;
    hash=malloc(sizeof(struct hash_j));
    hash->M = m;
    hash->heads = malloc(hash->M*sizeof(struct node_j));

    for (i = 0; i < hash->M; i++) 
    {
        hash->heads[i] = NULL;
    }
    return hash;
}

/* Funcao auxiliar para a insercao do jogo na hashtable. */
link_j insert_jogo(link_j head, pJogo j)
{
    /* Ponteiro para a variavel que guarda a antiga cabeca. */
    link_j old_head=head;
    head=malloc(sizeof(struct node_j));
    head->next=old_head;
    head->j=j;
    return head;
}

/* Funcao que insere o jogo na hashtable. */
void STinsert_jogo(hash_j hash, pJogo j)
{
    /* Variavel que guarda o indice da hashtable onde o jogo ficara. */
    int i = hash_chave(hash->M, j->n_jogo);
    hash->heads[i] = insert_jogo(hash->heads[i], j);
}

/* Funcao auxiliar que procura o jogo na hashtable. */
pJogo search_jogo(link_j head, char *n_jogo)
{
    /* Ponteiro para a variavel que garante a execucao do ciclo
    sem alterar a hashtable. */
    link_j temp=head;
    while(temp)
    {
        if(strcmp(temp->j->n_jogo, n_jogo)==0) return temp->j;
        temp=temp->next;
    }
    return NULL;
}

/* Funcao que procura o jogo na hashtable. */
pJogo STsearch_jogo(hash_j hash, char *n_jogo)
{
    /* Variavel que guarda o indice da hashtable onde o jogo esta guardado. */
    int i = hash_chave(hash->M, n_jogo);
    /* Ponteiro para uma variavel jogo generica. */
    pJogo j=NULL;

    if(!hash->heads[i]) 
    {
        return NULL;
    }

    j=search_jogo(hash->heads[i], n_jogo);

    if(!j) return NULL;

    return j;
}

/* Funcao que liberta toda a memoria utilziada pelo no dos jogos. */
void free_link_j(link_j node)
{
    free_jogo(node->j);
    free(node);
}

/* Funcao auxiliar que retira o jogo da hashtable e liberta a memoria associada. */
link_j delete_jogo(link_j head, char *n_jogo)
{
    /* Ponteiro para a variavel que garante a execucao do ciclo
    sem alterar a hashtable. */
    link_j temp = head;
    /* Ponteiro para a variavel auxiliar que guarda o no anterior. */
    link_j prev=NULL;

    while(temp)
    {
        if(!strcmp(temp->j->n_jogo, n_jogo))
        {
            if(temp==head) head=temp->next;
            
            else prev->next=temp->next;

            free_link_j(temp);
            break;
        }
        prev=temp;
        temp=temp->next;
    }
    return head;
}

/* Funcao que retira o jogo da hashtable. */
void STdelete_jogo(hash_j hash, char *n_jogo)
{
    /* Variavel que guarda o indice da hashtable onde o jogo esta guardado. */
    int i = hash_chave(hash->M, n_jogo);
    hash->heads[i] = delete_jogo(hash->heads[i], n_jogo);
}

/* Funcao que liberta toda a memoria utilizada pela hashtable dos jogos. */
void freeHash_j(hash_j hash)
{
    int i;
    /* Ponteiro para a variavel que garante a execucao do ciclo. */
    link_j temp;
    for (i = 0; i < hash->M; i++)
    {
        temp=hash->heads[i];
        while(hash->heads[i])
        {
            temp=hash->heads[i];
            hash->heads[i]=hash->heads[i]->next;
            free_link_j(temp);

        }
        free(hash->heads[i]);
    }
    free(hash->heads);
    free(hash);
}
