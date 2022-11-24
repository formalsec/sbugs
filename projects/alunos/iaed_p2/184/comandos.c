#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
#include "auxiliares.h"

void A(linkE *headEptr,hptr *h1)
{
    char *nome_equipa;
    linkE aux;
    nome_equipa = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]", nome_equipa);

    aux = encontra_E(*headEptr, nome_equipa);
    if(aux == NULL)
        insereInicio_E(headEptr, nome_equipa);
    else
        printf("%d Equipa existente.\n", (*h1) -> cont);
    
    free(nome_equipa);
}

void a(linkJ *headJptr, linkE headE, hptr *h1)
{
    char *jogo, *e1, *e2;
    int p1, p2;
    jogo = (char*)can_fail_malloc(sizeof(char)*MAX);
    e1 = (char*)can_fail_malloc(sizeof(char)*MAX);
    e2 = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", jogo, e1, e2, &p1, &p2);

    if (encontra_J(*headJptr, jogo) != NULL)
        printf("%d Jogo existente.\n", (*h1) -> cont);
    else if ((encontra_E(headE, e1) == NULL) || (encontra_E(headE, e2) == NULL))
        printf("%d Equipa inexistente.\n", (*h1) -> cont);
    else
    {   
        insereInicio_J(headJptr,jogo,e1,e2,p1,p2);
        vitorias(headE,p1,p2,e1,e2,h1);
    }

    free(jogo);
    free(e1);
    free(e2);
}

void p(linkJ *headJptr, hptr *h1)
{
    char *jogo;
    linkJ obj;
    int linha,g1,g2;
    linha = (*h1) -> cont;
    jogo = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]", jogo);

    obj = encontra_J(*headJptr, jogo);
    if (obj == NULL)
        printf("%d Jogo inexistente.\n", linha);
    else
    {  
        g1 = obj->golos1;
        g2 = obj->golos2;
        printf("%d %s %s %s %d %d\n", linha,obj->nome_jogo,obj->equipa1,obj->equipa2,g1,g2);   
    }
    free(jogo);
}

void P(linkE headE,hptr *h1)
{
    char *nome_e;
    linkE aux;
    nome_e = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]", nome_e);

    aux = encontra_E(headE, nome_e);
    if(aux == NULL)
        printf("%d Equipa inexistente.\n", (*h1) -> cont);
    else
        printf("%d %s %d\n", (*h1) -> cont, aux -> nome_equipa, aux -> vitorias);

    free(nome_e);
}

void r(linkJ *headJptr,hptr *h1, linkE headE)
{
    char *jogo;
    linkJ aux;
    jogo = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]", jogo);

    aux = encontra_J(*headJptr, jogo);
    if (aux == NULL)
        printf("%d Jogo inexistente.\n", (*h1) -> cont);
    else
    {    
        retira_pontos(aux, headE, h1);
        elimina_J(headJptr, jogo);
    }

    free(jogo);
}

void s(linkJ *headJptr,hptr *h1, linkE headE)
{
    int p1, p2;
    char* jogo;
    linkJ aux;
    jogo = (char*)can_fail_malloc(sizeof(char)*MAX);
    scanf(" %[^:\n]:%d:%d", jogo, &p1, &p2);

    aux = encontra_J(*headJptr, jogo);
    if(aux == NULL)
        printf("%d Jogo inexistente.\n", (*h1) -> cont);
    else
    {
        retira_pontos(aux, headE, h1);
        vitorias(headE, p1, p2, aux -> equipa1, aux -> equipa2, h1);
        aux -> golos1 = p1;
        aux -> golos2 = p2;
    } 
    free(jogo);  
}

void l(linkJ headJ, hptr *h1)
{
    linkJ t;
    int linha,g1,g2;
    linha = (*h1) -> cont;
    if(headJ == NULL)
        return;
    else if(headJ -> next == NULL)
    {
        g1 = headJ->golos1;  
        g2 = headJ->golos2; 
        printf("%d %s %s %s %d %d\n", linha,headJ->nome_jogo,headJ->equipa1,headJ->equipa2,g1,g2);
    }
    else
    {
        for (t = headJ -> prev; t != headJ; t = t -> prev)
        {  
            g1 = t->golos1;
            g2 = t->golos2;
            printf("%d %s %s %s %d %d\n", linha,t->nome_jogo,t->equipa1,t->equipa2,g1,g2);
        }
        g1 = headJ->golos1;  
        g2 = headJ->golos2; 
        printf("%d %s %s %s %d %d\n", linha,headJ->nome_jogo,headJ->equipa1,headJ->equipa2,g1,g2); 
    }       
}

void g(linkE headE, hptr *h1)
{
    char **nomes;
    
    linkE aux;
    int i,cont;
    cont = 0;
    nomes = (char**)can_fail_malloc(MAX*sizeof(char*));
    if(headE == NULL)
    { 
        return;
    }
    for(aux = headE, i = 0; aux != NULL; aux = aux -> next)
    {
        if(aux -> vitorias == (*h1) -> max_vit)
        {
            nomes[i] = aux -> nome_equipa;
            i++;
            cont++;
        }
    }
    SelectionSort(nomes, 0, cont);
    printf("%d Melhores %d\n", (*h1) -> cont, (*h1) -> max_vit);
    for(i=0; i < cont; i++)
        printf("%d * %s\n",(*h1) -> cont, nomes[i]);    
}
