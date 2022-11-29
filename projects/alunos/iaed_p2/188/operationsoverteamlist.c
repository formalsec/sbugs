#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "operationsoverteamlist.h"


team NEW(char *buffer)
{
    /* Insere uma nova equipa */
    team x = (team)can_fail_malloc(sizeof(struct equipa));
    x->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(buffer) + 1));
    strcpy(x->nome, buffer);
    x->vitorias = 0;
    x ->next= NULL;
    return x;
}

team insertBegin(team head, char *text)
{
    /* Coloca uma nova cabeca */
    team x = NEW(text);
    x->next = head;
    return x;
}

team analisaVitorias(char *equipa1, char *equipa2, int V1, int V2, team equipa)
{
    team equipaVencedora;
    /* Analisa equipas vencedoras */
    if (V1 > V2)
    {
        equipaVencedora = searchTeams(equipa1, equipa);
        equipaVencedora->vitorias += 1;
    }
    else if (V2 > V1)
    {
        equipaVencedora = searchTeams(equipa2, equipa);
        equipaVencedora->vitorias +=1;
    }
    return equipa;
}



team searchTeams(char *text, team head)
{
    /* Procura nas equipas */
    team t; 
    for (t = head; t != NULL;t = t->next)
    {
        if (strcmp(t ->nome, text) == 0)
        {
            return t;
        }
    }
    free(t);
    return NULL;
}


void Remove_Vitoria(char *equipa1, char *equipa2, int V1, int V2, team equipa)
{
    /* Retira vitorias no caso de uma equipa ser removida */
    team equipaVencedora;
    if (V1 >= V2)
    {
        equipaVencedora = searchTeams(equipa1, equipa);
        if (equipaVencedora->vitorias > 0)
            equipaVencedora->vitorias -= 1;
    }
    else if (V2 >= V1)
    {
        equipaVencedora = searchTeams(equipa2, equipa);
        if (equipaVencedora->vitorias > 0)
            equipaVencedora->vitorias -=1;
    }
}

void Retira_Vitoria(char *nome, team equipa)
{
    /* Utilizada na funcao s */
    team equipaLost;
    equipaLost = searchTeams(nome, equipa);
    if (equipaLost->vitorias > 0)
        equipaLost->vitorias -= 1;
}

void Adiciona_Vitoria(char *nome, team equipa)
{
    /* Utilizad na funcao s */
    team equipaWon;
    equipaWon = searchTeams(nome, equipa);
    equipaWon -> vitorias += 1;
}

int comprimento(team equipa)
{
    /* Verifica o comprimento de uma estrutura */
    int count = 0;
    team x = equipa;
    while( x!= NULL)
    {
        count++;
        x=x->next;
    }
    return count;
}

int cmpfunc(const void* a, const void* b)
{
    /* Funcao utilizada no qsort que serve para comparar duas strings */
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}


team libertaequipa(team equipa)
{
    /* da free da lista das equipas */
    if (equipa != NULL)
    {
        team old;
        old = equipa;
        equipa = equipa ->next;
        free(old->nome);
        free(old);
    }
    return equipa;
}