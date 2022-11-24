#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 1024

/* Funcao que adiciona um novo jogo a base de dados. */
void comando_a(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL) {
    char nome_jogo[DIM], equipa1[DIM], equipa2[DIM];
    int s1 = 0, s2 = 0;
    Equipas_hash um;
    Equipas_hash dois;
    jogo *x;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome_jogo, equipa1, equipa2, &s1, &s2);
    um = SearchE(e, equipa1, E);
    dois = SearchE(e, equipa2, E);
    x = Search(j, nome_jogo, M);
    /* Verifica se o nome do jogo ja existe na base de dados. */
    if (x == NULL) {
        /* Verifica se as equipas inseridas ja existem na base de dados. */
        if (um != NULL && dois != NULL) {
            x = adiciona_jogo(jogos, nome_jogo, um, dois, s1, s2);
            insert_jogo(j, x, M);
            if (s1 > s2) {
                um->jogos_ganhos++;
            } else if (s2 > s1) {
                dois->jogos_ganhos++;
            }
        } else {
            printf("%d Equipa inexistente.\n", NL);
        }
    } else {
        printf("%d Jogo existente.\n", NL);
    }
}

/* Funcao que imprime todos os jogos pela ordem em que foram inseridos. */
void comando_l(Jogos *jogos, int NL) {
    jogo *aux = jogos->head;
    /* Percorre a lista de jogos. */
    for (; aux != NULL; aux = aux->next) {
        printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome_equipa,
               aux->equipa2->nome_equipa, aux->score1, aux->score2);
    }
}
/* Funcao que imprime um certo jogo que foi inserido. */
void comando_p(Jogo_hash *j, int M, int NL) {
    jogo *x;
    char buffer[DIM];
    scanf("%[^:\n]", buffer);
    /* Verifica se o nome do jogo ja existe na base de dados. */
    x = Search(j, buffer, M);
    if (x != NULL) {
        printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1->nome_equipa, x->equipa2->nome_equipa,
               x->score1, x->score2);
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

/* Funcao que elimina um jogo da base de dados e depois liberta essa memoria. */
void comando_r(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL) {
    jogo *x;
    Equipas_hash e1;
    char buffer[DIM];
    scanf("%[^:\n]", buffer);
    x = Search(j, buffer, M);
    /* Verifica se o nome do jogo ja existe na base de dados. */
    if (x != NULL) {
        if (x->score1 > x->score2) {
            e1 = SearchE(e, x->equipa1->nome_equipa, E);
            e1->jogos_ganhos--;
        } else if (x->score1 < x->score2) {
            e1 = SearchE(e, x->equipa2->nome_equipa, E);
            e1->jogos_ganhos--;
        }
        delete_jogo(j, x, M);
        delete_jogoP(jogos, x);
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

/* Funcao que altera o resultado de um jogo que se encontra na base de dados. */
void comando_s(Jogo_hash *j, Equipas_hash *e, int M, int E, int NL) {
    jogo *x;
    Equipas_hash e1, e2;
    int s1, s2;
    char buffer[DIM];
    scanf("%[^:\n]:%d:%d", buffer, &s1, &s2);
    x = Search(j, buffer, M);
    /* Verifica se o nome do jogo ja existe na base de dados. */
    if (x != NULL) {
        e1 = SearchE(e, x->equipa1->nome_equipa, E);
        e2 = SearchE(e, x->equipa2->nome_equipa, E);
        if (x->score1 > x->score2 && s1 == s2) {
            e1->jogos_ganhos--;
        } else if (x->score1 > x->score2 && s1 < s2) {
            e1->jogos_ganhos--;
            e2->jogos_ganhos++;
        } else if (x->score1 == x->score2 && s1 < s2) {
            e2->jogos_ganhos++;
        } else if (x->score1 < x->score2 && s1 == s2) {
            e2->jogos_ganhos--;
        } else if (x->score1 < x->score2 && s1 > s2) {
            e1->jogos_ganhos++;
            e2->jogos_ganhos--;
        } else if (x->score1 == x->score2 && s1 > s2) {
            e1->jogos_ganhos++;
        }
        x->score1 = s1;
        x->score2 = s2;
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

/* Funcao que adiciona uma nova equipa ao sistema e incrementa o numero total de equipas em 1. */
int comando_A(Equipas_hash *e, int E, int total_equipas, int NL) {
    char buffer[DIM];
    scanf("%[^:\n]", buffer);
    /* Verifica se a equipa inserida ja existe na base de dados. */
    if (SearchE(e, buffer, E) == NULL) {
        insert_equipa(e, buffer, E);
        total_equipas++;
    } else {
        printf("%d Equipa existente.\n", NL);
    }
    return total_equipas;
}

/* Funcao que procura uma certa equipa na base de dados. */
void comando_P(Equipas_hash *e, int E, int NL) {
    Equipas_hash e1;
    char buffer[DIM];
    scanf("%[^:\n]", buffer);
    e1 = SearchE(e, buffer, E);
    /* Verifica se a equipa inserida ja existe na base de dados. */
    if (e1 != NULL) {
        printf("%d %s %d\n", NL, e1->nome_equipa, e1->jogos_ganhos);
    } else {
        printf("%d Equipa inexistente.\n", NL);
    }
}

/* Funcao auxiliar da funcao comando_g, que compara o nome das equipas. */
int compare(const void *a, const void *b) {
    struct str_equipa *pa = *(struct str_equipa **)a;
    struct str_equipa *pb = *(struct str_equipa **)b;
    return strcmp(pa->nome_equipa, pb->nome_equipa);
}

/* Funcao que verifica o numero maximo de vitorias e lista as equipas que ganharam esse numero de
 * jogos por ordem lexicografica. */
void comando_g(Equipas_hash *e, int E, int total_equipas, int NL) {
    struct str_equipa **array = NULL;
    struct str_equipa *aux = NULL;
    long i, k, max = 0;
    long total = 0;
    if (total_equipas > 0) {
        array = can_fail_malloc(total_equipas * sizeof(struct str_equipa));
        for (i = 0; i < E; i++) {
            aux = e[i];
            for (k = 0; aux != NULL; aux = aux->next, k++) {
                if (aux->jogos_ganhos > max) {
                    max = aux->jogos_ganhos;
                }
            }
        }
        i = 0;
        k = 0;
        while (i < E) {
            aux = e[i];
            while (aux != NULL) {
                if (aux->jogos_ganhos == max) {
                    array[k] = aux;
                    total++;
                    k++;
                }
                aux = aux->next;
            }
            i++;
        }
        qsort(array, total, sizeof(struct str_equipa *), compare);
        printf("%d Melhores %ld\n", NL, max);
        for (i = 0; i < total; i++) {
            printf("%d * %s\n", NL, array[i]->nome_equipa);
        }
        free(array);
    }
}