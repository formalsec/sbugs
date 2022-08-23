#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"

/* Funcao de hashing */
int hash(Chave value, int M)
{
    unsigned int h, a = 31415, b = 27183;

    for (h=0; *value!='\0'; value++, a=a*b % (M-1))
        h = (a*h + *value) % M;
    return h;
}


/* Funcao que cria uma lista de jogos */
Jogos* init_jogos()
{
    Jogos* Lst = malloc(sizeof(Jogos));
    Lst->head = NULL;
    Lst->last = NULL;
    return Lst;
}


/* Funcao que cria uma lista de equipas */
Equipas* init_equipas()
{
    Equipas* Lst = malloc(sizeof(Equipas));
    Lst->head = NULL;
    Lst->last = NULL;
    return Lst; 
}


/* Funcao que cria um jogo */
Jogo* novo_jogo()
{
    Jogo* J = malloc(sizeof(Jogo));
    J->nome = NULL;
    J->next = NULL;
    J->prev = NULL;
    J->score[0] = 0;
    J->score[1] = 0;
    J->Equipas[0] = NULL;
    J->Equipas[1] = NULL;
    return J;
}


/* Funcao que cria uma equipa */
Equipa* nova_equipa()
{
    Equipa* E = malloc(sizeof(Equipa));
    E->nome = NULL;
    E->next = NULL;
    E->jganhos = 0;
    return E;
}


/* Funcao que remove um jogo da lista de jogos e da memoria */
Jogos* remove_jogo(Jogos *Lst, char *text)
{
    Jogo *aux;
    for (aux=Lst->head; aux!=NULL; aux=aux->next)
        if (strcmp(aux->nome, text) == 0) {
            if (aux == Lst->head)
                Lst->head = aux->next;
            else if (aux == Lst->last)
                Lst->last = aux->prev;
            if (aux->prev != NULL)
                aux->prev->next = aux->next;
            if (aux->next != NULL)
                aux->next->prev = aux->prev;
            elimina_jogo(aux);
            break;
        }
    return Lst;
}


/* Funcao que encontra o maior numero de vitorias */
unsigned int encontra_max(Equipas *Lst)
{
    Equipa *aux;
    unsigned int Max = 0;
    for (aux=Lst->head; aux!=NULL; aux=aux->next)
        if (aux->jganhos > Max)
            Max = aux->jganhos;
    return Max;
}


/* Funcao que encontra as equipas com o maior numero de vitorias
e coloca os seus nomes em Nomes */
int encontra_melhores(Equipas*Lst,unsigned int Max,char**Nomes)
{
    int i = 0;
    Equipa *aux;
    for (aux=Lst->head; aux!=NULL; aux=aux->next)
        if (aux->jganhos == Max)
            Nomes[i++] = aux->nome;
    return i;
}


/* Funcao que ordena dois nomes lexicograficamente */
int compare(const void *a, const void *b)
{
    const char *A = *(const char **)a; 
    const char *B = *(const char **)b;
    return strcmp(A, B);
}


/* Funcao que liberta a memoria associada a um jogo */
void elimina_jogo(Jogo *J)
{
    free(J->nome);
    free(J->Equipas[0]);
    free(J->Equipas[1]);
    free(J);
}


/* Funcao que liberta a memoria associada a uma equipa */
void elimina_equipa(Equipa *E)
{
    free(E->nome);
    free(E);
}