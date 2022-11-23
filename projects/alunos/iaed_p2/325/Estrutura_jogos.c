#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Estrutura_jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que inicializa a lista dos jogos. */
Jogos *init_Jogos() {
    Jogos *estrutura_jogos = can_fail_malloc(sizeof(Jogos));
    estrutura_jogos->head = NULL;
    estrutura_jogos->last = NULL;
    return estrutura_jogos;
}

/* Funcao que adiciona um novo logo a lista de jogos alocando memoria. */
jogo *adiciona_jogo(Jogos *j, char *n, Equipas_hash e1, Equipas_hash e2, int s1, int s2) {
    jogo *new = can_fail_malloc(sizeof(struct stru_jogo));
    new->nome = can_fail_malloc(sizeof(char) * (strlen(n) + 1));
    strcpy(new->nome, n);
    new->equipa1 = e1;
    new->equipa2 = e2;
    new->score1 = s1;
    new->score2 = s2;
    new->next = NULL;
    new->previous = j->last;
    /* Se ja existir algum elemento na lista. */
    if (j->last != NULL) {
        j->last->next = new;
    } else {
        j->head = new;
    }
    j->last = new;
    return new;
}

/* Funcao que elimina um certo jogo da lista de jogos, libertando a memoria deste. */
void delete_jogoP(Jogos *l, jogo *n) {
    if (n->previous == NULL) {
        l->head = n->next;
    } else {
        n->previous->next = n->next;
    }
    if (n->next == NULL) {
        l->last = n->previous;
    } else {
        n->next->previous = n->previous;
    }
    free(n->nome);
    free(n);
}

/* Funcao que elimina todos os jogos da lista de jogos libertando toda a memoria que esta continha.
 */
void free_Jogos(Jogos *j) {
    jogo *fj = j->head;
    jogo *aux = NULL;
    while (fj != NULL) {
        aux = fj->next;
        free(fj->nome);
        free(fj);
        fj = aux;
    }
    free(j);
}