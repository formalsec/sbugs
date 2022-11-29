#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao de dispersao para strings com base nos slides.
 * Recalcula a base em cada iteracao e
 * evita anomalias com chaves altamente regulares. */
long hash(char *string, int tamanho) {
    long i, a = 31415, b = 27183;
    for (i = 0; *string != '\0'; string++, a = a * b % (tamanho - 1)) {
        i = (a * i + *string) % tamanho;
    }
    return i;
}

/* Funcao que recebe 2 tamanhos e inicializa e devolve a tabela de dispersao para os jogos
 * e para as equipas, relativamente aos tamanhos. */
hashTable *HTinit(int tamanho_jogos, int tamanho_equipas) {
    hashTable *ht = can_fail_malloc(sizeof(hashTable));

    ht->tamanho_jogos = 2 * tamanho_jogos;
    ht->numero_jogos = 0;
    ht->elementos_jogos = can_fail_calloc(ht->tamanho_jogos, sizeof(node_jogos *));

    ht->tamanho_equipas = 2 * tamanho_equipas;
    ht->numero_equipas = 0;
    ht->elementos_equipas = can_fail_calloc(ht->tamanho_equipas, sizeof(node_equipas *));

    return ht;
}

/* Funcao que liberta toda a memoria associada a hashtable. */
void HTdestroy(hashTable *ht) {
    free(ht->elementos_jogos);
    free(ht->elementos_equipas);
    free(ht);
}

/* Funcao que aumenta o tamanho da tabela de dispersao dos jogos para o dobro. */
void expand_jogos(hashTable *ht) {
    hashTable *new_ht = HTinit(ht->tamanho_jogos * 2, 1);
    long i;

    for (i = 0; i < ht->tamanho_jogos; i++)
        if (ht->elementos_jogos[i])
            HTinsert_jogo(new_ht, ht->elementos_jogos[i]);

    free(ht->elementos_jogos);
    ht->elementos_jogos = new_ht->elementos_jogos;
    ht->tamanho_jogos = new_ht->tamanho_jogos;
    free(new_ht->elementos_equipas);
    free(new_ht);
}

/* Funcao que adiciona um jogo na tabela de dispersao dos jogos. */
void HTinsert_jogo(hashTable *ht, node_jogos *jogo) {
    long i = hash(jogo->nome, ht->tamanho_jogos);

    while (ht->elementos_jogos[i] != NULL)
        i = (i + 1) % ht->tamanho_jogos;

    ht->elementos_jogos[i] = jogo;
    if (ht->numero_jogos++ > ht->tamanho_jogos / 2)
        expand_jogos(ht);
}

/* Funcao que remove um jogo da tabela de dispersao dos jogos. */
void HTdelete_jogo(hashTable *ht, char *nome) {
    node_jogos *aux = NULL;
    long j, i = hash(nome, ht->tamanho_jogos);

    while (ht->elementos_jogos[i] != NULL)
        if (!strcmp(nome, ht->elementos_jogos[i]->nome))
            break;
        else
            i = (i + 1) % ht->tamanho_jogos;

    if (ht->elementos_jogos[i] == NULL)
        return;

    ht->elementos_jogos[i] = NULL;
    ht->numero_jogos--;

    for (j = (i + 1) % ht->tamanho_jogos; ht->elementos_jogos[j] != NULL;
         j = (j + 1) % ht->tamanho_jogos, ht->numero_jogos--) {
        aux = ht->elementos_jogos[j];
        ht->elementos_jogos[j] = NULL;
        HTinsert_jogo(ht, aux);
    }
}

/* Funcao que dado um nome devolve o jogo com esse nome. */
node_jogos *HTsearch_jogo(hashTable *ht, char *nome) {
    long i = hash(nome, ht->tamanho_jogos);

    while (ht->elementos_jogos[i] != NULL) {
        if (!strcmp(nome, ht->elementos_jogos[i]->nome))
            return ht->elementos_jogos[i];
        else
            i = (i + 1) % ht->tamanho_jogos;
    }
    return NULL;
}

/* Funcao que aumenta o tamanho da tabela de dispersao das equipas para o dobro. */
void expand_equipas(hashTable *ht) {
    hashTable *new_ht = HTinit(1, ht->tamanho_equipas * 2);
    long i;

    for (i = 0; i < ht->tamanho_equipas; i++)
        if (ht->elementos_equipas[i])
            HTinsert_equipa(new_ht, ht->elementos_equipas[i]);

    free(ht->elementos_equipas);
    ht->elementos_equipas = new_ht->elementos_equipas;
    ht->tamanho_equipas = new_ht->tamanho_equipas;
    free(new_ht->elementos_jogos);
    free(new_ht);
}

/* Funcao que adiciona uma equipa na tabela de dispersao das equipas. */
void HTinsert_equipa(hashTable *ht, node_equipas *equipa) {
    long i = hash(equipa->nome, ht->tamanho_equipas);

    while (ht->elementos_equipas[i] != NULL)
        i = (i + 1) % ht->tamanho_equipas;

    ht->elementos_equipas[i] = equipa;
    if (ht->numero_equipas++ > ht->tamanho_equipas / 2)
        expand_equipas(ht);
}

/* Funcao que dado um nome devolve a equipa com esse nome. */
node_equipas *HTsearch_equipa(hashTable *ht, char *nome) {
    long i = hash(nome, ht->tamanho_equipas);

    while (ht->elementos_equipas[i] != NULL) {
        if (!strcmp(nome, ht->elementos_equipas[i]->nome))
            return ht->elementos_equipas[i];
        else
            i = (i + 1) % ht->tamanho_equipas;
    }
    return NULL;
}
