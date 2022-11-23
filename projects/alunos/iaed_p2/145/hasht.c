#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

int hash(Key n, int M) {

    int h, a = 31415, b = 27183;
    
    for (h = 0; *n != '\0'; n++, a = a * b % (M - 1))
        h = (a * h + *n) % M;
    
    return h;

}


Hashtable cria_hash(int max) {
    
    int i;
    Item * endereco;
    Hashtable hasht;
    
    hasht = (Hashtable) can_fail_malloc (sizeof(struct hasht));
    
    hasht -> M = 2 * max;
    hasht -> N = 0;
    
    endereco = (Item *) can_fail_malloc (2 * max * sizeof(Item));
    hasht -> endereco = endereco;
    
    for (i = 0; i < 2 * max; i++) /* Inicia todas as posicoes com um valor nulo */
        endereco[i] = NULL;

    return hasht;

}


void insere_hash(Item item, Hashtable hasht) {

    Item * endereco = hasht -> endereco;
    int M = hasht -> M, i = hash(key(item), M);
    
    while (endereco[i] != NULL) /* Percorre tabela ate encontrar uma posicao livre */
        i = (i + 1) % M;
    
    endereco[i] = item;

    hasht -> N++;

}


Item procura_hash(Key n, Hashtable hasht) {

    Item * endereco = hasht -> endereco;
    int M = hasht -> M, i = hash(n, M);

    while (endereco[i] != NULL) /* Percorre posicoes a partir de i ate encontrar o Item */
        if (eq(n, key(endereco[i])))
            return endereco[i];
        else
            i = (i+1) % M;

    return NULL; /* Devolve NULL se o elemento nao estiver na tabela */

}


Item apaga_hash(Key n, Hashtable hasht) {

    int M = hasht -> M, i = hash(n, M), j; 
    Item * endereco = hasht -> endereco, jogo, aux;
    
    while (endereco[i] != NULL) /* Encontra posicao do Item na tabela */
        if (eq(n, key(endereco[i]))) 
            break;
        else 
            i = (i+1) % M;

    jogo = endereco[i]; /* Guarda Item a devolver */

    if (jogo == NULL) /* Verifica se o Item esta na tabela */
        return jogo;
    
    /* Remove o Item */
    endereco[i] = NULL;
    hasht -> N--;
    
    /* Recoloca itens seguintes */
    for (j = (i + 1) % M; endereco[j] != NULL; j = (j + 1) % M, hasht -> N--) {
        aux = endereco[j];
        endereco[j] = NULL;
        insere_hash(aux, hasht);
    }

    return jogo;

}


void liberta_hash(Hashtable hasht) {

    Item * endereco = hasht -> endereco;
    int M = hasht -> M, i;

    for (i = 0; i < M; i++)
        if (endereco[i] != NULL) 
            free_item(endereco[i]);

    free(endereco);
    free(hasht);

}
