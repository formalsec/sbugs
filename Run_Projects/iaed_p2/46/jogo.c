#include <stdio.h>
#include "jogo.h"
#include <stdlib.h>
#include <string.h>


int hash(char *v, int M){
    /*Funcao recebe um nome e identifica na tabela de dispersao o endereco*/

    int h = 0, a = 127;

    for (; *v != '\0'; v++)
    h = (a*h + *v) % M;
    return h;
}

linkJogo ProcuraJHash(linkJogo *tab, char *v){
    /*Funcao recebe um nome de um jogo e acede a tabela de dispersao*/

    int i;
    linkJogo j;

    i = hash(v, hashM);
    if(tab[i]!= NULL) j = tab[i];
    else return NULL; /*acesso vazio*/

    while(j != NULL){
        if ( strcmp(j->jogo->nome, v) == 0) return j;/*caso encontre*/
        
        j = j->nextHash;
    }

    return NULL;/*caso depois da pesquisa nao encontrar o nome*/
}


linkJogo NovoJogo(char* nome, char* equipa1, char* equipa2, int score1, int score2){
    /*Funcao recebe um nome e cria um novo jogo alocando memoria dinamicamente*/
    linkJogo x;
    Jogo *j = (Jogo*) malloc(sizeof(Jogo));

    /*Novo node do tipo "jogo"*/
    x  = (linkJogo) malloc(sizeof(struct Jogo_Node));

    /*inicializa variaveis*/
    j->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(j->nome , nome);

    j->equipa1 = (char*) malloc(sizeof(char)*(strlen(equipa1)+1));
    strcpy(j->equipa1, equipa1);

    j->equipa2 = (char*) malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(j->equipa2, equipa2);

    j->score1 = (int*) malloc(sizeof(int));
    *(j->score1) = score1;

    j->score2 = (int*) malloc(sizeof(int));
    *(j->score2) = score2;

    x->jogo = j;

    x->nextHash = NULL;
    x->nextList = NULL;

    return x;
}


void InserirJogo(linkJogo *pheadj,linkJogo *ptailj, linkJogo *tabJogos, linkJogo j){
    /*Funcao insere um novo jogo na estrutura*/
    int i;

    /*Posiciona o jogo na tabela de dispersao*/
    i = hash(j->jogo->nome, hashM);

    if(tabJogos[i] != NULL){
        j->nextHash = tabJogos[i];
    }
    tabJogos[i] = j;

    /*Posiciona o jogo na lista*/
    if (*pheadj == NULL){ *pheadj = j;}
    if(*ptailj != NULL){(*ptailj)->nextList = j;}
    *ptailj = j;/*caso seja o primeiro jogo*/
}

void RemoverJogo(linkJogo *pheadj, linkJogo *ptailj, linkJogo *tabJogos, linkJogo j){
    /*Funcao recebe um jogo e retira-o da estrutura*/
    linkJogo auxL, auxH;
    int i=0;

    /*Reorganizacao ao retirar o jogo*/
    if (j == *pheadj && j == *ptailj){/*caso seja o unico*/
        *pheadj = NULL;
        *ptailj = NULL;
    }
    else if (j == *pheadj){/*caso seja o primeiro*/
        *pheadj = j->nextList;
    }
    else{
        auxL = *pheadj;
        while(auxL->nextList != j)
            auxL = auxL->nextList;
        auxL->nextList = j->nextList;
        if (j == *ptailj) *ptailj = auxL;
    }
    
    /*Reorganizacao da tabela de dispersao ao retirar o jogo*/
    i = hash(j->jogo->nome, hashM);

    if (tabJogos[i] == j)
        tabJogos[i] = j->nextHash;

    else{
        auxH = tabJogos[i];
        while (auxH->nextHash != j)
            auxH = auxH->nextHash;
        auxH->nextHash = j->nextHash;
    }

    /*Libertar a memoria alocada para o jogo a retirar*/
    freeJogo(j->jogo);
    free(j);


}

void freeJogo(Jogo *j){
    /*Funcao liberta a memoria dinamicamente alocada para um jogo*/
    free(j->nome);
    free(j->equipa1);
    free(j->equipa2);
    free(j->score1);
    free(j->score2);
    free(j);
}

void freeLinkJogo(linkJogo j){
    /*Funcao liberta a memoria dinamicamente alocada para um 
    encadeamento (lista) de nodes de jogos, recursivamente*/
    if (j->nextList != NULL)
        freeLinkJogo(j->nextList);
    freeJogo(j->jogo);
    free(j);
}
