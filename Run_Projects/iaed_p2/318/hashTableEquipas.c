#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"
/*Cria a hashtable para as equipas*/
HT_equipas *makeHTE(int HT_tam)
{
    int i;
    HT_equipas *heads;
    heads = malloc(sizeof(HT_equipas) * HT_tam);

    for (i = 0; i < HT_tam; i++)
    {
        heads[i] = NULL; /*Inicializa todas as entradas da hashtable a NULL*/
    }
    return heads;
}
/*Adiciona um elemento a Hashtable*/
void addHTE(equipa *equipa, HT_equipas *heads, int HT_tam)
{
    int i = hashU(equipa->nome, HT_tam);

    HT_equipas novo;
    novo = calloc(1, sizeof(HT_equipas) * 3);
    novo->equipa = equipa;

    if (heads[i]) /*Se a list nao estiver vazia, o elemento e adicionado ao inicio da lista*/
    {
        heads[i]->prev = novo;
        heads[i]->prev->equipa = equipa;
        heads[i]->prev->next = heads[i];
        heads[i] = heads[i]->prev;
    }
    else /*Se a lista estiver vazia, o primeiro elemento vai ser o novo elemento*/
    {
        heads[i] = novo;
    }
}
/*Remove um elemento da hashtable*/
void remHTE(char *nome, HT_equipas *heads, int HT_tam)
{
    int i = hashU(nome, HT_tam);

    HT_equipas HT_equipas;
    equipa *equipa = NULL;
    /*Ciclo que vai procurar o elemento a remover numa entrada da hashtable*/
    for (HT_equipas = heads[i]; HT_equipas; HT_equipas = HT_equipas->next)
    {
        equipa = HT_equipas->equipa;
        if (compare_strings(equipa->nome, nome) == 0) /*Se encontrar o elemento, remove e a o ciclo acaba*/
        {
            if (HT_equipas->prev == NULL)
            {
                heads[i] = HT_equipas->next;
            }
            else
            {
                HT_equipas->prev->next = HT_equipas->next;
            }
            if (HT_equipas->next != NULL)
            {
                HT_equipas->next->prev = HT_equipas->prev;
            }
            free(HT_equipas);
        }
        break; /*Acaba o ciclo pois ja removeu o elemento*/
    }
}
/*Procura um elemento na Hashtable de forma eficaz*/
equipa *searchEquipa(char *nome, HT_equipas *heads, int HT_tam)
{
    int i = hashU(nome, HT_tam);
    HT_equipas HT_equipas;
    equipa *equipa_ = NULL, *final = NULL;

    for (HT_equipas = heads[i]; HT_equipas; HT_equipas = HT_equipas->next)
    {
        equipa_ = HT_equipas->equipa;
        if (compare_strings(equipa_->nome, nome) == 0)
        {
            final = HT_equipas->equipa;
            break;
        }
    }
    return final;
}
/*Liberta a memoria da hashtable, eliminando-a*/
void freeHTE(HT_equipas *HT, int HT_tam)
{
    int i;
    HT_equipas tmp;

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