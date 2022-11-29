#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"
#include "jogos.h"
#include "auxiliares.h"


int vencedor(int p1, int p2)
{
    if(p1 == p2)
        return EMPATE;
    else
    {
        if(p1 > p2)
            return VIT1;
        else
            return VIT2;
    }
}

void vitorias(linkE head, int p1, int p2, char *equipa_1, char *equipa_2, hptr *h1)
{
    linkE aux;
    int vence;
    vence = vencedor(p1,p2);
    if(vence == VIT1)
    {
        aux = encontra_E(head, equipa_1);
        ++(aux -> vitorias);
        (*h1) -> max_vit = aux -> vitorias;
        
    }
    else if(vence == VIT2)
    {
        aux = encontra_E(head, equipa_2);
        ++(aux -> vitorias);
        (*h1) -> max_vit = aux -> vitorias;
    }

    
}

void retira_pontos(linkJ jogo, linkE headE, hptr *h1)
{
    int p1, p2,vence;
    linkE aux;
    p1 = jogo -> golos1;
    p2 = jogo -> golos2;
    vence = vencedor(p1, p2);    
    if(vence == VIT1)
    {
        aux = encontra_E(headE, jogo -> equipa1);
        --(aux -> vitorias);
    }
    else if(vence == VIT2)
    {
        aux = encontra_E(headE, jogo -> equipa2);
        --(aux -> vitorias);
    }

    if ((aux -> vitorias > (*h1) -> max_vit) && vence != EMPATE)
        (*h1) -> max_vit = aux -> vitorias;
}

void SelectionSort(char **nomes, int left, int right)
{
    int i, j, result, min;
    char *aux;
    for (i = left; i < right-1; i++)
    {
        min = i;
        
        for(j = i+1; j < right; j++)
        {
            result = strcmp(nomes[j],nomes[min]);
            if(result < 0)
                min = j;
        }
        aux = nomes[i];
        printf("%s\n",nomes[i]);
        nomes[i] = nomes[min];
        nomes[min] = aux;
    }
}

void aumenta(hptr* headH, int n)
{
    if(n == INI)
    {
        arm novo_arm;
        hptr aux;
        aux = (arm*)can_fail_malloc(sizeof(arm));
        novo_arm.cont = 0;
        novo_arm.max_vit = 0;
        (*aux) = novo_arm;
        (*headH) = aux;
    }
    else
        ++((*headH) -> cont);    
}
