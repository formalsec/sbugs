#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table_jogo.h"
#include "comandos.h"

/* Inicializacao das duas hash tables colocando todos os ponteiros a NULL */
jogo * init_hash_table_jogo(jogo *hash[HASH_SIZE])
{
    int i;
    for (i = 0; i < HASH_SIZE; i++) /*ciclo para percorrer as hash tables */
    {
        hash[i] = NULL;
    }
    return *hash;
}

/* Funcao para inserir um jogo na hash table */
jogo * hash_table_jogo_insert(jogo *j, jogo *hash[HASH_SIZE])
{
    int indice; /*posicao do jogo dado na hash table*/
    indice = hash_function(j->nome_jogo);
    j->next = hash[indice];
    hash[indice] = j; /*coloca o novo jogo como cabeca do encadeamento*/
    return *hash;
}

/* Funcao que retorna o jogo na hash table com o nome dado se existir */
jogo * hash_table_jogo_lookup(char *nome, jogo *hash[HASH_SIZE])
{
    int indice;
    jogo *aux;
    indice = hash_function(nome); /*posicao do jogo dado na hash table*/
    for(aux = hash[indice]; aux!=NULL; aux=aux->next)
    {
        if (strcmp(aux->nome_jogo, nome) == 0) /*se o nome do jogo for igual*/
        {
            return aux;
        }
    }
    return NULL; /*este valor e NULL se o jogo nao estiver na table */
} 

/* Funcao que apaga o jogo da hash table com o nome dado */ 
jogo * hash_table_jogo_delete(char *nome, jogo *hash[HASH_SIZE])
{
    int indice;
    jogo *aux, *aux_ant;
    indice = hash_function(nome); /*posicao do jogo dado na hash table*/
    aux = hash[indice];
    aux_ant = NULL;
    while (aux != NULL && strcmp(aux->nome_jogo, nome) != 0) 
    {
        aux_ant = aux;
        aux = aux->next;
    }
    if (aux == NULL) /*se a posicao nao estiver ocupada*/
    {
        return NULL;
    }
    if (aux_ant == NULL) /*se o jogo estiver em hash[indice]*/
    {
        hash[indice] = aux->next; /*o segundo elemento passa a primeiro*/
    }
    else
    {
        aux_ant->next = aux->next; /*o jogo e retirado do encadeamento*/
    }
    return *hash; /*retorna a hash table sem o jogo*/
}
