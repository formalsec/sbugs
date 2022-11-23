#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_jogos.h"

/* Cria uma hash table de procura linear */
Jogo** JNova_Hash(int max)
{
    Jogo **Hash;
    int i;
    Hash = (Jogo**)can_fail_malloc(max*sizeof(Jogo*));
    for (i=0; i<max; i++)
        Hash[i] = NULL;
    return Hash;
}


/* Aumenta a memoria da hash table */
Jogo** Jexpande(Jogo** Hash, int M)
{
    int i;
    Jogo **aux = Hash;
    Hash = JNova_Hash(M);
    for (i=0; i<M/2; i++)
        if (aux[i] != NULL)
            JInsere_Hash(Hash, aux[i], M);
    free(aux);
    return Hash;
}


/* Insere um elemento na hash table */
void JInsere_Hash(Jogo** Hash, Jogo* J, int M)
{
    Chave x = chave(J);
    int i = hash(x, M);
    while (Hash[i] != NULL)
        i = (i+1) % M;
    Hash[i] = J;
}


/* Encontra um elemento, dada uma chave */
Jogo* JProcura_Hash(Jogo** Hash, Chave x, int M)
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


/* Remove um elemento da hash table e da memoria e devolve N */
int JRemove_Hash(Jogo** Hash, Chave x, int M, int N)
{
    int j, i = hash(x, M);
    Jogo *v;
    while (Hash[i] != NULL) {
        if (strcmp(x, chave(Hash[i])) == 0)
            break;
        else
            i = (i+1) % M;
    }
    if (Hash[i] != NULL) {
        Hash[i] = NULL;
        N--;
        for (j=(i+1)%M; Hash[j]!=NULL; j=(j+1)%M, N--) {
            v = Hash[j];
            Hash[j] = NULL;
            JInsere_Hash(Hash, v, M);
        }
    }
    return N;
}


/* Liberta a memoria associada 'a hash table */
void JDestroi_Hash(Jogo** Hash, Jogos* Lst)
{
    Jogo *aux, *J = Lst->head;
    while (J != NULL) {
        aux = J->next;
        elimina_jogo(J);
        J = aux;
    }
    free(Hash);
}