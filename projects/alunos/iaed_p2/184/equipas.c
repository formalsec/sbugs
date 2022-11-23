#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "auxiliares.h"


void freeE(linkE* head)
{
    linkE aux1,aux2;
    for(aux1 = *head; aux1 != NULL;)
    {
        free(aux1 -> nome_equipa);
        aux2 = aux1;
        aux1 = aux1 -> next;
        free(aux2);
    }
}

linkE NOVO_E(char* nome)
{
    linkE nova_e = (linkE)can_fail_malloc(sizeof(struct node));
    nova_e -> nome_equipa = (char*)can_fail_malloc(sizeof(char)*(strlen(nome) + 1));
    strcpy(nova_e -> nome_equipa, nome);
    nova_e -> vitorias = 0;
    nova_e -> next = NULL;
    return nova_e;
}

void insereInicio_E(linkE *headptr, char *nome)
{
    linkE nova_e = NOVO_E(nome);
    nova_e -> next = *headptr;
    *headptr = nova_e;
}

linkE encontra_E(linkE head, char *nome)
{
    linkE objetivo;
    for (objetivo = head; objetivo != NULL; objetivo = objetivo -> next)
        if (strcmp(objetivo -> nome_equipa, nome) == 0)
            return objetivo;
    return NULL;
}