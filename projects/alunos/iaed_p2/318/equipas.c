#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"
/*Funcao que adiciona uma nova equipa ao sistema*/
void add_equipa(int NL, list_equipas *teams, HT_equipas *HT_equipas, int HT_tam)
{
    char nome[1023];
    equipa *novo = can_fail_calloc(1, sizeof(equipa));

    scanf(" %[^\n]", nome);

    if (searchEquipa(nome, HT_equipas, HT_tam)) /*Se a equipa ja existir, nao se adiciona*/
    {
        printf("%d Equipa existente.\n", NL);
        free(novo);
    }
    else /*Caso a equipa nao exista no sistema, adiciona-se*/
    {
        novo->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(novo->nome, nome);
        novo->jogos_ganhos = 0;

        if (teams->last)
            teams->last->next = novo;
        else
            teams->head = novo;

        teams->last = novo;

        addHTE(novo, HT_equipas, HT_tam); /*Colocar a equipa na hashtable*/
    }
}
/*Procura uma equipa no sistema*/
void procura_equipa(int NL, HT_equipas *HT_equipas, int HT_tam)
{
    equipa *equipa;
    char nome[1023];

    scanf(" %[^\n]", nome);
    equipa = searchEquipa(nome, HT_equipas, HT_tam);
    if (equipa)
        printf("%d %s %d\n", NL, equipa->nome, equipa->jogos_ganhos);
    else
        printf("%d Equipa inexistente.\n", NL);
}
/* Funcao de comparacao para o quick sort*/
int cmpfunc(const void *a, const void *b)
{
    struct equipa *ia = (struct equipa *)a;
    struct equipa *ib = (struct equipa *)b;
    return strcmp(ia->nome, ib->nome);
}
/*Funcao que lista as equipas com maior numero de partidas ganhas*/
void encontra_equipas(int NL, list_equipas *teams)
{
    equipa *equipa_, *champs;
    int tam = 0, i = 0;
    int melhor = 0;
    int mem_a = 100, mem_u = 0; /*Memoria atual alocada e memoria usada respetivamente*/
    champs = can_fail_malloc(sizeof(equipa_) * mem_a);

    for (equipa_ = teams->head; equipa_; equipa_ = equipa_->next)
    {
        if (equipa_->jogos_ganhos > melhor) /*Existe uma equipa com mais partidas ganhas do que as registadas anteriormente*/
        {
            melhor = equipa_->jogos_ganhos;
            mem_u = 1;
        }
        else if (equipa_->jogos_ganhos == melhor)
        {
            mem_u += 1;
            if (mem_u >= mem_a - 1) /*Se a memoria usada estivr perto de atingir a memoria alocada, aloca-se mais memoria*/
            {
                mem_a = mem_a + 100;
                champs = can_fail_realloc(champs, sizeof(equipa_) * mem_a);
            }
        }
    }
    if (teams->head) /*Se a lista das equipas estiver vazia, o comando nao emprime nada*/
        printf("%d Melhores %d\n", NL, melhor);
    for (equipa_ = teams->head; equipa_; equipa_ = equipa_->next)
    {
        if (equipa_->jogos_ganhos == melhor)
        {
            champs[tam] = equipa_[0];
            tam++;
        }
    }
    qsort(champs, tam, sizeof(struct equipa), cmpfunc); /*Funcao quick sort para odenar por odem alfabetica as equipas*/
    for (i = 0; i < tam; i++)
    {
        printf("%d * %s\n", NL, champs[i].nome);
    }
    free(champs);
}