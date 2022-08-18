#include <string.h>
#include <stdlib.h>
#include "equipa.h"
#include "jogo.h"


/* Cria um novo jogo, devolvendo um ponteiro para o mesmo */
ptrJogo criar_jogo(char *nome, linkEquipa equipa1, linkEquipa equipa2, int golos1, int golos2) {
    /* Reserva memoria para o jogo */
    ptrJogo jogo = (ptrJogo) malloc(sizeof(struct jogo));

    /* Reserva memoria para a string do nome do jogo */
    jogo->nome = (char*) malloc(sizeof(char) * (strlen(nome) + 1));

    strcpy(jogo->nome, nome);
    jogo->equipa1 = equipa1->equipa;
    jogo->equipa2 = equipa2->equipa;
    jogo->golos1 = golos1;
    jogo->golos2 = golos2;
    return jogo;
}

/* Recebe um jogo e liberta a memoria a ele associada */
void eliminar_jogo(ptrJogo jogo) {
    free(jogo->nome);
    free(jogo);
}