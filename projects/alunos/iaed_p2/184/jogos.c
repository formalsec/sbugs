#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "auxiliares.h"


void freeJ(linkJ *headd)
{
    linkJ t,aux;
    for(t = *headd; t != NULL;)
    {
        free(t -> nome_jogo);
        free(t -> equipa1);
        free(t -> equipa2);
        aux = t;
        t = t -> next;
        free(aux);
    }
}

linkJ NOVO_J(char *jogo, char *e1, char *e2, int p1, int p2)
{
    linkJ novoJ = (linkJ)can_fail_malloc(sizeof(struct node2));
    novoJ -> nome_jogo = (char*)can_fail_malloc(sizeof(char)*(strlen(jogo) + 1));
    novoJ -> equipa1 = (char*)can_fail_malloc(sizeof(char)*(strlen(e1) + 1));
    novoJ -> equipa2 = (char*)can_fail_malloc(sizeof(char)*(strlen(e2) + 1));
    strcpy(novoJ -> nome_jogo, jogo);
    strcpy(novoJ -> equipa1, e1);
    strcpy(novoJ -> equipa2, e2);
    novoJ -> golos1 = p1;
    novoJ -> golos2 = p2;
    novoJ -> next = NULL;
    novoJ -> prev = NULL;
    return novoJ;
}

void insereInicio_J(linkJ *headptr, char *jogo, char *e1, char *e2, int p1, int p2)
{
    linkJ aux;
    linkJ novoJ = NOVO_J(jogo, e1, e2, p1, p2);
    aux = *headptr;
    if(aux == NULL)
        *headptr = novoJ;

    else if((aux != NULL) && (aux -> next == NULL))
    {
        (*headptr) -> prev = novoJ;
        novoJ -> next = (*headptr);
        novoJ -> prev = (*headptr);
        *headptr = novoJ;
    }
    else if((aux != NULL) && aux -> next != NULL)
    {
        novoJ -> next = (*headptr);
        novoJ -> prev = (*headptr) -> prev;
        ((*headptr) -> prev) = novoJ;
        (*headptr) = novoJ;
    }
}

linkJ encontra_J(linkJ head, char *jogo)
{
    linkJ objetivo;
    for (objetivo = head; objetivo != NULL; objetivo = objetivo -> next)
        if (strcmp(objetivo -> nome_jogo, jogo) == 0)
            return objetivo;
    return NULL;
}

void elimina_J(linkJ *headptr, char *jogo)
{
    linkJ ctrl;
    linkJ ant;
    int contador;
    for (ctrl=*headptr, ant=NULL, contador=0; ctrl!=NULL; ant=ctrl, ctrl=ctrl->next, ++contador)
    {
        if (strcmp(ctrl -> nome_jogo, jogo) == 0)
        {
            /*Caso em que a lista contem varios elementos e se pretende remover o primeiro.*/
            if((ctrl == *headptr) && ((ctrl -> next) != NULL))
            {
                ((*headptr) -> next) -> prev = (*headptr) -> prev;
                (*headptr) = ctrl -> next;
            }

            /*Caso em que se pretende retirar um elemento do meio da lista.*/   
            else if(ctrl -> next != NULL)
            {
                ant -> next = ctrl -> next;
                (ctrl -> next) -> prev = ant;
            }

            /*Caso em que se pretende retirar o ultimo elemento da lista.*/
            else if((ctrl -> next == NULL) && (contador != 0))
            {   
                (*headptr) -> prev = ant;
                ant -> next = NULL;
            }

            else if(ctrl == *headptr)
                (*headptr) = NULL;

            free(ctrl -> nome_jogo);
            free(ctrl -> equipa1);
            free(ctrl -> equipa2);
            free(ctrl);            
        }
    }
}
