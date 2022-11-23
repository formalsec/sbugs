#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "HT_equipas.h"
#include "jogo.h"
#include "HT_jogos.h"
#include "lista_jogos.h"

#define MAX_EQ 1013 /* Constante para dividir as equipas pela hashtable */
#define MAX_JG 1013 /* Constante para dividir os jogos pela hashtable */
#define MAX_NOME_EQ 1023 /* Numero maximo de caracteres do nome de uma equipa */
#define MAX_NOME_JG 1023 /* Numero maximo de caracteres do nome de um jogo */

/* Funcoes dos comandos */
void comando_A(int NL, HT_eq equipas);
void comando_P(int NL, HT_eq equipas);
void comando_a(int NL, HT_eq equipas, HT_jg jogos, Lista_jg lista);
void comando_p(int NL, HT_jg jogos);
void comando_s(int NL, HT_jg jogos);
void comando_l(int NL, Lista_jg lista);
void comando_r(int NL, HT_jg jogos, Lista_jg lista_jogos);
void comando_g(int NL, HT_eq equipas);
void termina(HT_eq equipas, HT_jg jogos, Lista_jg lista_jogos);



/* Funcao main: Le os comandos introduzidos pelo utilizador e chama as funcoes correspondentes */
int main() {
    int NL = 1;
    char comando;

    /* Inicializa hashtables e a lista*/
    HT_eq equipas = HTeq_inicializa(MAX_EQ);
    HT_jg jogos = HTjg_inicializa(MAX_JG);
    Lista_jg lista_jogos = LSTjg_inicializa();

    while (1) {
        comando = getchar();
        switch (comando) {
            case 'A': {
                comando_A(NL, equipas);
                break;
            }
            
            case 'P': {
                comando_P(NL, equipas);
                break;
            }

            case 'a': {
                comando_a(NL, equipas, jogos, lista_jogos);
                break;
            }

            case 'p': {
                comando_p(NL, jogos);
                break;
            }
            case 's': {
                comando_s(NL, jogos);
                break;
            }
            
            case 'l': {
                comando_l(NL, lista_jogos);
                break;
            }
            
            case 'r': {
                comando_r(NL, jogos, lista_jogos);
                break;
            }
            case 'g': {
                comando_g(NL, equipas);
                break;
            }
            case 'x': {
                termina(equipas, jogos, lista_jogos);
                return 0; 
            }
        }
        getchar();
        NL++;
    }
    return 0;
}



/* Adiciona uma nova equipa ao sistema */
void comando_A(int NL, HT_eq equipas) {
    char n[MAX_NOME_EQ];
    char *nome;

    /* Le o nome da equipa */
    scanf(" %[^:\n]", n);
    nome = strdup(n);

    /* Se a equipa nao existir, cria e adiciona uma nova */
    if (HTeq_procura(equipas, nome, MAX_EQ) == NULL) {
        HTeq_adiciona(equipas, nome, MAX_EQ);
    }

    else
        printf("%d Equipa existente.\n", NL);

    free(nome);
}



/* Procura uma equipa no sistema */
void comando_P(int NL, HT_eq equipas) {
    char n[MAX_NOME_EQ];
    char *nome;
    Equipa eq;

    /* Le o nome da equipa */
    scanf(" %[^:\n]", n);
    nome = strdup(n);

    eq = HTeq_procura(equipas, nome, MAX_EQ);

    /* Se a equipa nao existir, imprime erro */
    if (eq == NULL)
        printf("%d Equipa inexistente.\n", NL);

        /* Senao, imprime o nome e o numero de vitorias */
    else {
        printf("%d %s %d\n", NL, nome_equipa(eq), vitorias_equipa(eq));
    }
    free(nome);
}



/* Adiciona um novo jogo ao sistema */
void comando_a(int NL, HT_eq equipas, HT_jg jogos, Lista_jg lista) {
    int score1, score2;
    char n_jg[MAX_NOME_JG], n_eq1[MAX_NOME_EQ], n_eq2[MAX_NOME_EQ];
    char *nome, *nome_eq1, *nome_eq2;
    Equipa eq1, eq2;
    Jogo jogo;

    /* Le o nome do jogo, os nomes das equipas e os scores de cada uma */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", n_jg, n_eq1, n_eq2, &score1, &score2);
    nome = strdup(n_jg);
    nome_eq1 = strdup(n_eq1);
    nome_eq2 = strdup(n_eq2);

    /* Se o jogo ja existir, imprime erro */
    if (HTjg_procura(jogos, nome, MAX_JG) != NULL)
        printf("%d Jogo existente.\n", NL);

    else {
        eq1 = HTeq_procura(equipas, nome_eq1, MAX_EQ);
        eq2 = HTeq_procura(equipas, nome_eq2, MAX_EQ);
        /* Se pelo menos uma das equipas nao existir, imprime erro */
        if (eq1 == NULL || eq2 == NULL)
            printf("%d Equipa inexistente.\n", NL);

        /* Senao, cria novo jogo e adiciona-o 'a hashtable e 'a lista */
        else {
            jogo = novo_jogo(nome, eq1, eq2, score1, score2);
            HTjg_adiciona(jogos, nome, jogo, MAX_JG);
            LSTjg_adiciona(lista, jogo);
        }
    }
    free(nome);
    free(nome_eq1);
    free(nome_eq2);
}



/* Procura um jogo no sistemma */
void comando_p(int NL, HT_jg jogos) {
    char n[MAX_NOME_JG];
    char *nome;
    Jogo jg;

    /* Le o nome do jogo */
    scanf(" %[^:\n]", n);
    nome = strdup(n);

    jg = HTjg_procura(jogos, nome, MAX_JG);

    /* Se o jogo nao existir, imprime erro */
    if (jg == NULL)
        printf("%d Jogo inexistente.\n", NL);

    /* Senao, imprime as informacoes do jogo */
    else {
        escreve_jogo(jg, NL);
    }
    free(nome);
}



/* Altera o score de um jogo */
void comando_s(int NL, HT_jg jogos) {
    int novo_score1, novo_score2;
    char n[MAX_NOME_JG];
    char *nome;
    Jogo jogo;
    Equipa antigo_vencedor, novo_vencedor;

    /* Le o nome do jogo e os novos scores */
    scanf(" %[^:\n]:%d:%d", n, &novo_score1, &novo_score2);
    nome = strdup(n);
    jogo = HTjg_procura(jogos, nome, MAX_JG);

    /* Se  o jogo nao existir, imprime erro */
    if (jogo == NULL)
        printf("%d Jogo inexistente.\n", NL);

    /* Senao, obtem o antigo vencedor, atualiza os scores e obtem o novo vencedor */
    else {
        antigo_vencedor = vencedor_jogo(jogo);
        atualiza_scores_jg(jogo, novo_score1, novo_score2);
        novo_vencedor = vencedor_jogo(jogo);

        /* Se antes era um empate e agora nao e', acrescenta 1 vitoria ao novo vencedor */
        if (antigo_vencedor == NULL && novo_vencedor != NULL)
            altera_vitorias_eq(novo_vencedor, 1);

        /* Se antes nao era empate e agora e', retira 1 vitoria ao antigo vencedor */
        else if (antigo_vencedor != NULL && novo_vencedor == NULL)
            altera_vitorias_eq(antigo_vencedor, -1);

        /* Se nunca foi empate e o vencedor mudou, retira 1 vitoria ao antigo vencedor e
        acrescenta 1 vitoria ao novo vencedor */
        else if (antigo_vencedor != novo_vencedor) {
            altera_vitorias_eq(novo_vencedor, 1);
            altera_vitorias_eq(antigo_vencedor, -1);
        }
    }
    free(nome);
}



/* Lista todos os jogos introduzidos, por ordem de introducao*/
void comando_l(int NL, Lista_jg lista) {
    LSTjg_escreve(NL, lista);
}



/* Apaga um jogo do sistema */
void comando_r(int NL, HT_jg jogos, Lista_jg lista_jogos) {
    char *nome;
    char n[MAX_NOME_JG];
    Jogo jogo;
    Equipa vencedor;

    /* Le o nome do jogo */
    scanf(" %[^:\n]", n);
    nome = strdup(n);
    jogo = HTjg_procura(jogos, nome, MAX_JG);

    /* Se o jogo nao existir, imprime erro */
    if (jogo == NULL)
        printf("%d Jogo inexistente.\n", NL);

    else {
        vencedor = vencedor_jogo(jogo);
        /* Se nao for um empate, retira 1 vitoria ao vencedor */
        if (vencedor != NULL)
            altera_vitorias_eq(vencedor, -1);
        
        /* apaga os nos da lista e da hashtable que contem o jogo */
        LSTjg_apaga(lista_jogos, jogo);
        HTjg_apaga(jogos, nome, jogo, MAX_JG);
        /* apaga o jogo do sistema */
        apaga_jogo(jogo);
    }
    
    free(nome);
}



/* Encontra as equipas que ganharam mais jogos */
void comando_g(int NL, HT_eq equipas) {
    int max_num[2];
    int max_v, num, i;
    Equipa* melhores;

    /* Obtem o numero maximo de jogos ganhos por 1 equipa e o numero de equipas com essa
    quantidade de jogos ganhos */
    maximo_vitorias(equipas, max_num, MAX_EQ);
    max_v = max_num[0];
    num = max_num[1];

    /* se nao existir nenhuma equipa, termina */
    if (num == 0)
        return;

    /* Cria um vetor com todas as equipas com o numero maximo de vitorias */
    melhores = (Equipa*) can_fail_malloc(num * sizeof(Equipa));
    melhores_equipas(equipas, melhores, max_v, MAX_EQ);
    qsort(melhores, num, sizeof(Equipa), compara_eq);

    /* Imprime as equipas por ordem */
    printf("%d Melhores %d\n", NL, max_v);
    for (i=0; i<num; i++)
        printf("%d * %s\n", NL, nome_equipa(melhores[i]));

    free(melhores);
}



/* Termina o programa */
void termina(HT_eq equipas, HT_jg jogos, Lista_jg lista_jogos) {
    LSTjg_termina(lista_jogos);
    HTjg_termina(jogos, MAX_JG);
    HTeq_termina(equipas, MAX_EQ);
}
