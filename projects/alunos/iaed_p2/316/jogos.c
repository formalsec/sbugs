#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que inicializa e devolve os jogos. */
Jogos *init_jogos() {
    Jogos *jogos = can_fail_malloc(sizeof(Jogos));
    jogos->head = jogos->last = NULL;
    return jogos;
}

/* Funcao que liberta a memoria associada a um jogo. */
void free_jogo(node_jogos *jogo) {
    free(jogo->nome);
    free(jogo);
}

/* Funcao que liberta toda a memoria associada aos jogos. */
void destroy_jogos(Jogos *jogos) {
    node_jogos *jogo = NULL;

    while (jogos->head) {
        jogo = jogos->head->next;
        free_jogo(jogos->head);
        jogos->head = jogo;
    }
    free(jogos);
}

/* Funcao que recebe um nome, 2 equipas e os respetivos scores e
 * devolve um jogo com o respetivo nome. */
node_jogos *cria_jogo(char *n, node_equipas *e1, node_equipas *e2, int s1, int s2) {
    node_jogos *jogo = can_fail_malloc(sizeof(node_jogos));

    jogo->nome = can_fail_malloc((strlen(n) + 1) * sizeof(char));
    strcpy(jogo->nome, n);
    jogo->equipa1 = e1;
    jogo->equipa2 = e2;
    jogo->score1 = s1;
    jogo->score2 = s2;
    jogo->next = jogo->previous = NULL;

    if (s1 > s2)
        equipa_vencedora(e1);

    else if (s2 > s1)
        equipa_vencedora(e2);

    return jogo;
}

/* Funcao que adiciona no fim um jogo aos jogos. */
void add_jogo(Jogos *jogos, node_jogos *jogo) {
    jogo->previous = jogos->last;
    if (jogos->last) {
        jogos->last->next = jogo;
        jogos->last = jogo;

    } else {
        jogos->head = jogo;
        jogos->last = jogo;
    }
}

/* Funcao que remove um jogo dos jogos. */
void remove_node_jogos(Jogos *jogos, node_jogos *jogo) {
    if (jogo->previous == NULL)
        jogos->head = jogo->next;

    else
        jogo->previous->next = jogo->next;

    if (jogo->next == NULL)
        jogos->last = jogo->previous;

    else
        jogo->next->previous = jogo->previous;

    free_jogo(jogo);
}

/* Funcao que recebe um jogo e 2 scores e altera os scores do jogo para os novos scores. */
void atualiza_scores_jogo(node_jogos *jogo, int s1, int s2) {
    if (jogo->score1 > jogo->score2 && s1 <= s2)
        equipa_diminui_jogos_ganhos(jogo->equipa1);

    else if (jogo->score1 < jogo->score2 && s1 >= s2)
        equipa_diminui_jogos_ganhos(jogo->equipa2);

    if (s1 > s2 && jogo->score1 <= jogo->score2)
        equipa_vencedora(jogo->equipa1);

    else if (s1 < s2 && jogo->score1 >= jogo->score2)
        equipa_vencedora(jogo->equipa2);

    jogo->score1 = s1;
    jogo->score2 = s2;
}
