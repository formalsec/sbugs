#include <stdlib.h>
#include "Jogos.h"

Item_j* inicializa_jogo(char *nome, char *eq1, char *eq2, int sc1, int sc2) {
    Item_j *j;
    /* Alocacao de memoria para o jogo */
    j = malloc(sizeof(Item_j));
    /* Copia de todos os elementos necessarios */
    j->nome = malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(j->nome, nome);
    j->eq1 = eq1;
    j->eq2 = eq2;
    j->sc1 = sc1;
    j->sc2 = sc2;
    /* Retorno do Item_j, atualizado */
    return j;
}

void liberta_jogo(Item_j *j) {
    free(j->nome); /* Libertacao da memoria associada ao nome do jogo */
    free(j);
}

void altera_pontuacao(Item_j *j, int sc1, int sc2) {
    j->sc1 = sc1;
    j->sc2 = sc2;
}

char* nome_jogo(Item_j *j) {
    return j->nome;
}

char* nome_eq1(Item_j *j) {
    return j->eq1;
}

char* nome_eq2(Item_j *j) {
    return j->eq2;
}

int pontuacao_eq1(Item_j *j) {
    return j->sc1;
}

int pontuacao_eq2(Item_j *j) {
    return j->sc2;
}