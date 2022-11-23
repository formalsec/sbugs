#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdlib.h>
#include "equipa.h"

/* Cria uma nova equipa, devolvendo um ponteiro para a mesma */
ptrEquipa criar_equipa(char *nome) {
    /* Reserva memoria para a equipa */
    ptrEquipa equipa = (ptrEquipa) can_fail_malloc(sizeof(struct equipa));

    /* Reserva memoria para a string do nome da equipa */
    equipa->nome = (char*) can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
    
    strcpy(equipa->nome, nome);
    equipa->vitorias = 0;
    return equipa;
}

/* Recebe uma equipa e liberta a memoria a ela associada */
void eliminar_equipa(ptrEquipa equipa) {
    free(equipa->nome);
    free(equipa);
}