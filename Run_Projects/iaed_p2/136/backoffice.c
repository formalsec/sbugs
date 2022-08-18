#include "backoffice.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* funcao que executa o comando a - criar um novo jogo */
void executa_a(int nL, fila jogos, fila equipas, fila jogos_ord)
{
    /* parametros lidos */
    char a[MAX_CAR], b[MAX_CAR], c[MAX_CAR];
    int s1, s2;

    jogo j, j1; /* jogo a adicionar / procurar */
    equipa e1, e2; /* equipas a procurar - participantes no jogo */

    scanf(" %1023[^:\n]:%1023[^:\n]:%1023[^:\n]:%d:%d", a, b, c, &s1, &s2); /* leitura */

    /* 1o averigua se o jogo ja existe */
    j1 = encontra_j_tab(jogos, a);
    
    if (j1) /* se encontrar da o erro devido */
    {
        escreve_erro(nL, JG_REP);
        return;
    }

    /* 2o averigua se as equipas existem */

    e1 = encontra_e_tab(equipas, b); /* procura a equipa 1 */

    if (!e1) /* se nao a encontrar da o erro devido */
    {
        escreve_erro(nL, NAO_EQ);
        return;
    }

    e2 = encontra_e_tab(equipas, c); /* procura a equipa 2 */

    /* se nao a da o erro devido */
    if (!e2)
    {
        escreve_erro(nL, NAO_EQ);
        return;
    }
    
    /* 4o se nao... */
    j = cria_jogo(a, e1, e2, s1, s2); /* cria o jogo */

    junta_j(jogos, j, TABELA); /* adiciona-o a tabela de dispersao */
    junta_j(jogos_ord , j, FILA); /* adiciona-o a fila de jogos */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando A - criar uma nova equipa */
void executa_A(int nL, fila equipas, fila equipas_ord)
{              
    char a[MAX_CAR]; /* parametro lido */
    equipa e1, e; /* equipa a procurar / adicionar */

    scanf(" %1023[^:\n]", a); /* le no formato de entrada */

    /* 1o averigua-se se a equipa ja foi criada */
    e1 = encontra_e_tab(equipas, a); 

    if (e1) /* se ja existir da o erro devido */
    {
        escreve_erro(nL, EQ_REP);
        return;
    }

    /* 2o se nao... */
    e = cria_equipa(a); /* cria a equipa */
    junta_e(equipas, e, TABELA); /* adiciona-a a tabela de dispersao */
    junta_e(equipas_ord, e, FILA); /* adiciona-a a fila de equipas */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando l - listar os jogos pela ordem de criacao */
void executa_l(int nL, fila jogos_ord)
{
    escreve_j_lst(nL, jogos_ord);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando p - procurar um jogo */
void executa_p(int nL, fila jogos)
{
    char a[MAX_CAR]; /* parametro lido */
    jogo j; /* jogo a procurar */

    scanf(" %1023[^:\n]", a); /* le no formato de entrada */

    j = encontra_j_tab(jogos, a); /* procura o jogo */

    if (!j) /* se nao encontrar da o devido erro */
        escreve_erro(nL, NAO_JG);
    else /* se nao, imprime o que encontrar */
        escreve_jogo(nL, j);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando P - procurar uma equipa */
void executa_P(int nL, fila equipas)
{
    char a[MAX_CAR]; /* parametro lido */
    equipa e; /* equipa a procurar */

    scanf(" %1023[^:\n]", a); /* le no formato de entrada */

    e = encontra_e_tab(equipas, a); /* procura a equipa */

    if (!e) /* se nao encontrar da o devido erro */
        escreve_erro(nL, NAO_EQ);
    else /* se nao, imprime o que encontrar */
        escreve_equipa(nL, e);
}                 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando r - apagar um jogo */
void executa_r(int nL, fila jogos, fila jogos_ord)
{
    char a[MAX_CAR]; /* parametro lido */
    jogo j; /* jogo a apagar */

    scanf(" %1023[^:\n]", a); /* le no formato de entrada */

    j = encontra_j_tab(jogos, a); /* procura o jogo */

    if (!j) /* se nao encontrar da o devido erro */
        escreve_erro(nL, NAO_JG);

    else /* se nao...*/
    {
        equipa vencedora; /* equipa vencedora do jogo */
        /* 1o retira a vitoria a vencedora da partida */

        vencedora = obtem_vencedora(j);
        if (vencedora == EQ_1(j)) /* se a vencedora for a equipa 1 */
            muda_vitorias(EQ_1(j), '-'); /* retira-lhe a vitoria */
        else if (vencedora == EQ_2(j)) /* se a vencedora for a equipa 2 */
            muda_vitorias(EQ_2(j), '-'); /* retira-lhe a vitoria */

        /* 2o apaga o jogo da tabela de dispersao e da fila */

        tira_j(jogos, j, TABELA);
        tira_j(jogos_ord, j, FILA);

        /* 3o liberta a memoria associada ao jogo */

        apaga_jogo(j);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando s - alterar o score de um jogo */
void executa_s(int nL, fila jogos)
{
    /* parametros lidos */
    char a[MAX_CAR]; 
    int s1, s2;

    jogo j; /* jogo a alterar */

    scanf(" %1023[^:\n]:%d:%d", a, &s1, &s2); /* le no formato de entrada */

    j = encontra_j_tab(jogos, a); /* procura o jogo */

    if (!j) /* se nao encontrar da o devido erro */
        escreve_erro(nL, NAO_JG);

    else /* se nao...*/
    {
        equipa vencedora; /* equipa vencedora do jogo anterior */
        /* primeiro tira a vitoria a antiga vencedora (se houver) */
        vencedora = obtem_vencedora(j);
        if (vencedora == EQ_1(j)) /* se a vencedora for a equipa 1 */
            muda_vitorias(EQ_1(j), '-'); /* retira-lhe a vitoria */
        else if (vencedora == EQ_2(j)) /* se a vencedora for a equipa 2 */
            muda_vitorias(EQ_2(j), '-'); /* retira-lhe a vitoria */

        /* depois adiciona-a a nova vencedora (se houver) */
        if (s1 > s2) /* nova vencedora equipa 1 */
            muda_vitorias(EQ_1(j), '+');
        else if (s2 > s1) /* nova vencedora equipa 2 */
            muda_vitorias(EQ_2(j), '+');

        /* no fim muda o score do jogo */
        altera_score(j, s1, s2);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao que executa o comando g - listar as equipas com mais vitorias */
void executa_g(int nL, fila equipas_ord)
{
    par_resultado max; /* maximo vitorias do conjunto de equipas e o no. de equipas que
    o tiveram */
    int maximo, num_venc; /* componentes do par_resultado max */
    arvore * raiz = NULL; /* arvore onde vamos adicionar as equipas com no. max. de vitorias */

    /* primeiro temos de saber o que procuramos -- MAXIMO */
    max = maximo_vitorias(equipas_ord); /* calculamos o par */
    maximo = max.maximo; /* numero maximo de vitorias */
    num_venc = max.num_venc; /* numero de equipas com o numero maximo de vitorias */
    if (maximo == NOMAX) return; /* se nao houver equipas nao escreve nada */

     /* depois temos de saber o que vamos imprimir -- ARVORE */
    raiz = ARVbuild(raiz, equipas_ord, maximo, num_venc);

    /* tendo a arvore, e so imprimi-la e no fim libertar a memoria a ela associada */

    printf("%d Melhores %d\n", nL, maximo); /* imprime-se o cabecalho */
    ARVprint(raiz, nL); /* depois a arvore */
    ARVclear(raiz); /* e depois libertamos a memoria */
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
