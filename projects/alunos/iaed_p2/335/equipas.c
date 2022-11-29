#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"

#define HT_TAM 4111 /* Tamanho da hashtable */

/* Aloca memoria e inicializa a hashtable das equipas */
link_equipa *inicializa_ht_equipas() {
    int i;
    link_equipa *ht = can_fail_malloc(HT_TAM*sizeof(link_equipa));
    for (i=0; i < HT_TAM; i++)
        ht[i] = NULL;
    return ht;
}

/* Aloca memoria e inicializa a lista das equipas */
lista_equipas *inicializa_lista_equipas() {
    lista_equipas *lista = can_fail_malloc(sizeof(lista_equipas));
    lista->primeiro = NULL;
    return lista;
}

/* Aloca memoria para um no' de uma equipa e inicializa-o com os respetivos dados */
link_equipa nova_equipa(char *nome_equipa) {
    link_equipa novo = can_fail_malloc(sizeof(struct node_equipa));
    novo->nome_equipa = can_fail_malloc(sizeof(char)*(strlen(nome_equipa)+1));
    strcpy(novo->nome_equipa, nome_equipa);
    novo->vitorias = 0;
    novo->next_ht = NULL;
    novo->next_lista = NULL;
    return novo;
}

/* Adiciona uma equipa a lista ligada, organizando-a por ordem lexicografica */
void adiciona_equipa_lista(link_equipa equipa, lista_equipas *lista) {
    link_equipa t; /* variavel de iteracao */

    /* Insercao no inicio da lista ligada */
    if(lista->primeiro == NULL || strcmp(equipa->nome_equipa, lista->primeiro->nome_equipa) < 0) {
        equipa->next_lista = lista->primeiro;
        lista->primeiro = equipa;
        return;
    }

    t = lista->primeiro;
    /* Procura a posicao da equipa na lista, com base na ordem lexicografica */
    while(t->next_lista != NULL && strcmp(t->next_lista->nome_equipa, equipa->nome_equipa) <0)
        t = t->next_lista;

    equipa->next_lista = t->next_lista;
    t->next_lista = equipa;
}

/* Adiciona uma equipa a hashtable */
void adiciona_equipa_ht(link_equipa equipa, link_equipa *ht) {
    int i = hash(equipa->nome_equipa);
    /* Caso a linha da hashtable esteja vazia  */
    if(!ht[i]) {
        ht[i] = equipa;
        return;
    }
    /* Caso contrario, insere no inicio */
    equipa->next_ht = ht[i];
    ht[i] = equipa;
}

/* Procura uma equipa na hashtable, e retorna um ponteiro para a mesma */
link_equipa procura_equipa(char *nome_equipa, link_equipa *ht) {
    link_equipa t;
    int i = hash(nome_equipa);
    for(t = ht[i]; t != NULL; t = t->next_ht)
        if(strcmp(t->nome_equipa, nome_equipa) == 0) {
            return t;
            }
    return NULL;
}

/* Percorre a lista de equipas e encontra o numero maximo de vitorias numa equipa
 * Caso nao exista nenhuma equipa, devolve -1 */
int encontra_max_vit(lista_equipas *lista) {
    link_equipa t;
    int max_vit = -1;
    for(t = lista->primeiro; t != NULL; t = t->next_lista)
        if (t->vitorias > max_vit)
            max_vit = t->vitorias;
    return max_vit;
}

/* Percorre a lista de equipas e imprime todas as que tiverem
 * o numero maximo de vitorias */
void print_g(int NL, int max_vit, lista_equipas *lista) {
    link_equipa t;
    printf("%d Melhores %d\n", NL, max_vit);
    for(t = lista->primeiro; t!= NULL; t = t->next_lista)
        if (t->vitorias == max_vit)
            printf("%d * %s\n", NL, t->nome_equipa);
}

/* Liberta a memoria alocada para as estruturas com os dados das equipas */
void destroi_estrut_equipas(lista_equipas *lista, link_equipa *ht) {
    link_equipa aux;
    while(lista->primeiro) {
        aux = lista->primeiro->next_lista;
        free(lista->primeiro->nome_equipa);
        free(lista->primeiro);
        lista->primeiro = aux;
    }
    free(lista);
    free(ht);
}

/* Transforma o nome do jogo ou da equipa numa chave para a hashtable */
int hash(char *v) {
    int h = 0, a = 127;

    for (;*v != '\0'; v++)
        h = (a*h + *v) % HT_TAM;
    return h;
}
