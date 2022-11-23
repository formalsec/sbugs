#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos_equipas.h"


/*Tamanho da HashTable para equipas e a respetiva ocupacao.*/
long tabEq_size = 8, tabEq_ocup;
/*Ponteiro para a HashTable das Equipas.*/
pEquipa *tabela_Equi;
/*Tamanho da HashTable para jogos e a respetiva ocupacao.*/
long tabJo_size = 8, tabJo_ocup;
/*Ponteiro para a HashTable dos Jogos.*/
pJogo* tabela_Jo;
/*Head e Tail da lista duplamente ligada que guarda os jogos por ordem de introducao.*/
pJogo head, tail;

/*--------------*/
/*---Funcoes----*/
/*--Auxiliares--*/
/*--------------*/

/*
Funcao 'inicializar_estruturas':
    Argumentos - void;
    Descricao - cria as estruturas necessarias para o inicio da execucao dos comandos;
    Valor de Retorno - void;
*/
void inicializar_estruturas(){
    tabela_Equi = cria_tabela_equi();
    tabela_Jo = cria_tabela_jogo();
}

/*
Funcao 'freeEstruturas':
    Argumentos - void;
    Descricao - liberta a memoria alocada para as estrututras utilizadas;
    Valor de Retorno - void;
*/
void freeEstruturas(){
    freeTabEq();
    freeTabJo();
}

/*--------------*/
/*---Comandos---*/
/*--------------*/

/*Comando 'a':
    Descricao - Adiciona um novo jogo;
*/
void a(long line){
    int sc1, sc2;
    long i, j;
    char nomes[3][1024];
    pJogo novo_jogo;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nomes[0], nomes[1], nomes[2], &sc1, &sc2);
    if (search_Jo(nomes[0]) != NOT_FOUND)
        printf("%ld Jogo existente.\n", line);
    else if ((i = search_Eq(nomes[1])) == NOT_FOUND || (j = search_Eq(nomes[2])) == NOT_FOUND)
        printf("%ld Equipa inexistente.\n", line);
    else{
        novo_jogo = cria_jogo(nomes[0], tabela_Equi[i], tabela_Equi[j], sc1, sc2);
        insert_Jo(novo_jogo);
    }
}

/*Comando 'A':
    Descricao - Adiciona uma nova equipa.
*/
void A(long line){
    char str[1024];
    pEquipa nova_equipa;
    scanf("%[^:\n]", str);
    if (search_Eq(str) != NOT_FOUND)
        printf("%ld Equipa existente.\n", line);
    else{
        nova_equipa = cria_equipa(str);
        insert_Eq(nova_equipa);
    }
}

/*Comando 'l':
    Descricao - Lista todos os jogos pela ordem em que foram introduzidos.
*/
void l(long line){
    pJogo pAux=head;
    while (pAux != NULL){
        printf("%ld %s %s %s %d %d\n", line, pAux->nome, pAux->e1->nome, pAux->e2->nome, pAux->sc1, pAux->sc2);
        pAux = pAux->next;
    }
}

/*Comando 'p':
    Descricao - Procura um jogo.
*/
void p(long line){
    long i;
    char str[1024];
    scanf("%[^:\n]", str);
    if ((i = search_Jo(str)) == NOT_FOUND)
        printf("%ld Jogo inexistente.\n", line);
    else{
        printf("%ld %s %s %s %d %d\n", line, tabela_Jo[i]->nome, tabela_Jo[i]->e1->nome, tabela_Jo[i]->e2->nome, tabela_Jo[i]->sc1, tabela_Jo[i]->sc2);
    }
}

/*Comando 'P':
    Descricao - Procura uma equipa.
*/
void P(long line){
    long i;
    char str[1024];
    scanf("%[^:\n]", str);
    if ((i = search_Eq(str)) == NOT_FOUND)
        printf("%ld Equipa inexistente.\n", line);
    else{
        printf("%ld %s %d\n", line, tabela_Equi[i]->nome, tabela_Equi[i]->vit);
    }
}

/*Comando 'r':
    Descricao - Apaga um jogo.
*/
void r(long line){
    char str[1024];
    scanf("%[^:\n]", str);
    if (remove_Jo(str) != REMOVED)
        printf("%ld Jogo inexistente.\n", line);
}

/*Comando 's':
    Descricao - Altera a pontuacao (_score_) de um jogo.
*/
void s(long line){
    int sc1, sc2, ant_venc, novo_venc;
    long i;
    char str[1024];
    scanf("%[^:\n]:%d:%d", str, &sc1, &sc2);
    if ((i = search_Jo(str)) == NOT_FOUND)
        printf("%ld Jogo inexistente.\n", line);
    else{
        ant_venc = vencedor(tabela_Jo[i]->sc1, tabela_Jo[i]->sc2);
        novo_venc = vencedor(sc1, sc2);
        tabela_Jo[i]->sc1 = sc1;
        tabela_Jo[i]->sc2 = sc2;
        atualiza_vencedores(ant_venc, novo_venc, tabela_Jo[i]->e1, tabela_Jo[i]->e2);
    }  
}

/*Comando 'g':
    Descricao - Encontra as equipas que venceram mais jogos.
*/
void g(long line){
    int max = 0;
    long i = 0, j = 0;
    pEquipa *campeoes;
    if (tabEq_ocup == 0)
        return;
    campeoes = (pEquipa*) can_fail_malloc(sizeof(pEquipa) * tabEq_ocup);
    for (i = 0; i < tabEq_size; ++i)
        if (tabela_Equi[i] != NULL){
            if (tabela_Equi[i]->vit==max){
                campeoes[j] = tabela_Equi[i];
                ++j;
            }
            else if (tabela_Equi[i]->vit > max){
                j = 0;
                max = tabela_Equi[i]->vit;
                campeoes[j] = tabela_Equi[i];
                ++j;
            }
        }
    mergesort(campeoes, 0, j-1);
    printf("%ld Melhores %d\n", line, max);
    for (i = 0; i < j; ++i){
        printf("%ld * %s\n", line, campeoes[i]->nome);
    }
    free(campeoes);
}

/*--------------*/
/*-----Main-----*/
/*--------------*/

/*
Descricao:
    Depois de inicializar as estruturas seleciona o comando correspondente ao input.
*/
int main(){
    long line=0; /*Contador de linhas incrementado em cada linha.*/
    char c;
    inicializar_estruturas();
    while ((c = getchar()) != 'x'){
        line++;
        switch (c){
            case 'a':
                getchar();
                a(line);
                break;

            case 'A':
                getchar();
                A(line);
                break;

            case 'l':
                l(line);
                break;

            case 'p':
                getchar();
                p(line);
                break;

            case 'P':
                getchar();
                P(line);
                break;

            case 'r':
                getchar();
                r(line);
                break;

            case 's':
                getchar();
                s(line);
                break;

            case 'g':
                g(line);
                break;

        }
        getchar();
    }
    freeEstruturas();
    return 0;
}