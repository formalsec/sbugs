#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Equipas.h"

int hash(char *nome, int m) /* Funcao que identifica em que index da hastable e que o jogo esta e retorna o index desejado*/
{
    int h, a = 31415, b = 27183;
    for (h = 0; strcmp(nome, "\0") != 0; nome++, a = a * b % (m - 1))
        h = (a * h + *nome) % m;
    return h;
}

pEquipa NEW(char *nome) /* Funcao auxiliar de insertBeginList */
{
    pEquipa x = can_fail_malloc(sizeof(struct Equipa)); /* Aloca a memoria necessaria para equipas e coloca o nome e inicializa as vitorias a 0*/
    x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(x->nome, nome);
    x->vitorias = 0;
    x->next = NULL;
    return x;
}

pEquipa insertBeginList(pEquipa head, char *nome) /* Funcao auxiliar de STdeleteJ */
{
    pEquipa x = NEW(nome); /* cria a equipa e coloca no x uma equipa */
    x->next = head;
    return x;
}

pEquipa removeEquipaList(pEquipa head, char *nome) /* Funcao auxiliar de STdelete */
{
    pEquipa t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) /* Percorre a "gaveta" da hastable que a equipa esta e quando encontra a equipa remove-a*/
    {
        if (strcmp(t->nome, nome) == 0)
        {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;
            freeEquipa(t);
            break;
        }
    }
    return head;
}

pEquipa searchList(pEquipa head, char *nome) /* Funcao auxiliar de STsearch*/
{
    pEquipa t;
    for (t = head; t != NULL; t = t->next) /* Percorre a "gaveta" da hastable que a equipa esta e quando encontra a equipa retorna-o*/
    {
        if (strcmp(t->nome, nome) == 0)
        {
            return t;
        }
    }
    return NULL;
}

pEquipa *STinit(int m) /* Funcao que inicializa a hashtable dos jogos*/
{
    pEquipa *heads;
    heads = can_fail_calloc(m, sizeof(pEquipa)); /*Aloca a memoria necessaria*/
    return heads;
}

void STinsert(pEquipa *heads, char *nome, int m) /* Funcao que insere uma equipa ao inicio da lista de um determinado index da hashtable*/
{
    int i = hash(nome, m); /*Encontra o index da hashtable onde se destina essa equipa e insere-a */
    heads[i] = insertBeginList(heads[i], nome);
}

void STdelete(pEquipa *heads, char *nome, int m) /* Funcao que remove uma equipa da lista de um determinado index da hashtable */
{
    int i = hash(nome, m); /*Encontra o index da hashtable onde se encontra essa equipa e remove-a */
    heads[i] = removeEquipaList(heads[i], nome);
}

pEquipa STsearch(pEquipa *heads, char *nome, int m) /* Funcao que procura se uma determinada equipa faz parte da hashtable */
{
    int i = hash(nome, m); /*Encontra o index da hashtable onde se encontra essa equipa e retorna-a */
    return searchList(heads[i], nome);
}

void freeEquipa(pEquipa a) /* Funcao que da free a um determinada equipa */
{
    free(a->nome);
    free(a);
}

void printEquipa(pEquipa a, int nl) /* Funcao que da print a uma equipa e as suas vitorias */
{
    printf("%d %s %u\n", nl, a->nome, a->vitorias);
}
