#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "HashtableEquipa.h"

/* Cria a hashtable, alocando a memoria necessaria. */
Hashtable_Equipa* ht_criar_equipa(int max) {
    Hashtable_Equipa* ht = can_fail_malloc(sizeof(Hashtable_Equipa));
    int i;
    ht->entradas = can_fail_malloc(sizeof(Lista_Ligada_Equipa) * max);
    ht->cap = max;
    ht->qtd = 0;

    /* Inicializa todos os espacos da hashtable com uma nova lista ligada. */
    for (i = 0; i < max; ++i)
        ht->entradas[i] = ll_criar_equipa();

    return ht;
}

/* Calcula o index que sera armazenada a equipa. */
int ht_hash_equipa(Hashtable_Equipa* ht, char* chave) {
    unsigned long int valor = 0;
    int i, tam = strlen(chave);

    /* Aumenta o fator de aleatoriedade. */
    for (i = 0; i < tam; ++i)
        valor = valor * 37 + chave[i];

    return valor % ht->cap;
}

/* Insere a equipa na hashtable. */
void ht_inserir_equipa(Hashtable_Equipa* ht, Equipa* equipa, char* chave) {
    /* A funcao hash eh utilizada para encontrar o index do elemento na hashtable. */
    int i = ht_hash_equipa(ht, chave);

    Lista_Ligada_Equipa* lista = ht->entradas[i];
    ll_inserir_equipa(lista, equipa, chave);

    ht->qtd++;
}

/* Verifica a exitencia de uma equipa, dada uma chave. */
Equipa* ht_pesquisar_equipa(Hashtable_Equipa* ht, char* chave) {
    /* A funcao hash eh utilizada para encontrar o index do elemento na hashtable. */
    int index_hash = ht_hash_equipa(ht, chave);
    No_Equipa* n = ht->entradas[index_hash]->inicio;
    
    /* Enquanto o no nao for nulo e o elemento nao for encontrado, percorre os nos. */
    while (n) {
        if (strcmp(n->chave, chave) == 0)
            return n->equipa;
        n = n->prox;
    }

    return NULL;
}

/* Liberta todas as instancias e memoria alocada da hashtable. */
void free_hash_equipa(Hashtable_Equipa* ht) {
    int i;
    No_Equipa* tmp, * aux;

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

