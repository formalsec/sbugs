#include "equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que inicializa e devolve as equipas. */
Equipas *init_equipas() {
    Equipas *equipas = malloc(sizeof(Equipas));
    equipas->head = NULL;
    return equipas;
}

/* Funcao que liberta toda a memoria associada as equipas. */
void destroy_equipas(Equipas *equipas) {
    node_equipas *e = NULL;

    while (equipas->head) {
        e = equipas->head->next;
        free(equipas->head->nome);
        free(equipas->head);
        equipas->head = e;
    }
    free(equipas);
}

/* Funcao que recebe um nome e devolve uma equipa. */
node_equipas *cria_equipa(char *nome) {
    node_equipas *e = malloc(sizeof(node_equipas));
    e->next = NULL;
    e->nome = malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(e->nome, nome);
    e->jogos_ganhos = 0;
    return e;
}

/* Funcao que adiciona no inicio uma equipa as equipas. */
Equipas *push_equipa(Equipas *equipas, node_equipas *equipa) {
    equipa->next = equipas->head;
    equipas->head = equipa;
    return equipas;
}

/* Funcao que atualiza os jogos ganhos de uma equipa quando ganha. */
void equipa_vencedora(node_equipas *equipa) {
    equipa->jogos_ganhos++;
}

/* Funcao que diminui os jogos ganhos de uma equipa quando um jogo e removido,
 * se essa equipa nao tiver jogos ganhos nao faz nada. */
void equipa_diminui_jogos_ganhos(node_equipas *equipa) {
    if (equipa->jogos_ganhos == 0)
        return;
    equipa->jogos_ganhos--;
}

/* Funcao que recebe todas as equipas e devolve um vetor com as equipas com maior numero de jogos
 * ganhos, recebe tambem um ponteiro para guardar o numero de equipas nesse vetor. */
node_equipas **melhores_equipas(Equipas *equipas, long *numero_melhores) {
    node_equipas **melhores = NULL; /* Vetor para guardar as melhores equipas. */
    node_equipas *equipa = NULL;
    long max_jogos_ganhos = 0; /* Numero maximo de jogos ganhos. */
    long i = 0;

    /* Calcula o maximo de jogos ganhos e o numero de equipas com esse numero de jogos ganhos. */
    for (equipa = equipas->head; equipa; equipa = equipa->next) {
        if (equipa->jogos_ganhos > max_jogos_ganhos) {
            max_jogos_ganhos = equipa->jogos_ganhos;
            i = 1;

        } else if (equipa->jogos_ganhos == max_jogos_ganhos)
            i++;
    }

    melhores = calloc(i, sizeof(node_equipas *));
    *numero_melhores = i; /* Guarda o tamanho do vetor no ponteiro recebido. */
    i = 0;

    /* Guarda no vetor as melhores equipas. */
    for (equipa = equipas->head; equipa; equipa = equipa->next)
        if (equipa->jogos_ganhos == max_jogos_ganhos)
            melhores[i++] = equipa;

    return melhores;
}

/* Funcao que liberta toda a memoria associada ao vetor das melhores equipas. */
void destroy_melhores(node_equipas **melhores) {
    free(melhores);
}
