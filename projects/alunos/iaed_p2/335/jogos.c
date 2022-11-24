#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"

#define HT_TAM 4111 /* Tamanho da hashtable */

/* Aloca memoria e inicializa a hashtable dos jogos */
link_jogo *inicializa_ht_jogos() {
    int i;
    link_jogo *ht = can_fail_malloc(HT_TAM*sizeof(link_jogo));
    for (i=0; i < HT_TAM; i++)
        ht[i] = NULL;
    return ht;
}

/* Aloca memoria e inicializa a lista dos jogos */
lista_jogos *inicializa_lista_jogos() {
    lista_jogos *lista = can_fail_malloc(sizeof(lista_jogos));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}

/* Aloca memoria para um no' de um jogo e inicializa-o com os respetivos dados */
link_jogo novo_jogo(char *nome_jogo, char *equipa1, char *equipa2,
                    int score1, int score2, link_equipa *ht_equipas) {
    link_jogo novo = can_fail_malloc(sizeof(struct node_jogo));
    novo->nome_jogo = can_fail_malloc(sizeof(char)*(strlen(nome_jogo)+1));
    strcpy(novo->nome_jogo, nome_jogo);
    novo->equipa1 = procura_equipa(equipa1, ht_equipas);
    novo->equipa2 = procura_equipa(equipa2, ht_equipas);
    novo->score1 = score1;
    novo->score2 = score2;
    novo->next_ht = NULL;
    novo->next_lista = NULL;
    return novo;
}

/* Adiciona um jogo no fim da lista ligada */
void adiciona_jogo_lista(link_jogo jogo, lista_jogos *lista) {
    /* Caso a lista esteja vazia */
    if (!lista->primeiro) {
        lista->primeiro = jogo;
        lista->ultimo = jogo;
        return;
    }

    lista->ultimo->next_lista = jogo;
    lista->ultimo = jogo;
}

/* Adiciona um jogo no inicio da hashtable */
void adiciona_jogo_ht(link_jogo jogo, link_jogo *ht) {
    int i = hash(jogo->nome_jogo);
    /* Caso a linha da hashtable esteja vazia */
    if(!ht[i]) {
        ht[i] = jogo;
        return;
    }
    jogo->next_ht = ht[i];
    ht[i] = jogo;
}

/* Procura um jogo na hashtable, e retorna um ponteiro para o mesmo */
link_jogo procura_jogo(char *nome_jogo, link_jogo *ht) {
    link_jogo t;
    int i = hash(nome_jogo);
    for(t = ht[i]; t != NULL; t = t->next_ht)
        if(strcmp(t->nome_jogo, nome_jogo) == 0)
            return t;
    return NULL;
}

/* Remove um jogo da lista, alterando os ponteiros associados ao no' desse jogo */
void remove_jogo_lista(link_jogo jogo, lista_jogos *lista) {
    link_jogo t, prev;
    for (t = lista->primeiro, prev = NULL; t != NULL; prev = t, t =t->next_lista) {
        if(strcmp(t->nome_jogo, jogo->nome_jogo) == 0) {
            if(t == lista->primeiro)  /* Caso seja o primeiro */
                lista->primeiro = t->next_lista;
            else                            /* Caso contrario */
                prev->next_lista = t->next_lista;
            if(t->next_lista == NULL)       /* Caso seja o ultimo */
                lista->ultimo = prev;
            break;
        }
    }
}

/* Remove um jogo da hashtable, alterando os ponteiros associados ao no' desse jogo */
void remove_jogo_ht(link_jogo jogo, link_jogo *ht) {
    link_jogo t, prev;
    int i = hash(jogo->nome_jogo);
    for (t = ht[i], prev = NULL; t != NULL; prev = t, t =t->next_ht) {
        if(strcmp(t->nome_jogo, jogo->nome_jogo) == 0) {
            if(t == ht[i])    /* Caso seja o primeiro */
                ht[i] = t->next_ht;
            else                    /* Caso contrario */
                prev->next_ht = t->next_ht;
            break;
        }
    }
}

/* Liberta memoria associada ao no' de um jogo */
void liberta_jogo(link_jogo jogo) {
    free(jogo->nome_jogo);
    free(jogo);
}

/* Liberta a memoria alocada para as estruturas com os dados dos jogos */
void destroi_estrut_jogos(lista_jogos *lista, link_jogo *ht) {
    link_jogo aux;
    while(lista->primeiro) {
        aux = lista->primeiro->next_lista;
        liberta_jogo(lista->primeiro);
        lista->primeiro = aux;
    }
    free(lista);
    free(ht);
}
