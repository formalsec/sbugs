#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"
/*Cria a hashtable para os jogos*/
HT_jogos *makeHTJ(int HT_tam)
{
    int i;
    HT_jogos *heads;
    heads = can_fail_malloc(sizeof(HT_jogos) * HT_tam);

    for (i = 0; i < HT_tam; i++) /*Inicializa todas as entradas da hashtable a NULL*/
    {
        heads[i] = NULL;
    }
    return heads;
}
/*Adiciona um elemento a Hashtable*/
void addHTJ(jogo *jogo, HT_jogos *heads, int HT_tam)
{
    int i = hashU(jogo->nome, HT_tam);

    HT_jogos novo;
    novo = can_fail_calloc(1, sizeof(HT_jogos) * 3);
    novo->p = jogo;

    if (heads[i]) /*Se a list nao estiver vazia, o elemento e adicionado ao inicio da lista*/
    {
        heads[i]->prev = novo;
        heads[i]->prev->p = jogo;
        heads[i]->prev->next = heads[i];
        heads[i] = heads[i]->prev;
    }
    else /*Se a lista estiver vazia, o primeiro elemento vai ser o novo elemento*/
    {
        heads[i] = novo;
    }
}
/*Remove um elemento da hashtable*/
void remHTJ(char *nome, HT_jogos *heads, int HT_tam)
{
    int i = hashU(nome, HT_tam);

    HT_jogos HT_jogos;
    jogo *jogo = NULL;
    /*Ciclo que vai procurar o elemento a remover numa entrada da hashtable*/
    for (HT_jogos = heads[i]; HT_jogos; HT_jogos = HT_jogos->next)
    {
        jogo = HT_jogos->p;
        if (strcmp(jogo->nome, nome) == 0) /*Se encontrar o elemento, remove e a o ciclo acaba*/
        {
            if (HT_jogos->prev == NULL)
            {
                heads[i] = HT_jogos->next;
            }
            else
            {
                HT_jogos->prev->next = HT_jogos->next;
            }
            if (HT_jogos->next != NULL)
            {
                HT_jogos->next->prev = HT_jogos->prev;
            }
            free(HT_jogos);
            break;
        }
    }
}
/*Procura um elemento na Hashtable de forma eficaz*/
jogo *searchJogo(char *nome, HT_jogos *heads, int HT_tam)
{
    int i = hashU(nome, HT_tam);
    HT_jogos HT_jogos;
    jogo *jogo_ = NULL, *final = NULL;
    HT_jogos = heads[i];
    while (HT_jogos)
    {
        jogo_ = HT_jogos->p;
        if (compare_strings(jogo_->nome, nome) == 0)
        {
            final = HT_jogos->p;
            break;
        }
        HT_jogos = HT_jogos->next;
    }
    return final;
}
/*Liberta a memoria da hashtable, eliminando-a*/
void freeHTJ(HT_jogos *HT, int HT_tam)
{
    int i;
    HT_jogos tmp;

    for (i = 0; i < HT_tam; i++) /*Ciclo que percorre os elementos da hashtable, libertanto a memoria usada*/
    {
        while (HT[i] != NULL)
        {
            tmp = HT[i]->next;
            free(HT[i]);
            HT[i] = tmp;
        }
    }
    free(HT);
}