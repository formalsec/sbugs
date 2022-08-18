#include <stdlib.h>
#include <string.h>
#include "HashtableJogo.h"

/* Cria a hashtable, alocando a memoria necessaria. */
Hashtable_Jogo* ht_criar_jogo(int max) {
    Hashtable_Jogo* ht = malloc(sizeof(Hashtable_Jogo));
    int i;
    ht->entradas = malloc(sizeof(Lista_Ligada_Jogo) * max);
    ht->cap = max;
    ht->qtd = 0;

    /* Inicializa todos os espacos da hashtable com uma nova lista ligada. */
    for (i = 0; i < max; ++i)
        ht->entradas[i] = ll_criar_jogo();

    return ht;
}

/* Calcula o index que sera armazenado o jogo. */
int ht_hash_jogo(Hashtable_Jogo* ht, char* chave) {
    unsigned long int valor = 0;
    int i, tam = strlen(chave);

    /* Aumenta o fator de aleatoriedade. */
    for (i = 0; i < tam; ++i)
        valor = valor * 37 + chave[i];

    return valor % ht->cap;
}

/* Insere o jogo na hashtable. */
void ht_inserir_jogo(Hashtable_Jogo* ht, Jogo* jogo, char* chave) {
    /* A funcao hash eh utilizada para encontrar o index do elemento na hashtable. */
    int i = ht_hash_jogo(ht, chave);

    Lista_Ligada_Jogo* lista = ht->entradas[i];
    ll_inserir_jogo(lista, jogo, chave);

    ht->qtd++;
}

/* Deleta um jogo da hashtable. */
void ht_deletar_jogo(Hashtable_Jogo* ht, char* chave) {
    /* A funcao hash eh utilizada para encontrar o index do elemento na hashtable. */
    int index_hash = ht_hash_jogo(ht, chave);

    Lista_Ligada_Jogo* lista = ht->entradas[index_hash];
    No_Jogo* tmp = lista->inicio;;
    
    while (tmp) {
        if (strcmp(tmp->chave, chave) == 0) {
            ll_deletar_no(lista, tmp);
            free(tmp->chave);
            free(tmp);
            ht->qtd--;
            return;
        }
        tmp = tmp->prox;
    }
}

/* Verifica a exitencia de um jogo, dada uma chave. */
Jogo* ht_pesquisar_jogo(Hashtable_Jogo* ht, char* chave) {
    /* A funcao hash eh utilizada para encontrar o index do elemento na hashtable. */
    int index_hash = ht_hash_jogo(ht, chave);
    No_Jogo* n = ht->entradas[index_hash]->inicio;

    /* Enquanto o no nao for nulo e o elemento nao for encontrado, percorre a lista. */
    while (n) {
        if (strcmp(n->chave, chave) == 0)
            return n->jogo;
        n = n->prox;
    }

    return NULL;
}

/* Liberta todas as instancias e memoria alocada da hashtable. */
void free_hash_jogo(Hashtable_Jogo* ht) {
    int i;
    No_Jogo* tmp, * aux;
    /* Para cada index da hashtable, libertamos a memoria alocada. */
    for (i = 0; i < ht->cap; i++) {
        for (tmp = ht->entradas[i]->inicio; tmp != NULL; tmp = aux) {
            aux = tmp->prox;
            free(tmp->chave);
            free(tmp);
        }
        free(ht->entradas[i]);
    }

    free(ht->entradas);
    free(ht);
}

