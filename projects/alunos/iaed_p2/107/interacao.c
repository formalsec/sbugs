#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "interacao.h"

/*Le duas equipas, um nome para um jogo e os scores e adiciona aos 
jogos jogados caso as equipas existam e o jogo nao existir. Nao retorna nada*/
void novo_jogo(no_equipa *tabela_equipas[],lista_jogos **fila_jogos,no_jogo_tabela *tabela_jogos[],int linha){
    char nome[MAX_NOME],equipa1[MAX_NOME];
    char equipa2[MAX_NOME];
    int score1,score2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);
    /*existe o jogo e as equipas?*/
    if(procura_jogo_lista(tabela_jogos,nome)){
        /*o jogo existe logo imprime erro*/
        printf("%d Jogo existente.\n",linha);
        return;
    }
    if(!procura_equipa_lista(tabela_equipas,equipa1) || 
    !procura_equipa_lista(tabela_equipas,equipa2)){
        /*uma das equipas nao existe logo imprime erro*/
        printf("%d Equipa inexistente.\n",linha);
        return;
    }
    /*nao havendo erros, adiciona o jogo*/
    adiciona_jogo(tabela_equipas,fila_jogos,tabela_jogos,nome,equipa1,equipa2,score1,score2); 
}

/*Le um nome de um jogo e procura-o. Caso este exista imprime as suas informacoes,
caso contrario imprime um erro. Nao retorna nada*/
void procura_jogo(no_jogo_tabela *tabela_jogos[],int linha){
    char nome[MAX_NOME];
    no_jogo_tabela *alvo;
    scanf("  %[^:\n]",nome);
    alvo = procura_jogo_lista(tabela_jogos,nome);
    if(alvo) /*existe?*/
        printf("%d %s %s %s %d %d\n",linha,alvo->jogo1.nome,alvo->jogo1.equipa1,alvo->jogo1.equipa2,alvo->jogo1.score1,alvo->jogo1.score2);
    else
    {    /*nao existe imprime erro*/
        printf("%d Jogo inexistente.\n",linha);
    }
}

/*Le um nome de um jogo e apaga-o caso este exista. Caso contrario imprime um erro.
Nao retorna nada*/
void apaga_jogo_alvo(no_equipa  *tabela_equipas[],no_jogo_tabela *tabela_jogos[], lista_jogos **fila_jogos,int linha){
    char nome[MAX_NOME];
    scanf(" %[^:\n]",nome); /*existe?*/
    if(!procura_jogo_lista(tabela_jogos,nome)){
        printf("%d Jogo inexistente.\n",linha);
        return;
    }
    /*existe logo apaga-o*/  
    apaga_jogo(tabela_equipas,fila_jogos,tabela_jogos,nome);
}

/*Le o nome de um jogo, e dois novos scores e altera os scores
do jogo correspondente ao nome lido se este existir. Caso contrario imprime
um erro. Nao retorna nada*/
void altera_score_jogo(no_jogo_tabela *tabela_jogos[],no_equipa  *tabela_equipas[],int linha){
    char nome[MAX_NOME];
    int score1,score2;
    scanf(" %[^:\n]:%d:%d",nome,&score1,&score2);
    if(!procura_jogo_lista(tabela_jogos,nome)){ /*nao existe?*/
         printf("%d Jogo inexistente.\n",linha);
         return;
    }
    /*existe, logo altera o score*/
    altera_score(tabela_equipas,tabela_jogos,nome,score1,score2);
}

/*Le um nome de uma equipa e adiciona-a as equipas existentes caso esta 
ainda nao tenha sido adicionada. Caso contrario, imprime um erro.
Nao retorna nada*/
void adiciona_equipa_alvo(no_equipa  *tabela_equipas[],int linha,int *numero_equipas){
    char nome[MAX_NOME];
    scanf(" %[^:\n]",nome);
    /*ja existe a equipa?*/
    if(procura_equipa_lista(tabela_equipas,nome)){
         /*entao imprime o erro*/
        printf("%d Equipa existente.\n",linha);
        return;
    }
    /*nao existe logo adiciona-a*/
    adiciona_equipa(tabela_equipas,nome,numero_equipas);
}

/*Le o nome de uma equipa e procura-a na tabela de equipas, imprimindo
as suas informacoes caso exista. Caso contrario, imprime um erro.
Nao retorna nada*/
void procura_equipa(no_equipa  *tabela_equipas[],int linha){
    char nome[MAX_NOME];
    equipa *alvo;
    scanf(" %[^:\n]",nome);
    alvo = procura_equipa_lista(tabela_equipas,nome);
    if(alvo){ 
        /*a equipa existe logo imprime-a*/
        printf("%d %s %d\n",linha,alvo->nome,alvo->vitorias);
    }
    else
    {   
        /*nao existe logo imprime o erro*/
        printf("%d Equipa inexistente.\n",linha);
    }
}

