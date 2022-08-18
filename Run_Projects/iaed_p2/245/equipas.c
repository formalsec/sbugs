#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include "auxiliares.h"     /* Header file que contem os defines relativos as funcoes auxiliares */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

/**************************************************************/
/*  Ficheiro que contem os comandos relativos as equipas.     */
/*                                                            */
/*  Comandos:                                                 */
/*                                                            */
/*  A -> A nome ; Adiciona uma nova equipa.                   */
/*  P -> P nome ; Procura uma equipa dado um nome.            */
/*  g -> g      ; Encontra as equipas que ganharam mais jogos */
/*                 ordenando por ordem alfabetica.            */
/**************************************************************/

/*  Funcao A
    Input: A nome
    Output: Nada (excepto erro)
    Descricao: Adiciona uma nova equipa. */
Lista_equipas *A(int NL, char s[], hashtable_equipas *ht_equipa, Lista_equipas *lista_equipa) {
    Equipa *novo; 
    Equipa *a = ht_equipas_verifica(ht_equipa, s);
    if (a != NULL) {
        printf("%d Equipa existente.\n", NL);
        return lista_equipa;
    }
    novo = malloc(sizeof(Equipa));
    novo->nome = malloc(strlen(s) + 1);
    strcpy(novo->nome, s);
    novo->vitorias = 0;

    novo->next = NULL;
    novo->prev = lista_equipa->last; 

    if (lista_equipa->head == NULL) {
        lista_equipa->head = novo;
    }
    else {
        lista_equipa->last->next = novo;
    } 
    lista_equipa->last = novo; 
    ht_equipas_insere(ht_equipa, s);   
    return lista_equipa;
} 

/*  Funcao P
    Input: P nome
    Output: NL nome numero-de-jogos-ganhos
    Descricao: Procura uma equipa dado um nome. */
void P(int NL, char s[], hashtable_equipas *ht_equipa) {
    Equipa *a = ht_equipas_verifica(ht_equipa, s);
    if (a == NULL) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, a->nome, a->vitorias);
    return;
}

/*  Funcao g
    Input: g
    Output: NL Melhores numero-de-jogos-ganhos
            NL * nome-equipa1
            NL * nome-equipa2
            NL * nome-equipa3
            ...
    Descricao:  Encontra as equipas que ganharam mais jogos e lista por ordem
    alfabetica. */
void g(int NL, Lista_equipas *lista_equipa, hashtable_equipas *ht_equipa) { 
    char **e;
    int c = 0; 
    int melhor = 0, i, j = 0;
    Equipa *a;
    Equipa *percorre = lista_equipa->head;
    Equipa *descobre = lista_equipa->head;

    e = malloc(sizeof(char*) * 10003);
    if (lista_equipa->head == NULL) {
        return;
    }
    while (percorre != NULL) {
        
        a = ht_equipas_verifica(ht_equipa, percorre->nome);
        c += 1;
        if (a->vitorias >= melhor) {
            melhor = a->vitorias;
        }
        percorre = percorre->next;
    }
    while (descobre != NULL) {
        a = ht_equipas_verifica(ht_equipa, descobre->nome);
        if (melhor == a->vitorias) {
            e[j++] = a->nome;
        }
        descobre = descobre->next;
    }
    qsort(e, j, sizeof(char*), compara);
    printf("%d Melhores %d\n", NL, melhor);
    for (i = 0; i < j; i++) {
        printf("%d * %s\n", NL, e[i]);
    }
    free(e);
    return;
}