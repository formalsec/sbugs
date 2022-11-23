#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1023 /* Numero maximo de caracteres de um nome. */
#define INIT_HT 10000 /* Numero para inicializar a hashtable. */

/* Funcao que cria e devolve um sistema inicializado. */
Sistema *novoSistema() {
    Sistema *sistema = can_fail_malloc(sizeof(Sistema));

    sistema->jogos = init_jogos();
    sistema->equipas = init_equipas();
    sistema->ht = HTinit(INIT_HT, INIT_HT);

    return sistema;
}

/* Funcao que liberta toda a memoria associada ao sistema. */
void destroy_sistema(Sistema *sistema) {
    destroy_jogos(sistema->jogos);
    destroy_equipas(sistema->equipas);
    HTdestroy(sistema->ht);
    free(sistema);
}

/* Funcao que le o nome de um jogo, o nome de duas equipas e os seus respetivos scores,
 * se o nome do jogo nao existir no sistema e se as duas equipas existirem no sistema,
 * guarda o jogo no sistema,
 * se nao imprime uma mensagem de erro. */
void adiciona_jogo(Sistema *sistema, int NL) {
    node_jogos *jogo = NULL;
    node_equipas *equipa1 = NULL, *equipa2 = NULL;
    char n[MAX_CHAR + 1], e1[MAX_CHAR + 1], e2[MAX_CHAR + 1];
    int s1, s2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", n, e1, e2, &s1, &s2);

    if (HTsearch_jogo(sistema->ht, n))
        printf("%d Jogo existente.\n", NL);

    else {
        equipa1 = HTsearch_equipa(sistema->ht, e1);
        equipa2 = HTsearch_equipa(sistema->ht, e2);

        if (!equipa1 || !equipa2)
            printf("%d Equipa inexistente.\n", NL);

        else {
            jogo = cria_jogo(n, equipa1, equipa2, s1, s2);
            add_jogo(sistema->jogos, jogo);
            HTinsert_jogo(sistema->ht, jogo);
        }
    }
}

/* Funcao que imprime todos os jogos pela ordem em que foram introduzidos,
 * se nao existir nenhum jogo nao imprime nada. */
void lista_jogos(Sistema *sistema, int NL) {
    node_jogos *jogo = sistema->jogos->head;
    for (; jogo; jogo = jogo->next)
        printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome,
               jogo->score1, jogo->score2);
}

/* Funcao que le o nome de um jogo e imprime o respetivo jogo,
 * se nao existir nenhum jogo com esse nome imprime uma mensagem de erro. */
void procura_jogo(Sistema *sistema, int NL) {
    node_jogos *jogo = NULL;
    char n[MAX_CHAR + 1];

    scanf(" %[^:\n]", n);

    jogo = HTsearch_jogo(sistema->ht, n);
    if (jogo)
        printf("%d %s %s %s %d %d\n", NL, jogo->nome, jogo->equipa1->nome, jogo->equipa2->nome,
               jogo->score1, jogo->score2);

    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Funcao que le o nome de um jogo e remove o respetivo jogo do sistema,
 * se nao existir nenhum jogo com esse nome imprime uma mensagem de erro. */
void apaga_jogo(Sistema *sistema, int NL) {
    node_jogos *jogo = NULL;
    char n[MAX_CHAR + 1];

    scanf(" %[^:\n]", n);

    jogo = HTsearch_jogo(sistema->ht, n);
    if (jogo) {
        if (jogo->score1 > jogo->score2)
            equipa_diminui_jogos_ganhos(jogo->equipa1);

        else if (jogo->score1 < jogo->score2)
            equipa_diminui_jogos_ganhos(jogo->equipa2);

        HTdelete_jogo(sistema->ht, jogo->nome);
        remove_node_jogos(sistema->jogos, jogo);

    } else
        printf("%d Jogo inexistente.\n", NL);
}

/* Funcao que le o nome de um jogo e dois scores,
 * se existir um jogo com esse nome atualiza os scores do jogo,
 * se nao imprime uma mensagem de erro.  */
void altera_score(Sistema *sistema, int NL) {
    node_jogos *jogo = NULL;
    char n[MAX_CHAR + 1];
    int s1, s2;

    scanf(" %[^:\n]:%d:%d\n", n, &s1, &s2);

    jogo = HTsearch_jogo(sistema->ht, n);
    if (jogo)
        atualiza_scores_jogo(jogo, s1, s2);

    else
        printf("%d Jogo inexistente.\n", NL);
}

/* Funcao que le o nome de uma equipa,
 * se nao existir nehuma equipa com esse nome,
 * guarda a equipa no sistema,
 * caso contrario imprime uma mensagem de erro. */
void adiciona_equipa(Sistema *sistema, int NL) {
    node_equipas *equipa = NULL;
    char n[MAX_CHAR + 1];

    scanf(" %[^:\n]", n);

    if (HTsearch_equipa(sistema->ht, n))
        printf("%d Equipa existente.\n", NL);

    else {
        equipa = cria_equipa(n);
        sistema->equipas = push_equipa(sistema->equipas, equipa);
        HTinsert_equipa(sistema->ht, equipa);
    }
}

/* Funcao que le o nome de uma equipa e imprime o nome e o numero de jogos ganhos dessa equipa,
 * se nao existir nenhuma equipa com esse nome imprime uma mensagem de erro. */
void procura_equipa(Sistema *sistema, int NL) {
    node_equipas *equipa = NULL;
    char n[MAX_CHAR + 1];

    scanf(" %[^:\n]", n);

    equipa = HTsearch_equipa(sistema->ht, n);
    if (equipa)
        printf("%d %s %d\n", NL, n, equipa->jogos_ganhos);

    else
        printf("%d Equipa inexistente.\n", NL);
}

/* Funcao auxiliar que compara os nomes de duas equipas. */
int compara(const void *a, const void *b) {
    return strcmp((*(const node_equipas **)a)->nome, (*(const node_equipas **)b)->nome);
}

/* Funcao auxiliar que ordena um vetor de equipas por ordem lexicografica. */
void ordena_equipas(node_equipas **melhores, int tamanho) {
    qsort(melhores, tamanho, sizeof(node_equipas *), compara);
}

/* Funcao que imprime as equipas que ganharam mais jogos por ordem lexicografica,
 * se nao existir nenhuma equipa nao imprime nada.*/
void encontra_equipas(Sistema *sistema, int NL) {
    node_equipas **melhores = NULL; /* Vetor auxiliar para guardar as melhores equipas. */
    long *numero_melhores = NULL;   /* Ponteiro para o tamanho do vetor melhores. */
    long i = 0;

    if (sistema->equipas->head) {
        numero_melhores = can_fail_malloc(sizeof(long));
        melhores = melhores_equipas(sistema->equipas, numero_melhores);

        printf("%d Melhores %d\n", NL, melhores[0]->jogos_ganhos);

        ordena_equipas(melhores, *numero_melhores);

        for (i = 0; i < *numero_melhores; i++)
            printf("%d * %s\n", NL, melhores[i]->nome);

        free(numero_melhores);
        destroy_melhores(melhores);
    }
}
