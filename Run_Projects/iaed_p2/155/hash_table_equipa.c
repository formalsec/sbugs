#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table_equipa.h"
#include "comandos.h"

/* Funcao para inserir uma equipa na hash table */
equipa * init_hash_table_equipa(equipa * hash[HASH_SIZE])
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
    {
        hash[i] = NULL;
    }
    return *hash;
}

/* Funcao para inserir uma equipa na hash table */
equipa * hash_table_equipa_insert(equipa *e, equipa *hash[HASH_SIZE])
{
    int indice; /*posicao da equipa dada na hash table*/
    indice = hash_function(e->nome_equipa); 
    e->next = hash[indice];
    hash[indice] = e; /*coloca a nova equipa como cabeca do encadeamento*/
    return *hash;
}

/* Funcao que retorna a equipa na hash table com o nome dado se existir */
equipa * hash_table_equipa_lookup(char *nome, equipa *hash[HASH_SIZE])
{
    int indice;
    equipa *aux;
    indice = hash_function(nome); /*posicao do jogo dado na hash table*/
    for(aux = hash[indice]; aux!=NULL; aux=aux->next)
    {
        if (strcmp(aux->nome_equipa, nome) == 0) /*se o nome do jogo for igual*/
        {
            return aux;
        }
    }
    return NULL; /* Este valor eh NULL se o jogo nao estiver na table */ 
} 

/* Funcao que apaga uma equipa da hash table com o nome dado */ 
equipa * hash_table_equipa_delete(char *nome, equipa *hash[HASH_SIZE])
{
    int indice;
    equipa *aux, *aux_ant;
    indice = hash_function(nome); /*posicao da equipa dada na hash table*/
    aux = hash[indice];
    aux_ant = NULL;
    while (aux != NULL && strcmp(aux->nome_equipa, nome) != 0)
    {
        aux_ant = aux;
        aux = aux->next;
    }
    if (aux == NULL)
    {
        return NULL;
    }
    if (aux_ant == NULL)
    {
        hash[indice] = aux->next;
    }
    else
    {
        aux_ant->next = aux->next;
    }
    return *hash;
}
