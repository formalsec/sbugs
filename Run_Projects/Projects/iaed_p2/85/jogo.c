#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aux.h"
#include "jogo.h"

/* Funcao que cria e inicializa uma nova lista duplamente ligada vazia. */
list new_list()
{
    /* Ponteiro para uma lista duplamente ligada. */
    list ls;
    ls=malloc(sizeof(struct list));
    ls->head=ls->last=NULL;
    return ls;
}

/* Funcao auxiliar que cria o jogo e adiciona-o como o ultimo elemento da lista 
   duplamente ligada. */
pJogo cria_jogo(char *n_jogo, char *eq1, char *eq2, int sc1, int sc2, list ls)
{
    /* Criacao e inicializacao de um ponteiro para a estrutura jogo. */
    pJogo new=malloc(sizeof(struct jogo));
    new->next=NULL;
    new->previous=ls->last;

    new->n_jogo=strdup(n_jogo);
    new->eq1=strdup(eq1);
    new->eq2=strdup(eq2);
    new->sc1=sc1;
    new->sc2=sc2;

    if(sc1>sc2) new->vencedora=strdup(eq1);

    else if(sc2>sc1) new->vencedora=strdup(eq2);

    else new->vencedora=NULL;

    if(ls->last) ls->last->next=new;
    ls->last=new;
    if(!ls->head) ls->head=new;

    return new;
}

/* Funcao auxiliar que imprime o conteudo guardado na estrutura jogo. */
void print_j(pJogo j)
{
    printf("%s %s %s %d %d\n", j->n_jogo, j->eq1, j->eq2, j->sc1, j->sc2);
}

/* Funcao que liberta toda a memoria utilziada pelo jogo. */
void free_jogo(pJogo j)
{
    free(j->n_jogo);
    free(j->eq1);
    free(j->eq2);
    if(j->vencedora) free(j->vencedora);
    free(j);
}

/* Funcao auxiliar que altera o score de um determinado jogo. */
void altera_score_aux(pJogo j, int sc1, int sc2)
{
    j->sc1=sc1;
    j->sc2=sc2;

    if(sc1>sc2)
    {
        free(j->vencedora);
        j->vencedora=strdup(j->eq1);
    }

    else if(sc1<sc2)
    {
        free(j->vencedora);
        j->vencedora=strdup(j->eq2);
    }

    else 
    {
        free(j->vencedora);
        j->vencedora=NULL;
    }
}

/* Funcao que retira um elemento da lista. */
void remove_el(list ls, pJogo j)
{
    if(!j->previous && !j->next) ls->head=ls->last=NULL;

    else if(j->previous && !j->next) 
    {
        ls->last=j->previous;
        j->previous->next=NULL;
    }

    else if(!j->previous && j->next)
    {
        j->next->previous=NULL;
        ls->head=j->next;
    }

    else
    {
        j->previous->next=j->next;
        j->next->previous=j->previous;
    }
}

/* Funcao que imprime a lista. */
void print_list(list ls, int NL)
{
    /* Ponteiro para a variavel auxiliar guarda a copia head e 
    permite que a original nao se altere durante o ciclo. */
    pJogo temp=ls->head;

    while(temp)
    {
        printf("%d ", NL);
        print_j(temp);
        temp=temp->next;
    }
}

/* Funcao que liberta toda a memoria utilizada pela lista. */
void free_list(list ls)
{
    free(ls);
}
