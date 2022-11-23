#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#include "proj2_aux.h"
#include "proj2_comandos.h"

/*Comando a - Adiciona um novo jogo ao sistema.*/
void a(int NL,char *atr1,char *atr2,char *atr3,char *atr4,char *atr5,Lista_jogos_equipas *lje){
    Equipa *equipa_1, *equipa_2;
    Jogo *novo_jogo;
    int posicao = hash(atr1);
    if(procura_nome_jogo(lje, atr1) != NULL){   /*Caso o jogo ja exista, imprime*/
        printf("%d Jogo existente.\n", NL);     /*o erro e retorna.*/
        return;
    }
    equipa_1= procura_nome_equipa(lje, atr2);
    equipa_2= procura_nome_equipa(lje, atr3);
    if(equipa_1 == NULL || equipa_2 == NULL){   /*Caso uma das equipas nao exista,*/
        printf("%d Equipa inexistente.\n", NL); /*imprime o erro e retorna.*/
        return;
    }
    novo_jogo= adiciona_jogo(atr1, equipa_1, equipa_2, atr4, atr5);
    if(lje->primeiro_jogo == NULL){       /*Altera os ponteiros necessarios de acordo*/
        lje->primeiro_jogo= novo_jogo;    /*com a ordem de introducao os jogos.*/
    }
    else{
        novo_jogo->jogo_anterior= lje->ultimo_jogo;
        lje->ultimo_jogo->jogo_seguinte= novo_jogo;
    }
    lje->ultimo_jogo= novo_jogo;
    if(lje->tab_jogo[posicao]->primeiro_jogo == NULL){
        lje->tab_jogo[posicao]->primeiro_jogo= novo_jogo;
    }
    else{
        novo_jogo->anterior_tabela= lje->tab_jogo[posicao]->ultimo_jogo;
        lje->tab_jogo[posicao]->ultimo_jogo->prox_tabela= novo_jogo;
    }
    lje->tab_jogo[posicao]->ultimo_jogo= novo_jogo;
    if(novo_jogo->score1 > novo_jogo->score2){  /*Adiciona uma vitoria a equipa que ganhou o jogo.*/
        novo_jogo->equipa1->vitorias +=1;
    }
    else if(novo_jogo->score2 > novo_jogo->score1){
        novo_jogo->equipa2->vitorias +=1;
    }
}

/*Comando A - Adiciona uma nova equipa ao sistema.*/
void A(int NL,char *atr1,Lista_jogos_equipas *lje){
    Equipa *nova_equipa;
    int posicao = hash(atr1);
    if(procura_nome_equipa(lje, atr1) != NULL){ /*Caso a equipa ja exista, imprime*/
        printf("%d Equipa existente.\n", NL);   /*o erro e retorna.*/
        return;
    }
    nova_equipa = adiciona_equipa(atr1);
    if(lje->primeira_equipa == NULL){       /*Altera os ponteiros necessarios de acordo*/
        lje->primeira_equipa = nova_equipa; /*com a ordem de introducao das equipas.*/
    }
    else{
        lje->ultima_equipa->equipa_seguinte= nova_equipa;
    }
    lje->ultima_equipa = nova_equipa;
    if(lje->tab_equipa[posicao]->primeira_equipa == NULL){
        lje->tab_equipa[posicao]->primeira_equipa= nova_equipa;
    }
    else{
        lje->tab_equipa[posicao]->ultima_equipa->prox_tabela = nova_equipa;
    }
    lje->tab_equipa[posicao]->ultima_equipa = nova_equipa;
}

/*Comando l - Lista todos os jogos existentes no sistema pela ordem em que foram introduzidos.*/
void l(int NL, Lista_jogos_equipas *lje){
    Jogo *jogo= lje->primeiro_jogo;
    while(jogo != NULL){
        printf("%d %s %s %s %d %d\n", NL, jogo->nome,
        jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
        jogo= jogo->jogo_seguinte;
    }
}

/*Comando p - Procura um jogo dado um nome.*/
void p(int NL, char *atr1, Lista_jogos_equipas *lje){
    Jogo *jogo= procura_nome_jogo(lje, atr1);
    if(jogo == NULL){   /*Caso o jogo nao exista, imprime o erro.*/
        printf("%d Jogo inexistente.\n", NL);
    }
    else{   /*Caso o jogo exista, imprime o mesmo.*/
        printf("%d %s %s %s %d %d\n", NL, jogo->nome,
        jogo->equipa1->nome, jogo->equipa2->nome, jogo->score1, jogo->score2);
    }
}

/*Comando P - Procura uma equipa dado um nome.*/
void P(int NL, char *atr1, Lista_jogos_equipas *lje){
    Equipa *equipa= procura_nome_equipa(lje,atr1);
    if (equipa == NULL){   /*Caso a equipa nao exista, imprime o erro.*/
        printf("%d Equipa inexistente.\n", NL);
    }
    else{   /*Caso a equipa exista, imprime a mesma.*/
        printf("%d %s %d\n", NL, equipa->nome, equipa->vitorias);
    }
}

/*Comando r - Apaga um jogo dado um nome.*/
void r(int NL, char *atr1, Lista_jogos_equipas *lje){
    Jogo *jogo;
    int posicao = hash(atr1);
    jogo= procura_nome_jogo(lje, atr1);     /*Encontra o jogo a eliminar.*/
    if(jogo == NULL){   /*Caso o jogo nao exista, imprime o erro e retorna.*/
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    if(lje->primeiro_jogo == jogo){     /*Altera os ponteiros necessarios para o jogo*/
        if(lje->ultimo_jogo == jogo){   /*deixar de estar na lista e na tabela.*/
            lje->primeiro_jogo = NULL;
            lje->ultimo_jogo = NULL;
        }
        else{
            jogo->jogo_seguinte->jogo_anterior= NULL;
            lje->primeiro_jogo= jogo->jogo_seguinte;
        }
    }
    else if(lje->ultimo_jogo == jogo){
        jogo->jogo_anterior->jogo_seguinte= NULL;
        lje->ultimo_jogo = jogo->jogo_anterior;
    }
    else{
        jogo->jogo_anterior->jogo_seguinte = jogo->jogo_seguinte;
        jogo->jogo_seguinte->jogo_anterior = jogo->jogo_anterior;
    }
    if(lje->tab_jogo[posicao]->primeiro_jogo == jogo){
        if(lje->tab_jogo[posicao]->ultimo_jogo == jogo){
            lje->tab_jogo[posicao]->primeiro_jogo= NULL;
            lje->tab_jogo[posicao]->ultimo_jogo= NULL;
        }
        else{
            jogo->prox_tabela->anterior_tabela= NULL;
            lje->tab_jogo[posicao]->primeiro_jogo = jogo->prox_tabela;
        }
    }
    else if(lje->tab_jogo[posicao]->ultimo_jogo == jogo){
        jogo->anterior_tabela->prox_tabela= NULL;
        lje->tab_jogo[posicao]->ultimo_jogo = jogo->anterior_tabela;
    }
    else{
        jogo->anterior_tabela->prox_tabela= jogo->prox_tabela;
        jogo->prox_tabela->anterior_tabela= jogo->anterior_tabela;
    }
    if(jogo->score1 > jogo->score2){        /*Retira uma vitoria a equipa que tinha ganho o jogo.*/
        jogo->equipa1->vitorias -= 1;
    }
    else if(jogo->score2 > jogo->score1){
        jogo->equipa2->vitorias -= 1;
    }
    free(jogo->nome);   /*Liberta a memoria alocada na criacao do jogo.*/
    free(jogo);
}

/*Comando s - Altera o score de um jogo dado um nome.*/
void s(int NL, char *atr1, char *atr2, char*atr3, Lista_jogos_equipas *lje){
    Jogo *jogo= procura_nome_jogo(lje, atr1);
    if(jogo == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    if(jogo->score1 > jogo->score2){    /*Tira uma vitoria a equipa que tinha ganho o jogo com*/
        jogo->equipa1->vitorias -= 1;   /*os scores antigos.*/
    }
    else if(jogo->score2 > jogo->score1){
        jogo->equipa2->vitorias -= 1;
    }
    jogo->score1= atoi(atr2);      /*Altera os scores do jogo.*/
    jogo->score2= atoi(atr3);
    if(jogo->score1 > jogo->score2){    /*Adiciona uma vitoria a equipa que ganhou o jogo*/
        jogo->equipa1->vitorias += 1;   /*com os scores novos.*/
    }
    else if(jogo->score2 > jogo->score1){
        jogo->equipa2->vitorias += 1;
    }
}

/*Comando g - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica
do nome da equipa.*/
void g(int NL, Lista_jogos_equipas *lje){
    Tabela_equipas *max_vitorias;
    int num_max_vitorias;
    num_max_vitorias= procura_max_vitorias(lje);
    max_vitorias= procura_equipa_vitorias(lje, num_max_vitorias);
    ordena_equipa_vitorias(max_vitorias, NL, num_max_vitorias);
}