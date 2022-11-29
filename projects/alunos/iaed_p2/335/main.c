#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#include "equipas.h"
#include "jogos.h"

#define NOME_MAX 1023 /* Numero maximo de caracteres de um nome de um jogo ou equipa */


/* Adiciona um jogo  ao sistema
 * Caso o jogo ja exista, gera um erro
 * Caso uma das equipas nao exista, gera um erro */
void a(int NL, lista_jogos *lista, link_equipa *ht_equipas, link_jogo *ht_jogos) {
    char nome_jogo[NOME_MAX+1], nome_equipa1[NOME_MAX+1], nome_equipa2[NOME_MAX+1];
    int score1, score2;
    link_equipa equipa1, equipa2;
    link_jogo novo;
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome_jogo, nome_equipa1, nome_equipa2, &score1, &score2);

    if (procura_jogo(nome_jogo, ht_jogos)) {
        printf("%d Jogo existente.\n", NL);
        return;
    }
    if (!(equipa1 = procura_equipa(nome_equipa1, ht_equipas)) ||
            !(equipa2 = procura_equipa(nome_equipa2, ht_equipas))) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    /* Atualiza as vitorias com base nos scores */
    if (score1 < score2)
        equipa2->vitorias++;
    if (score1 > score2)
        equipa1->vitorias++;

    /* aloca memoria para o jogo e adiciona-o as estruturas */
    novo = novo_jogo(nome_jogo, nome_equipa1, nome_equipa2, score1, score2, ht_equipas);
    adiciona_jogo_lista(novo, lista);
    adiciona_jogo_ht(novo, ht_jogos);
}

/* Adiciona uma equipa ao sistema
 * Caso a equipa ja exista, gera um erro */
void A(int NL, link_equipa *ht_equipas, lista_equipas *lista_equipas) {
    char nome_equipa[NOME_MAX];
    link_equipa nova;
    scanf(" %[^\n]", nome_equipa);
    if (procura_equipa(nome_equipa, ht_equipas)) {
        printf("%d Equipa existente.\n", NL);
        return;
    }
    /* aloca memoria para a equipa e adiciona-a as estruturas */
    nova = nova_equipa(nome_equipa);
    adiciona_equipa_lista(nova, lista_equipas);
    adiciona_equipa_ht(nova, ht_equipas);

}

/* Procura um jogo no sistema
 * Caso o jogo nao exista, gera um erro */
void p(int NL, link_jogo *ht_jogos) {
    char nome_jogo[NOME_MAX+1];
    link_jogo jogo;
    scanf(" %[^\n]", nome_jogo);
    if (!(jogo = procura_jogo(nome_jogo, ht_jogos))) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    printf("%d %s %s %s %d %d\n", NL, jogo->nome_jogo,
        jogo->equipa1->nome_equipa, jogo->equipa2->nome_equipa, jogo->score1, jogo->score2);
}

/* Procura uma equipa no sistema
 * Caso a equipa nao exista, gera um erro */
void P(int NL, link_equipa *ht_equipas) {
    char nome_equipa[NOME_MAX+1];
    link_equipa equipa;
    scanf(" %[^\n]", nome_equipa);
    if (!(equipa = procura_equipa(nome_equipa, ht_equipas))) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, equipa->nome_equipa, equipa->vitorias);
}

/* Lista todos os jogos pela ordem que foram introduzidos */
void l(int NL, lista_jogos *lista_jogos) {
    link_jogo t;
    for(t = lista_jogos->primeiro; t!= NULL; t = t->next_lista)
        printf("%d %s %s %s %d %d\n", NL, t->nome_jogo,
            t->equipa1->nome_equipa, t->equipa2->nome_equipa, t->score1, t->score2);
}

/* Altera o score de um jogo
 * Caso o jogo nao exista, gera um erro */
void s(int NL, link_jogo *ht_jogos) {
    char nome_jogo[NOME_MAX+1];
    int score1, score2;
    link_jogo jogo;
    scanf(" %[^:]:%d:%d", nome_jogo, &score1, &score2);
    if (!(jogo = procura_jogo(nome_jogo, ht_jogos))) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* Atualiza as vitorias com base nos scores */
    if (jogo->score1 > jogo->score2)
        jogo->equipa1->vitorias--;
    if (jogo->score1 < jogo->score2)
        jogo->equipa2->vitorias--;
    if (score1 > score2)
        jogo->equipa1->vitorias++;
    if (score1 < score2)
        jogo->equipa2->vitorias++;

    jogo->score1 = score1;
    jogo->score2 = score2;
}

/* Remove um jogo do sistema
 * Caso o jogo nao exista, gera um erro */
void r(int NL, lista_jogos *lista_jogos, link_jogo *ht_jogos) {
    char nome_jogo[NOME_MAX+1];
    link_jogo jogo;
    scanf(" %[^\n]", nome_jogo);
    if (!(jogo = procura_jogo(nome_jogo, ht_jogos))) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /* Caso alguma equipa tenha ganho o jogo, remove uma vitoria */
    if (jogo->score1 > jogo->score2)
        jogo->equipa1->vitorias--;
    if (jogo->score1 < jogo->score2)
        jogo->equipa2->vitorias--;

    remove_jogo_lista(jogo, lista_jogos);
    remove_jogo_ht(jogo, ht_jogos);

    liberta_jogo(jogo); /* Liberta a memoria associada a esse jogo */
}

/* Lista as equipas que ganharam mais jogos, por ordem lexicografica */
void g(int NL, lista_equipas *lista_equipas) {
    /* Encontra o numero maximo de vitorias (-1 caso nao hajam equipas) */
    int max_vit = encontra_max_vit(lista_equipas);
    if (max_vit >= 0)
        print_g(NL, max_vit, lista_equipas);
}

/* Funcao principal do programa que invoca as funcoes consoante o comando recebido */
int main() {
    int cmdo, NL = 0;

    /* Inicializacao das estruturas */
    link_equipa *ht_equipas = inicializa_ht_equipas();
    link_jogo *ht_jogos = inicializa_ht_jogos();
    lista_equipas *lista_equipas = inicializa_lista_equipas();
    lista_jogos *lista_jogos = inicializa_lista_jogos();

    do {
        NL++;
        switch(cmdo = getchar()) {
        case 'a': a(NL, lista_jogos, ht_equipas, ht_jogos); break;
        case 'A': A(NL, ht_equipas, lista_equipas); break;
        case 'p': p(NL, ht_jogos); break;
        case 'P': P(NL, ht_equipas); break;
        case 'l': l(NL, lista_jogos); break;
        case 's': s(NL, ht_jogos); break;
        case 'r': r(NL, lista_jogos, ht_jogos); break;
        case 'g': g(NL, lista_equipas); break;
        case 'x': break;
        }
        getchar(); /* ler o caracter '\n' */
    } while (cmdo != 'x');

    /* Liberta a memoria alocada para as estruturas na execucao do programa */
    destroi_estrut_equipas(lista_equipas, ht_equipas);
    destroi_estrut_jogos(lista_jogos, ht_jogos);
    return 0;
}
