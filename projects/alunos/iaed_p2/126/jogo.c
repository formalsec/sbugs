#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "jogo.h"



/* Recebe um nome, 2 equipas e os respetivos scores e devolve um novo jogo com esses dados */
Jogo novo_jogo(char* nome, Equipa eq1, Equipa eq2, int score1, int score2) {
    Jogo novo = (Jogo) can_fail_malloc(sizeof(struct jg));

    novo->nome = strdup(nome);
    novo->equipa1 = eq1;
    novo->equipa2 = eq2;
    novo->score1 = score1;
    novo->score2 = score2;
    /* Atualiza o numero de vitorias da equipa vencedora */
    if (score1 > score2)
        altera_vitorias_eq(eq1, 1);
    else if (score2 > score1)
        altera_vitorias_eq(eq2, 1);
    return novo;
}



/* Recebe um jogo e devolve o seu nome */
char* nome_jogo(Jogo jg) {
    return jg->nome;
}



/* Recebe um jogo e o numero da linha de input e imprime esse numero e os dados do jogo */
void escreve_jogo(Jogo jg, int NL) {
    char*nome = jg->nome;
    Equipa eq1 = jg->equipa1;
    Equipa eq2 = jg->equipa2;
    int score1 = jg->score1;
    int score2 = jg->score2;
    char* nome_eq1 = nome_equipa(eq1);
    char* nome_eq2 = nome_equipa(eq2);
    printf("%d %s %s %s %d %d\n", NL, nome, nome_eq1, nome_eq2, score1, score2);
}



/* Recebe um jogo e devolve a euipa vencedora. Em caso de empate, devolve NULL */
Equipa vencedor_jogo(Jogo jogo) {
    if (jogo->score1 > jogo->score2)
        return jogo->equipa1;
    else if (jogo->score2 > jogo->score1)
        return jogo->equipa2;
    else
        return NULL;
}



/* Recebe um jogo, e 2 inteiros e atualiza os scores do jogo para esses inteiros */
void atualiza_scores_jg(Jogo jg, int score1, int score2) {
    jg->score1 = score1;
    jg->score2 = score2;
}



/* Recebe um jogo e apaga-o do sistema */
void apaga_jogo(Jogo jogo) {
    free(jogo->nome);
    free(jogo);
}

