#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heads.h"
/*Funcao que adiciona um novo jogo ao sistema*/
void add_jovo(int NL, list_jogos *jogos, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam)
{
    jogo *novo = malloc(sizeof(jogo) + 1);
    equipa *equipa;
    int score1, score2;
    char tmp[1023]; /*usa-se apenas um char tmp para todos os inputs para poupar memoria*/

    scanf(" %[^:]", tmp);
    novo->nome = malloc(sizeof(char) * (strlen(tmp) + 1)); /*Adiciona-se o nome*/
    strcpy(novo->nome, tmp);

    scanf(":%[^:]", tmp);
    novo->e1 = malloc(sizeof(char) * (strlen(tmp) + 1)); /*Adiciona-se a equipa 1*/
    strcpy(novo->e1, tmp);

    scanf(":%[^:]", tmp);
    novo->e2 = malloc(sizeof(char) * (strlen(tmp) + 1)); /*Adiciona-se a equipa 2*/
    strcpy(novo->e2, tmp);

    scanf(":%d:%d", &score1, &score2);
    novo->score1 = score1; /*Adiciona-se o score da equipa 1*/
    novo->score2 = score2; /*Adiciona-se o score da equipa 2*/

    if (searchJogo(novo->nome, HT_jogos, HT_tam) != NULL) /*Se o jogo ja estiver registado no sistema*/
    {
        printf("%d Jogo existente.\n", NL);
        free_jogo(novo);
    }
    /*Se alguma das equipas nao estiver registada no sistema*/
    else if (searchEquipa(novo->e1, HT_equipas, HT_tam) == NULL || searchEquipa(novo->e2, HT_equipas, HT_tam) == NULL)
    {
        printf("%d Equipa inexistente.\n", NL);
        free_jogo(novo); /*Liberta-se a memoria visto que nao se adiciona a lista*/
    }
    else /*Regista-se o novo jogo no sistema*/
    {
        novo->prev = jogos->last;
        novo->next = NULL;
        addHTJ(novo, HT_jogos, HT_tam); /*Adiciona-se na hashtable*/
        if (jogos->last)
            jogos->last->next = novo;
        else
            jogos->head = novo;
        jogos->last = novo;

        /*Adicionar um jogo ganho a equipa vencedora da partida*/
        if (novo->score1 > novo->score2)
        {
            equipa = searchEquipa(novo->e1, HT_equipas, HT_tam);
            equipa->jogos_ganhos = equipa->jogos_ganhos + 1;
        }
        else if (novo->score1 < novo->score2)
        {
            equipa = searchEquipa(novo->e2, HT_equipas, HT_tam);
            equipa->jogos_ganhos = equipa->jogos_ganhos + 1;
        }
    }
}
/*Funcao que remove um jogo do sistema*/
void apaga_jogo(int NL, list_jogos *jogos, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam)
{
    jogo *jogo;
    char nome[1023];
    equipa *equipa;

    scanf(" %[^:\n]", nome);
    jogo = searchJogo(nome, HT_jogos, HT_tam);
    if (jogo) /*Se o jogo existir no sistema*/
    {
        if (jogo->score1 > jogo->score2)
        {
            equipa = searchEquipa(jogo->e1, HT_equipas, HT_tam);
            equipa->jogos_ganhos = equipa->jogos_ganhos - 1;
        }
        if (jogo->score1 < jogo->score2)
        {
            equipa = searchEquipa(jogo->e2, HT_equipas, HT_tam);
            equipa->jogos_ganhos = equipa->jogos_ganhos - 1;
        }
        remHTJ(nome, HT_jogos, HT_tam); /*Remove-se da hashtable*/
        rm_jogo(jogos, jogo);           /*Remove-se da lista ligada*/
    }
    else /*Caso o jogo a ser removido nao exista no sistema*/
    {
        printf("%d Jogo inexistente.\n", NL);
    }
}
/*Lista todos os jogos do sistema por odem de introducao*/
void lista_jogos(int NL, list_jogos *jogos)
{
    jogo *jogo;
    /*Percorre a lista ligada*/
    for (jogo = jogos->head; jogo; jogo = jogo->next)
    {
        printf("%d ", NL);
        printf("%s ", jogo->nome);
        printf("%s ", jogo->e1);
        printf("%s ", jogo->e2);
        printf("%d ", jogo->score1);
        printf("%d\n", jogo->score2);
    }
}
/*Verifica se um jogo esta presente no sistema*/
void procura_jogo(int NL, HT_jogos *HT, int HT_tam)
{
    char nome[1023];
    jogo *jogo;

    scanf(" %[^\n]", nome);
    jogo = searchJogo(nome, HT, HT_tam);
    if (jogo != NULL) /*Se o jogo existir*/
    {
        printf("%d ", NL);
        printf("%s ", jogo->nome);
        printf("%s ", jogo->e1);
        printf("%s ", jogo->e2);
        printf("%d ", jogo->score1);
        printf("%d\n", jogo->score2);
    }

    else /*Se o jogo nao estiver registado no sistema*/
        printf("%d Jogo inexistente.\n", NL);
}
/*Funcao que altera o resultado de uma partida registada anteriormente no sistema*/
void altera_score(int NL, HT_jogos *HT_jogos, HT_equipas *HT_equipas, int HT_tam)
{
    char nome[1023];
    int s1, s2;
    jogo *jogo;
    equipa *equipa1, *equipa2;
    memset(nome, 0, 1023);

    scanf(" %[^:]s:", nome);
    scanf(":%d:%d", &s1, &s2);

    jogo = searchJogo(nome, HT_jogos, HT_tam);

    if (jogo) /*Se o jogo existir*/
    {
        equipa1 = searchEquipa(jogo->e1, HT_equipas, HT_tam);
        equipa2 = searchEquipa(jogo->e2, HT_equipas, HT_tam);
        /*Reduz-se o numero de partidas ganhas da equipa que tinha ganho anteriormente*/
        if (jogo->score1 > jogo->score2)
        {
            equipa1->jogos_ganhos -= 1;
        }
        if (jogo->score1 < jogo->score2)
        {
            equipa2->jogos_ganhos -= 1;
        }
        /*Verifica-se qual equipa ganha com o novo score introduzido e incrementa-se o numero de jogos ganhos da mesma*/
        if (s1 > s2)
            equipa1->jogos_ganhos += 1;
        if (s1 < s2)
            equipa2->jogos_ganhos += 1;

        jogo->score1 = s1;
        jogo->score2 = s2;
    }
    else /*Se o jogo nao estiver no sistema*/
        printf("%d Jogo inexistente.\n", NL);
}