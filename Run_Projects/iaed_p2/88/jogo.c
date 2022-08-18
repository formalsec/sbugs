#include "jogo.h"

/* cria um novo jogo */
jogo novo_jogo(char *nome, equipa e1, equipa e2, int score_e1, int score_e2, jogo ultimo_jogo) {

    jogo jogo_aux = (jogo) malloc(sizeof(struct stru_jogo));

    jogo_aux->nome = (char *) malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(jogo_aux->nome, nome);

    jogo_aux->e1 = e1;
    jogo_aux->e2 = e2;

    jogo_aux->score_e1 = score_e1;
    jogo_aux->score_e2 = score_e2;

    jogo_aux->ant = ultimo_jogo;
    jogo_aux->prox = NULLjogo;

    /* colocar o jogo criado como proximo jogo do ultimo jogo */
    if (ultimo_jogo != NULLjogo) {
        ultimo_jogo->prox = jogo_aux;
    }

    return jogo_aux;

}

/* liberta a memoria associada a um jogo */
void liberta_jogo(void *j) {

    free(((jogo)(j))->nome);

    /* corrigir ordem entre jogos */
    if (((jogo)(j))->prox != NULLjogo) {
        ((jogo)(j))->prox->ant = ((jogo)(j))->ant;
    }

    if(((jogo)(j))->ant != NULLjogo) {
        ((jogo)(j))->ant->prox = ((jogo)(j))->prox;
    }

    free((jogo)(j));

}

/* verifica se o nome do jogo j e igual a string */
int jogo_nome_igual(void *j, void *string) {
    return (strcmp(((jogo)(j))->nome, (char *)string) == 0);
}


