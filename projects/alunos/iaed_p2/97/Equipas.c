#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include "Equipas.h"

Item_eq* inicializa_equipa(char *nome) {
    Item_eq *e;
    /* Alocacao de memoria para a equipa */
    e = can_fail_malloc(sizeof(Item_eq));
    /* Copia do nome para a estrutura */
    e->nome = can_fail_malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(e->nome, nome);
    /* Colocar o numero de jogos ganhos a zero */
    e->ganhos = 0;
    /* Retorno do Item_j, atualizado */
    return e;
}

void liberta_equipa(Item_eq *e) {
    free(e->nome); /* Libertacao da memoria associada ao nome da equipa */
    free(e);
}

void aumenta_pontuacao(Item_eq *e) {
    e->ganhos++;
}

void diminui_pontuacao(Item_eq *e) {
    e->ganhos--;
}

char* nome_equipa(Item_eq *e) {
    return e->nome;
}

int ganhos_equipa(Item_eq *e) {
    return e->ganhos;
}