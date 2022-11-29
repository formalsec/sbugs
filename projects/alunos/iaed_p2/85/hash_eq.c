#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aux.h"
#include "hash_eq.h"

/* Funcao que inicializa a hashtable das equipas. */
hash_eq init_hash_eq(int m)
{
    int i;
    /* Ponteiro para a hashtable que vai ser inicializada e devolvida pela funcao. */
    hash_eq hash;
    hash=can_fail_malloc(sizeof(struct hash_eq));
    hash->M = m;
    hash->heads = can_fail_malloc(hash->M*sizeof(struct node_eq));

    for (i = 0; i < hash->M; i++) 
    {
        hash->heads[i] = NULL;
    }
    return hash;
}

/* Funcao auxiliar para a insercao da equipa na hashtable. */
link_eq insert_eq(link_eq head, pEquipa eq)
{
    /* Ponteiro para a variavel que guarda a antiga cabeca. */
    link_eq old_head=head;
    head=can_fail_malloc(sizeof(struct node_eq));
    head->next=old_head;
    head->eq=eq;
    return head;
}

/* Funcao que insere a equipa na hashtable. */
void STinsert_eq(hash_eq hash, pEquipa eq)
{
    /* Variavel que guarda o indice da hashtable onde a equipa esta guardada. */
    int i = hash_chave(hash->M, eq->n_eq);
    hash->heads[i] = insert_eq(hash->heads[i],eq);
}

/* Funcao auxiliar que procura o jogo na hashtable. */
pEquipa search_eq(link_eq head, char *n_eq)
{
    /* Ponteiro para a variavel que garante a execucao do ciclo
    sem alterar a hashtable. */
    link_eq temp=head;
    while(temp)
    {
        if(strcmp(temp->eq->n_eq, n_eq)==0) return temp->eq;
        temp=temp->next;
    }
    return NULL;
}

/* Funcao que procura o jogo na hashtable. */
pEquipa STsearch_eq(hash_eq hash, char *n_eq)
{
    /* Variavel que guarda o indice da hashtable2 onde a equipa esta guardada. */
    int i = hash_chave(hash->M, n_eq);
    /* Ponteiro para uma variavel equipa generica. */
    pEquipa eq=NULL;

    if(!hash->heads[i]) return NULL;

    eq=search_eq(hash->heads[i], n_eq);

    if(!eq) return NULL;

    return eq;
}

/* Funcao que que corrige as vitorias das equipas apos a alteracao dos scores. */
void corrige_wins(hash_eq hash_eq, pJogo j, char *old_vencedora)
{
    if((!j->vencedora && !old_vencedora) || 
        (j->vencedora && old_vencedora && strcmp(j->vencedora, old_vencedora)==0)) return;

    else if(!j->vencedora && old_vencedora)
    {
        STsearch_eq(hash_eq, old_vencedora)->wins--;
        return;
    }

    else if(j->vencedora && !old_vencedora)
    {
        STsearch_eq(hash_eq, j->vencedora)->wins++;
        return;
    }

    else
    {
        STsearch_eq(hash_eq, old_vencedora)->wins--;
        STsearch_eq(hash_eq, j->vencedora)->wins++;
        return;
    }
}

/* Funcao que calcula o maximo de vitorias e o numero de equipas com essas vitorias. */
void calcula_max(hash_eq hash, int *max, int *num_eq)
{
    int i;
    /* Ponteiro para a variavel que garante a execucao do ciclo
    sem alterar a hashtable. */
    link_eq temp = NULL;

    for(i=0; i<hash->M; i++)
    {
        temp=hash->heads[i];
        while(temp)
        {
            if(temp->eq->wins == *max) (*num_eq)++;

            if(temp->eq->wins > *max)
            {
                *num_eq=1;
                *max=temp->eq->wins;
            }
            temp=temp->next;
        }
    }
}

/* Funcao auxiliar para o qsort. */
int comparestr(const void*pa, const void*pb)
{
    char **v1, **v2;
    v1=(char**)pa;
    v2=(char**)pb;
    return strcmp(*v1, *v2);
}

/* Funcao que imprime as equipas com o numero maximo de vitorias por ordem lexiografica. */
void imprime_vencedoras(hash_eq hash, int max, int num_eq, int NL)
{
    int i, j=0;
    /* Vetor que contem os nomes das equipas com o maximo de wins. */
    char **equipas;
    /* Ponteiro para a variavel que garante a execucao do ciclo
    sem alterar a hashtable. */
    link_eq temp = NULL;

    equipas=(char**)can_fail_malloc(sizeof(char*)*num_eq);

    for(i=0; i<hash->M && j!=num_eq; i++)
    {
        temp=hash->heads[i];
        while(temp)
        {
            if(temp->eq->wins == max)
            {
                equipas[j++]=strdup(temp->eq->n_eq);
            }
            temp=temp->next;
        }
    }
    
    qsort(equipas, num_eq, sizeof(char*), comparestr);

    printf("%d Melhores %d\n", NL, max);
    for(i=0; i<num_eq; i++)
    {
        printf("%d * %s\n", NL, equipas[i]);
        free(equipas[i]);
    }
    free(equipas);
}

/* Funcao que liberta toda a memoria utilziada pelo no das equipas. */
void free_link_eq(link_eq node)
{
    free_eq(node->eq);
    free(node);
}

/* Funcao que liberta toda a memoria utilizada pela a hashtable das equipas. */
void freeHash_eq(hash_eq hash)
{
    int i;
    /* Ponteiro para a variavel que garante a execucao do ciclo. */
    link_eq temp;
    for (i = 0; i < hash->M; i++)
    {
        temp=hash->heads[i];
        while(hash->heads[i])
        {
            temp=hash->heads[i];
            hash->heads[i]=hash->heads[i]->next;
            free_link_eq(temp);

        }
        free(hash->heads[i]);
    }
    free(hash->heads);
    free(hash);
}
