#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Ficheiro que contem as funcoes auxiliares utilizadas nas implementacoes das diversas listas
    e das hashtables */

/*  Funcao criar lista de equipas
    Input: Nada
    Output: lista de equipas
    Descricao: Esta funcao cria a lista duplamente ligada das equipas
    alocando memoria e inicializando todos os indices a NULL. */
Lista_equipas *criar_lista() {
    Lista_equipas *lista = malloc(sizeof(Lista_equipas));
    lista->head = NULL;
    lista->last = NULL;
    return lista;
}

/*  Funcao libertar lista de equipas 
    Input: Lista de equipas
    Output: Nada
    Descricao: Esta funcao liberta toda a memoria alocada para
    a lista duplamente ligada. */  
void liberta_lista_equipas(Lista_equipas *lista_equipa) {
 /*   Equipa *a = lista_equipa->head; */
    while(lista_equipa->head != NULL) {
        Equipa *a = lista_equipa->head->next;
        free(lista_equipa->head->nome);
        free(lista_equipa->head);
        lista_equipa->head = a;
    }
    free(lista_equipa);
}

/*  Funcao hash
    Input: key
    Output: value
    Descricao: Esta funcao recebe uma chave e calcula o slot adequado
    para a mesma na hashtable. */
unsigned int hash(char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    value = value % TAMANHO;
    return value;
}

/*  Funcao criar hashtable equipas
    Input: Nada
    Output: hashtable equipas
    Descricao: Esta funcao cria a hashtable das equipas, alocando
    memoria para toda a hashtable e iniciando os seus slots a NULL. */
hashtable_equipas *criar_equipas() {
    int i;
    hashtable_equipas *hashtable = malloc(sizeof(hashtable_equipas) * 1);
    hashtable->entradas = malloc(sizeof(Equipa) * TAMANHO);

    for (i = 0; i < TAMANHO; ++i) {
        hashtable->entradas[i] = NULL;
    }
    return hashtable;
}

/*  Funcao liberta hashtable equipas
    Input: hashtable equipas
    Output: Nada
    Descricao: Esta funcao liberta toda a memoria alocada para
    a hashtable equipas. */
void libertar_equipas(hashtable_equipas *hashtable) {
    int i;
    Equipa *atual;
    Equipa *next;
    for (i=0; i < TAMANHO; i++) {
        atual = hashtable->entradas[i];
        while (atual != NULL) {
            next = atual->next;
            free(atual->nome);
            free(atual);
            atual = next;
        }
    }
    free(hashtable->entradas);
    free(hashtable); 
}

/*  Funcao aloca para hashtable das equipas
    Input: key
    Output: equipa
    Descricao: Esta funcao aloca espaco correspondente a estrutura de
    uma equipa no slot calculado pela mesma. */
Equipa *ht_equipas_aloca(char *key) {
    Equipa *p_equipa = malloc(sizeof(Equipa));

    p_equipa->nome = malloc((strlen(key) + 1));
    p_equipa->next = NULL;
    p_equipa->prev = NULL;

    strcpy(p_equipa->nome, key);
    p_equipa->vitorias = 0;
    return p_equipa;
}

/*  Funcao insere equipa na hashtable
    Input: hashtable equipas e key
    Output: Nada
    Descricao: Esta funcao insere uma equipa no slot da hashtable
    correspondente. */
void ht_equipas_insere(hashtable_equipas *hashtable, char *key) {
    Equipa *prev; 
    unsigned int slot = hash(key);

    Equipa *equipa = hashtable->entradas[slot];

    if (equipa == NULL) {
        hashtable->entradas[slot] = ht_equipas_aloca(key);
        return;
    }
    while (equipa != NULL) {
        if (strcmp(equipa->nome, key) == 0) {
            equipa = ht_equipas_aloca(key);
            return;
        } 
        prev = equipa;
        equipa = prev->next;
    }
    prev->next = ht_equipas_aloca(key);
}

/* Funcao verifica equipa
    Input: hashtable equipas e key
    Output: equipa
    Descricao: Esta funcao verifica se o key dado corresponde a uma
    equipa presente na hashtable. */
Equipa *ht_equipas_verifica(hashtable_equipas *hashtable, char *key) {
    unsigned int slot = hash(key);
    Equipa *equipa = hashtable->entradas[slot];
    
    if (equipa == NULL) {
        return NULL;
    }
    while (equipa != NULL) {
        if (strcmp(equipa->nome, key) == 0) {
            return equipa;
        }
        equipa = equipa->next;
    }
    return NULL;
}

/*  Funcao criar lista de jogos
    Input: Nada
    Output: lista de jogos
    Descricao: Esta funcao cria a lista duplamente ligada dos jogos
    alocando memoria e inicializando todos os indices a NULL. */
Lista_jogos *criar_lista_j() {
    Lista_jogos *lista = malloc(sizeof(Lista_jogos) * 1);
    lista->head = NULL;
    lista->last = NULL;
    return lista;
}

/*  Funcao libertar lista de jogos 
    Input: Lista de jogos
    Output: Nada
    Descricao: Esta funcao liberta toda a memoria alocada para
    a lista duplamente ligada. */ 
void liberta_lista(Lista_jogos *lista_jogo) {
    Jogo *proximo;

    while (lista_jogo->head != NULL) {
        proximo = lista_jogo->head->next;
        free(lista_jogo->head->nome); 
        free(lista_jogo->head->equipa2);
        free(lista_jogo->head);
        lista_jogo->head = proximo;
    }
    free(lista_jogo);
    return;
}

/*  Funcao criar hashtable jogos
    Input: Nada
    Output: hashtable jogos
    Descricao: Esta funcao cria a hashtable dos jogos, alocando
    memoria para toda a hashtable e iniciando os seus slots a NULL. */
hashtable_jogos *criar_jogos() {
    int i;
    hashtable_jogos *hashtable_j = malloc(sizeof(hashtable_jogos));
    hashtable_j->entradas = malloc(sizeof(Jogo) * TAMANHO);

    for (i = 0; i < TAMANHO; ++i) {
        hashtable_j->entradas[i] = NULL;
    }
    return hashtable_j;
}

/*  Funcao apaga jogo da hash
    Input: hashtable jogos e key
    Output: Nada
    Descricao: Esta funcao recebe uma key e apga o jogo da hashtable
    correspondente a essa key. */
void ht_jogos_apaga(hashtable_jogos *ht_jogos, char *key) {
    Jogo *prev;
    int id = 0;
    unsigned int b = hash(key);
    Jogo *jogo = ht_jogos->entradas[b];

    if (jogo == NULL) {
        return;
    }
    while (jogo != NULL) {
        if (strcmp(jogo->nome, key) == 0) {
            if (jogo->next == NULL && id == 0) {
                ht_jogos->entradas[b] = NULL;
            }
            if (jogo->next == NULL && id != 0) {
                prev->next = NULL;
            } 
            if (jogo->next != NULL && id != 0) {
                prev->next = jogo->next;
            }
            free(jogo->nome);
            free(jogo->equipa1->nome);
            free(jogo->equipa1);
            free(jogo->equipa2->nome);
            free(jogo->equipa2);
            free(jogo); 
            return;
        }
        prev = jogo;
        jogo = prev->next;
        ++id;
    }
    free(ht_jogos);
}

/* Funcao verifica jogo
    Input: hashtable jogo e key
    Output: jogo
    Descricao: Esta funcao verifica se o key dado corresponde a um
    jogo presente na hashtable. */
Jogo *ht_jogos_verifica(hashtable_jogos *hashtable_j, char *key) {
    unsigned int slot = hash(key);
    Jogo *jogo = hashtable_j->entradas[slot];

    if (jogo == NULL) {
        return NULL;
    }
    while (jogo != NULL) {
        if (strcmp(jogo->nome, key) == 0) {
            return jogo;
        }
        jogo = jogo->next;
    }
    return NULL;
}

/*  Funcao liberta hashtable jogos
    Input: hashtable jogos
    Output: Nada
    Descricao: Esta funcao liberta toda a memoria alocada para
    a hashtable jogos. */
/*
void libertar_jogos(hashtable_jogos *ht_jogos) {
    int i; 
    for (i = 0; i < TAMANHO; i++) {
        while(ht_jogos[i].entradas) {
            Jogo *a = ht_jogos[i].entradas;
            free(a);
            ht_jogos[i].entradas = a;
        }
    }
}
*/ 

/* Funcao compara
    Input: 2 ponteiros
    Output: inteiro
    Descricao: Esta funcao compara duas strings. */
int compara(const void *ptr1, const void *ptr2) {
    char *s1 = *(char**)ptr1;
    char *s2 = *(char**)ptr2;
    return strcmp(s1, s2);
}