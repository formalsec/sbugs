#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_equipas.h"

/* Cria uma hash table de procura linear */
Equipa** ENova_Hash(int max)
{
    Equipa **Hash;
    int i;
    Hash = (Equipa**)can_fail_malloc(max*sizeof(Equipa*));
    for (i=0; i<max; i++)
        Hash[i] = NULL;
    return Hash;
}


/* Aumenta a memoria da hash table */
Equipa** Eexpande(Equipa** Hash, int M)
{
    int i;
    Equipa **aux = Hash;
    Hash = ENova_Hash(M);
    for (i=0; i<M/2; i++)
        if (aux[i] != NULL)
            EInsere_Hash(Hash, aux[i], M);
    free(aux);
    return Hash;
}


/* Insere um elemento na hash table */
void EInsere_Hash(Equipa** Hash, Equipa* E, int M)
{
    Chave x = chave(E);
    int i = hash(x, M);
    while (Hash[i] != NULL)
        i = (i+1) % M;
    Hash[i] = E;
}


/* Encontra um elemento, dada uma chave */
Equipa* EProcura_Hash(Equipa** Hash, Chave x, int M)
{
    int i = hash(x, M);
    while (Hash[i] != NULL) {
        if (strcmp(x, chave(Hash[i])) == 0)
            return Hash[i];
        else
            i = (i+1) % M;
    }
    return NULL;    
}


/* Liberta a memoria associada 'a hash table */
void EDestroi_Hash(Equipa** Hash, Equipas* Lst)
{
    Equipa *aux, *E = Lst->head;
    while (E != NULL) {
        aux = E->next;
        elimina_equipa(E);
        E = aux;
    }
    free(Hash);
}