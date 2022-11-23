#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipa.h"
#include "jogo.h"
#include "tab_equipas.h"
#include "tab_jogos.h"

#define STRMAX 1024

/* tamanhos das tabelas de jogos e equipas, respetivamente */
#define TAMANHO_J 2999
#define TAMANHO_E 2027

/* Prototipos */
void adiciona_jogo(tab_disp tab_jogos, tab_disp tab_equipas, jogo *j_1, jogo *j_ult, int n_linha);
void lista_jogos(jogo j_1, int n_linha);
void procura_jogo_nome(tab_disp tab_jogos, int n_linha);
void retira_jogo(tab_disp tab_jogos, jogo *j_1, jogo *j_ult, int n_linha);
void altera_score(tab_disp tab_jogos, int n_linha);
void adiciona_equipa(tab_disp tab_jogos, int n_linha);
void procura_equipa_nome(tab_disp tab_jogos, int n_linha);

/* Funcao auxiliar */
int mudanca_vitorias(int dif_antes, int dif_depois);

/* Interacao com input */
int main() {

    char comando;
    int n_linha = 1;

    /* Registar primeiro e ultimo jogo inseridos */
    jogo jogo_1 = NULLjogo;        
    jogo jogo_ult = NULLjogo;

    tab_disp tab_equipas, tab_jogos;

    tab_equipas = nova_tab(TAMANHO_E);
    tab_jogos = nova_tab(TAMANHO_J);

    while ((comando = getchar()) != 'x') {

        switch (comando) {

            case 'a':
                adiciona_jogo(tab_jogos, tab_equipas, &jogo_1, &jogo_ult, n_linha);
                n_linha ++;
                break;

            case 'l':
                lista_jogos(jogo_1, n_linha);
                n_linha ++;
                break;

            case 'p':
                procura_jogo_nome(tab_jogos, n_linha);
                n_linha ++;
                break;

            case 'r':
                retira_jogo(tab_jogos, &jogo_1, &jogo_ult, n_linha);
                n_linha ++;
                break;

            case 's':
                altera_score(tab_jogos, n_linha);
                n_linha ++;
                break;

            case 'A':
                adiciona_equipa(tab_equipas, n_linha);
                n_linha ++;
                break;

            case 'P':
                procura_equipa_nome(tab_equipas, n_linha);
                n_linha ++;
                break;

            case 'g':
                mostra_equipas_max(tab_equipas, n_linha);
                n_linha ++;
                break;

        }

    }

    liberta_tab_jogos(tab_jogos);
    liberta_tab_equipas(tab_equipas);

    return 0;
}

/* adiciona um jogo a tabela de jogos e regista-o como ultimo jogo*/
void adiciona_jogo(tab_disp tab_jogos, tab_disp tab_equipas, jogo *j_1, jogo *j_ult, int n_linha) {

    char buf_nome[STRMAX];
    char buf_e1[STRMAX];
    char buf_e2[STRMAX];
    int score_e1, score_e2;
    equipa e1 = NULLequipa;
    equipa e2 = NULLequipa;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buf_nome, buf_e1, buf_e2, &score_e1, &score_e2);

    if (procura_tab_jogo(tab_jogos, buf_nome) != NULLjogo) {
        printf("%d Jogo existente.\n", n_linha);
        return;

    }

    if (((e1 = procura_tab_equipa(tab_equipas, buf_e1)) == NULLequipa) ||
        ((e2 = procura_tab_equipa(tab_equipas, buf_e2)) == NULLequipa)) {
            printf("%d Equipa inexistente.\n", n_linha);
            return ;
    }

    *j_ult = novo_jogo(buf_nome, e1, e2, score_e1, score_e2, *j_ult);
    insere_tab_jogo(tab_jogos, *j_ult);

    /* caso em que ainda nao se registaram jogos */
    if (*j_1 == NULLjogo) {
        *j_1 = *j_ult;
    }

    /* incrementar o numero de vitorias de alguma equipa, se for o caso */
    if (score_e1 > score_e2) {
        e1->vitorias ++;
    }

    else if (score_e1 < score_e2) {
        e2->vitorias ++;
    }

    return ;

}


/* adiciona uma equipa a tabela de equipas com base no input */
void adiciona_equipa(tab_disp tab_equipas, int n_linha) {

    char buf[STRMAX];
    equipa equipa_aux;

    scanf(" %[^:\n]", buf);

    if (procura_tab_equipa(tab_equipas, buf) != NULLequipa) {
        printf("%d Equipa existente.\n", n_linha);
        return ;
    }

    equipa_aux = nova_equipa(buf, 0);
    insere_tab_equipa(tab_equipas, equipa_aux);

    return ;

}

/* Exibe a informacao de todos os jogos por ordem de insercao */
void lista_jogos(jogo jogo_1, int n_linha) {

    jogo j_aux = jogo_1;

    while (j_aux != NULLjogo) {
        printf("%d %s %s %s %d %d\n", n_linha, j_aux->nome, j_aux->e1->nome, j_aux->e2->nome, 
                                    j_aux->score_e1, j_aux->score_e2);
        j_aux = j_aux->prox;
    }

    return ;
}

/* procura um jogo pelo nome e exibe a sua informacao */
void procura_jogo_nome(tab_disp tab_jogos, int n_linha) {

    char buf[STRMAX];
    jogo j_aux;

    scanf(" %[^:\n]", buf);

    if ((j_aux = procura_tab_jogo(tab_jogos, buf)) == NULLjogo) {
        printf("%d Jogo inexistente.\n", n_linha);
        return ;
    }

    printf("%d %s %s %s %d %d\n", n_linha, j_aux->nome, j_aux->e1->nome, j_aux->e2->nome, 
                                j_aux->score_e1, j_aux->score_e2);

    return ;

}

/* apaga um jogo da tabela de jogos e atualiza o primeiro e ultimo jogo registados */
void retira_jogo(tab_disp tab_jogos, jogo *j_1, jogo *j_ult, int n_linha) {

    char buf[STRMAX];
    jogo j_aux;

    scanf(" %[^:\n]", buf);

    if ((j_aux = procura_tab_jogo(tab_jogos, buf)) == NULLjogo) {
        printf("%d Jogo inexistente.\n", n_linha);
        return ;
    }

    /* retirar uma vitoria a alguma das equipas, se for o caso */
    if (j_aux->score_e1 > j_aux->score_e2) {
        j_aux->e1->vitorias --;
    }

    else if (j_aux->score_e2 > j_aux->score_e1) {
        j_aux->e2->vitorias --;
    }

    /* caso especial em que se apaga o primeiro jogo registado */
    if (strcmp((*j_1)->nome, buf) == 0) {

        *j_1 = (*j_1)->prox;

        /* caso em que so ha um jogo */
        if (*j_1 == NULLjogo) {
            *j_ult = *j_1;
        }
    }

    /* caso especial em que se apaga o ultimo jogo registado */
    else if (strcmp((*j_ult)->nome, buf) == 0) {
        *j_ult = (*j_ult)->ant;
    }

    retira_tab_jogo(tab_jogos, buf);

    return ;

}

/* altera o score de um jogo na tabela de jogos e atualiza vitorias das respetivas equipas */
void altera_score(tab_disp tab_jogos, int n_linha) {

    char buf[STRMAX];
    int score_e1, score_e2;
    jogo jogo_aux;
    int dif_antes, dif_depois;

    scanf(" %[^:\n]:%d:%d", buf, &score_e1, &score_e2);

    if ((jogo_aux = procura_tab_jogo(tab_jogos, buf)) == NULLjogo) {
        printf("%d Jogo inexistente.\n", n_linha);
        return ;
    }

    /* obter saldo do score antes e depois da mudanca */
    dif_antes = jogo_aux->score_e1 - jogo_aux->score_e2;
    dif_depois = score_e1 - score_e2;

    /* ha mudanca no numero de vitorias nos casos em que os saldos tem 
     * sinais contrarios ou se pelo menos um for 0 (empate) */
    if (dif_antes * dif_depois <= 0) {
        jogo_aux->e1->vitorias += mudanca_vitorias(dif_antes, dif_depois);

        /* trocar sinal dos saldos para a segunda equipa */
        jogo_aux->e2->vitorias += mudanca_vitorias(-1 * dif_antes, -1 * dif_depois);
    }

    jogo_aux->score_e1 = score_e1;
    jogo_aux->score_e2 = score_e2;

    return ;

}

/* Funcao que recebe o saldo de um jogo antes e depois de uma mudanca
 * e retorna 1 se tal mudanca se traduz numa vitoria, -1 no caso de uma derrota, 
 * e 0 se nao ha mudanca */
int mudanca_vitorias(int dif_antes, int dif_depois) {

    /* se se atualizou para uma vitoria */
    if (dif_depois > 0) {
        return 1;
    }

    /* se inicialmente houve uma vitoria */
    if (dif_antes > 0) {
        return -1;
    }

    else {
        return 0;
    }

}

/* procura uma equipa pelo nome na tabela de equipas */
void procura_equipa_nome(tab_disp tab_equipas, int n_linha) {

    char buffer[STRMAX];
    equipa equipa_aux;

    scanf(" %[^:\n]", buffer);

    if ((equipa_aux = procura_tab_equipa(tab_equipas, buffer)) == NULLequipa) {
        printf("%d Equipa inexistente.\n", n_linha);
        return ;
    }

    printf("%d %s %d\n", n_linha, equipa_aux->nome, equipa_aux->vitorias);

    return ;

}









