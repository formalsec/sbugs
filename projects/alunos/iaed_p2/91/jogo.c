#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>

#include "jogo.h"
#include "common.h"

Jogo *criar_jogo() {
    Jogo *jogo = can_fail_malloc(sizeof(Jogo));
    char input[STR_MAX];
    char input1[STR_MAX];
    char input2[STR_MAX];

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", input, input1, input2, &jogo->scores[0], &jogo->scores[1]);
    jogo->nome = copiar_texto(input);
    jogo->equipas[0] = copiar_texto(input1);
    jogo->equipas[1] = copiar_texto(input2);
    
    return jogo;
}

void free_jogo(Jogo *jogo) {
    free(jogo->nome);
    free(jogo->equipas[0]);
    free(jogo->equipas[1]);
    free(jogo);
}
