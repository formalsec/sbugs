#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geral.h"
#include "structs.h"

#define MAX_NOME 1024

/*-------------------------INICIALIZACOES-----------------------------*/
/*funcao que inicializa a lista de jogos*/
listagem list() 
{
    listagem lst;
    lst = malloc(sizeof(struct lst));
    lst->head = NULL;
    lst->tail = NULL;
    return lst;
}

/*funcoes de iniciacao de ambas as hash tables*/
table_eq Init_eq(int m)
{
    int i;
    table_eq table;
    table = (table_eq)malloc(sizeof(struct hash_eq));
    table->M = m;
    table->heads = malloc(table->M*sizeof(struct node_eq));
    for (i = 0; i < table->M; i++) 
    {
        table->heads[i] = NULL;
    }
    return table;
}

table_jogos Init_jogo(int m)
{
    int i;
    table_jogos table;
    table = (table_jogos)malloc(sizeof(struct hash_jogos));
    table->M = m;
    table->heads = malloc(table->M*sizeof(struct node_jogo));
    for (i = 0; i < table->M; i++) 
    {
        table->heads[i] = NULL;
    }
    return table;
}

/*funcoes de procura de ambas as hash tables*/
int hash_eq(char nome[],table_eq table)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *nome++))
        hash = ((hash << 5) + hash) + c; 

    return hash % table->M;
}

int hash_jogos(char nome[],table_jogos table)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *nome++))
        hash = ((hash << 5) + hash) + c; 
    return hash % table->M;
}

/*----------------------------COMUNS--------------------------------*/

/*funcoes de procura na hash table de equipas*/
Equipas SearchEquipa(char nome[],table_eq table)
{
    int i = hash_eq(nome,table);
    Equipas equipa = NULL;
    /*caso nao exista essa equipa*/
    if (table->heads[i] == NULL) {
        return NULL;
    }
    equipa = search_equipa(table->heads[i],nome);
    if (equipa == NULL) {
        return NULL;
    }
    return equipa;
}

Equipas search_equipa(Node_eq head, char nome[])
{
    Node_eq temp=head;
    while(temp != NULL)
    {
        if (strcmp(temp->equipa->nome,nome) == 0) {
            return temp->equipa;
        }
        temp = temp->next;
    }
    return NULL;
}

/*funcoes de procura na hash table dos jogos*/
pJogo SearchJogo(char nome[],table_jogos table) 
{
    int i = hash_jogos(nome, table);
    pJogo match = NULL;
    /*caso nao exista esse jogo*/
    if (table->heads[i] == NULL) {
        return NULL;
    }
    match = search_jogo(table->heads[i],nome);
    if (match == NULL) {
        return NULL;
    }
    return match;
}

pJogo search_jogo(Node_jogos head, char nome[])
{
    Node_jogos temp=head;
    while(temp != NULL)
    {
        if (strcmp(temp->match->nome,nome) == 0) {
            return temp->match;
        }
        temp = temp->next;
    }
    return NULL;
}

/*-------------------------------FREES---------------------------*/

/*funcao que liberta a hash de equipas*/
void liberta_hash_eq(table_eq tab_eq)
{
    int i;
    Node_eq temp;
    for (i = 0; i < tab_eq->M; i++) {
        temp = tab_eq->heads[i];
        while(tab_eq->heads[i] != NULL) {
            temp = tab_eq->heads[i];
            tab_eq->heads[i] = tab_eq->heads[i]->next;
            liberta_no_eq(temp);
        }
        free(tab_eq->heads[i]);
    }
    free(tab_eq->heads);
    free(tab_eq);

}

/*liberta memoria alocada de cada no*/
void liberta_no_eq(Node_eq node_eq)
{
    free(node_eq->equipa->nome);
    free(node_eq->equipa);
    free(node_eq);
}

/*funcao que liberta a hash de jogos*/
void liberta_hash_j(table_jogos tab_j)
{
    int i;
    Node_jogos temp;
    for (i = 0; i < tab_j->M; i++) {
        temp = tab_j->heads[i];
        while(tab_j->heads[i] != NULL) {
            temp = tab_j->heads[i];
            tab_j->heads[i] = tab_j->heads[i]->next;
            liberta_no_j(temp);
        }
        free(tab_j->heads[i]);
    }
    free(tab_j->heads);
    free(tab_j);

}

/*liberta memoria alocada de cada no*/
void liberta_no_j(Node_jogos node_j)
{
    free(node_j->match->nome);
    free(node_j->match->equipa1);
    free(node_j->match->equipa2);
    free(node_j->match->winner);
    free(node_j->match);
    free(node_j);
}