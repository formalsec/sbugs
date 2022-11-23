#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao hash utilizada na formacao de hashtables dos jogos e das equipas recebe 
    uma string nome e retorna o indice da tabela hash_value respetivo a essa string.
* Esse indice resulta do resto da divisao da soma dos valores ASCII de cada caracter 
    da string dada pelo tamanho TAM_HASH da respetiva hashtable.*/
unsigned long hash(char * nome)
{
    int i, len = strlen(nome);
    unsigned long hash_value = 0;

    for(i = 0; i < len; i++)
    {
        hash_value += nome[i];
    }
    hash_value = hash_value % TAM_HASH;
    return hash_value;
}

