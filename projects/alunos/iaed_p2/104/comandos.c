#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"
#include "jogo.h"
#include "listas.h"
#include "hashtables.h"
#include "comandos.h"

/* Comprimento maximo do nome das equipas e dos jogos */
#define MAX 1024

/* Adiciona um novo jogo */
void novo_jogo(lstJogos lista, hashJogos hash_jogos, hashEquipas hash_equipas, int nl) {
    char nome[MAX], equipa1[MAX], equipa2[MAX];
    int golos1, golos2;
    ptrJogo jogo;
    linkJogo aux;
    linkEquipa e1, e2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &golos1, &golos2);

    aux = procurar_jogo_hash(hash_jogos, nome);
    e1 = procurar_equipa_hash(hash_equipas, equipa1);
    e2 = procurar_equipa_hash(hash_equipas, equipa2);

    /* Se aux != NULL, entao o jogo ja existe */
    if (aux != NULL)
        printf("%d Jogo existente.\n", nl);
    /* Se e1 ou e2 == NULL, entao a equipa nao existe */
    else if (e1 == NULL || e2 == NULL)
        printf("%d Equipa inexistente.\n", nl);
    else {
        jogo = criar_jogo(nome, e1, e2, golos1, golos2);
        adicionar_jogo_lst(lista, jogo);
        adicionar_jogo_hash(hash_jogos, jogo);
        if (jogo->golos1 > jogo->golos2)
            e1->equipa->vitorias++;
        else if (jogo->golos1 < jogo->golos2)
            e2->equipa->vitorias++;
    }
}

/* Adiciona uma nova equipa */
void nova_equipa(lstEquipas lista, hashEquipas hash_equipas, int nl) {
    char nome[MAX];
    ptrEquipa equipa;
    linkEquipa aux;

    scanf(" %[^:\n]", nome);

    aux = procurar_equipa_hash(hash_equipas, nome);

    /* Se aux != NULL, entao a equipa ja existe */
    if (aux != NULL)
        printf("%d Equipa existente.\n", nl);
    else {
        equipa = criar_equipa(nome);
        adicionar_equipa_lst(lista, equipa);
        adicionar_equipa_hash(hash_equipas, equipa);
    }
}

/* Lista todos os jogos pela ordem em que foram introduzidos */
void listar_jogos(lstJogos lista, int nl) {
    linkJogo aux;
    ptrJogo jogo;
    ptrEquipa e1, e2;

    /* Percorre cada jogo da lista e imprime-o */
    for (aux = lista->primeiro; aux != NULL; aux = aux->prox) {
        jogo = aux->jogo;
        e1 = jogo->equipa1;
        e2 = jogo->equipa2;
        printf("%d %s %s %s %d %d\n", nl, jogo->nome, e1->nome, e2->nome, jogo->golos1, jogo->golos2);
    }
}

/* Procura o jogo com o nome dado */
void procurar_jogo(hashJogos hash_jogos, int nl) {
    char nome[MAX];
    linkJogo aux;
    ptrJogo jogo;
    ptrEquipa e1, e2;

    scanf(" %[^:\n]", nome);

    aux = procurar_jogo_hash(hash_jogos, nome);

    /* Se aux == NULL, entao o jogo nao existe */
    if (aux == NULL)
        printf("%d Jogo inexistente.\n", nl);
    else {
        jogo = aux->jogo;
        e1 = jogo->equipa1;
        e2 = jogo->equipa2;
        printf("%d %s %s %s %d %d\n", nl, jogo->nome, e1->nome, e2->nome, jogo->golos1, jogo->golos2);
    }
}

/* Procura a equipa com o nome dado */
void procurar_equipa(hashEquipas hash_equipas, int nl) {
    char nome[MAX];
    linkEquipa aux;
    ptrEquipa equipa;

    scanf(" %[^:\n]", nome);

    aux = procurar_equipa_hash(hash_equipas, nome);

    /* Se aux == NULL, a equipa nao existe */
    if (aux == NULL)
        printf("%d Equipa inexistente.\n", nl);
    else {
        equipa = aux->equipa;
        printf("%d %s %d\n", nl, equipa->nome, equipa->vitorias);
    }
}

/* Apaga o jogo com o nome dado */
void apagar_jogo(lstJogos lista, hashJogos hash_jogos, int nl) {
    char nome[MAX];
    linkJogo aux1, aux2;
    ptrJogo jogo;
    ptrEquipa e1, e2;

    scanf(" %[^:\n]", nome);

    aux1 = procurar_jogo_hash(hash_jogos, nome);

    /* Se aux == NULL, entao o jogo nao existe */
    if (aux1 == NULL)
        printf("%d Jogo inexistente.\n", nl);
    else {
        jogo = aux1->jogo;
        e1 = jogo->equipa1;
        e2 = jogo->equipa2;
        if (jogo->golos1 > jogo->golos2)
            e1->vitorias--;
        else if (jogo->golos1 < jogo->golos2)
            e2->vitorias--;
        aux2 = procurar_jogo_lst(lista, nome);
        /* Remove o jogo da hashtable */
        remover_jogo_hash(hash_jogos, aux1);
        /* Remove o jogo da lista */
        remover_jogo_lst(lista, aux2);
        /* Liberta a memoria associada ao jogo */
        eliminar_jogo(jogo);
    }
}

/* Altera a pontuacao do jogo com o nome dado */
void alterar_pontuacao(hashJogos hash_jogos, int nl) {
    linkJogo aux;
    ptrJogo jogo;
    ptrEquipa e1, e2;
    char nome[MAX];
    int novo_golos1, novo_golos2;

    scanf(" %[^:\n]:%d:%d", nome, &novo_golos1, &novo_golos2);

    aux = procurar_jogo_hash(hash_jogos, nome);

    /* Se aux == NULL, entao o jogo nao existe */
    if (aux == NULL)
        printf("%d Jogo inexistente.\n", nl);
    else {
        jogo = aux->jogo;
        e1 = jogo->equipa1;
        e2 = jogo->equipa2;
        /* Caso 1: antes era empate e agora uma das equipas vence */
        if (jogo->golos1 == jogo->golos2) {
            if (novo_golos1 > novo_golos2)
                e1->vitorias++;
            else if (novo_golos1 < novo_golos2)
                e2->vitorias++;
        }
        /* Caso 2: antes uma das equipas vencia e agora ha empate */
        else if (novo_golos1 == novo_golos2) {
            if (jogo->golos1 > jogo->golos2)
                e1->vitorias--;
            else if (jogo->golos1 < jogo->golos2)
                e2->vitorias--;
        }
        /* Caso 3: antes vencia a equipa 1 e agora vence a equipa 2 */
        else if (jogo->golos1 > jogo->golos2 && novo_golos1 < novo_golos2) {
            e1->vitorias--;
            e2->vitorias++;
        }
        /* Caso 4: antes vencia a equipa 2 e agora vence a equipa 1 */
        else if (jogo->golos1 < jogo->golos2 && novo_golos1 > novo_golos2) {
            e1->vitorias++;
            e2->vitorias--;
        }

        /* Atualiza a pontuacao do jogo */
        jogo->golos1 = novo_golos1;
        jogo->golos2 = novo_golos2;
    }
}

/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica */
void mais_vitorias(lstEquipas lista, int nl) {
    /* Lista onde sao guardadas as equipas com mais vitorias */
    lstEquipas lista_mais_vit = criar_lst_equipas();
    linkEquipa aux;
    int max_vit = 0, i, comp;
    char **nomes_mais_vit;

    /* Percorre cada equipa da lista */
    for (aux = lista->primeiro; aux != NULL; aux = aux->prox) {
        /* Se o numero de vitorias da equipa for igual ao maior numero de vitorias atual,
           a equipa e' adicionada 'a lista */
        if (aux->equipa->vitorias == max_vit)
            adicionar_equipa_lst(lista_mais_vit, aux->equipa);
        /* Se o numero de vitorias da equipa for maior que o maior numero de vitorias atual,
           este numero e' atualizado, a lista e' limpa e a equipa e' adicionada */
        else if (aux->equipa->vitorias > max_vit) {
            max_vit = aux->equipa->vitorias;
            limpar_lst_equipas(lista_mais_vit);
            adicionar_equipa_lst(lista_mais_vit, aux->equipa);
        }
    }

    comp = comp_lst_equipas(lista_mais_vit);

    /* Caso nao exista nenhuma equipa, nao imprime nada */
    if (comp > 0) {
        /* Reserva memoria para um vetor de ponteiros para strings */
        nomes_mais_vit = (char**) can_fail_malloc(comp * sizeof(char*));
        aux = lista_mais_vit->primeiro;

        /* Percorre cada equipa da lista e adiciona o seu nome ao vetor */
        for (i = 0; i < comp; i++) {
            nomes_mais_vit[i] = aux->equipa->nome;
            aux = aux->prox;
        }

        /* Ordena o vetor por ordem lexicografica */
        qsort(nomes_mais_vit, comp, sizeof(char*), comparar_str);

        printf("%d Melhores %d\n", nl, max_vit);

        /* Percorre o vetor ordenado e imprime o nome das equipas com mais vitorias */
        for (i = 0; i < comp; i++)
            printf("%d * %s\n", nl, nomes_mais_vit[i]);

        /* Liberta a memoria associada ao vetor */
        free(nomes_mais_vit);
    }

    /* Liberta a memoria associada 'a lista */
    apagar_lst_equipas(lista_mais_vit);
}

/* Liberta toda a memoria associada 'as listas, 'as hashtables, 'as equipas e aos jogos */
void terminar_prog(lstJogos lista_jogos, lstEquipas lista_equipas, hashJogos hash_jogos, hashEquipas hash_equipas) {
    apagar_hash_jogos(hash_jogos);
    apagar_hash_equipas(hash_equipas);
    apagar_lst_mais_jogos(lista_jogos);
    apagar_lst_mais_equipas(lista_equipas);
}

/* Funcao de comparacao passada como argumento do qsort(), utilizada para comparar strings */
int comparar_str(const void *str1, const void *str2) {
    char **s1 = (char **) str1;
    char **s2 = (char **) str2;
    return strcmp(*s1, *s2);
}