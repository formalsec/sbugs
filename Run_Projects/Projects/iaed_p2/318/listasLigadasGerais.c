#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"

/*--------------------------------------------------------------------*/

/*Funcao que cria a lista ligada dos jogos*/
list_jogos *mk_list()
{
    list_jogos *l = malloc(sizeof(list_jogos));
    l->head = l->last = NULL;
    return l;
}
/*Funcao que cria a lista ligada das equipas*/
list_equipas *mk_list_eq()
{
    list_equipas *l = malloc(sizeof(list_equipas));
    l->head = l->last = NULL;
    return l;
}
/*Funcao que liberta memoria alocada de um jogo*/
void free_jogo(jogo *n)
{
    free(n->nome);
    free(n->e1);
    free(n->e2);
    free(n);
}
/*Funcao que liberta a memoria alocada de uma equipa*/
void free_equipa(equipa *n)
{
    free(n->nome);
    free(n);
}
/*Funcao que remove um jogo da lista ligada*/
void rm_jogo(list_jogos *jogos, jogo *n)
{
    if (n->prev)
    {
        n->prev->next = n->next;
    }
    else
    {
        jogos->head = n->next;
    }
    if (n->next)
    {
        n->next->prev = n->prev;
    }
    else
    {
        jogos->last = n->prev;
    }
    free_jogo(n);
}
/*Funcao que liberta a memoria alocada da lista ligada dos jogos*/
void free_list_jogos(list_jogos *jogos)
{
    while (jogos->head)
    {
        jogo *tmp = jogos->head->next;
        free_jogo(jogos->head);
        jogos->head = tmp;
    }
    free(jogos);
}
/*Funcao que liberta a memoria alocada da lista ligada das equipas*/
void free_list_equipas(list_equipas *teams)
{
    while (teams->head)
    {
        equipa *tmp = teams->head->next;
        free_equipa(teams->head);
        teams->head = tmp;
    }
    free(teams);
}