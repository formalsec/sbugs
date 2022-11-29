#ifndef AUXILIARES_H
#define AUXILIARES_H
#include "jogos.h"
#include "equipas.h"
/*Valor que significa empate num jogo.*/
#define EMPATE 0
/*Valor que significa vitoria da equipa1 num jogo.*/
#define VIT1 1
/*Valor que significa vitoria da equipa2 num jogo.*/
#define VIT2 2
/*Tamanho do espaco reservado para armazenar strings recebidas 
em scanf's antes de estas serem avaliadas e ser reservado 
apenas o espaco necessario para as mesmas.*/
#define MAX 1093
/*Valor que indica a funcao aumenta para inicializar um armazenador.*/
#define INI 3
/*Valor que indica a funcao aumenta para incrementar o parametro cont.*/
#define INC 4


typedef struct armazena{
    /*cont conta e armazena o numero de linhas do input que o programa recebe.*/
    int cont;
    /*max_vit armazena o maior numero de vitorias conseguidas por uma equipa.*/
    int max_vit;
} arm;
typedef arm* hptr;

/*Funcao vencedor recebe dois inteiros, e compara-os de forma a concluir se se tratam de 
um empate ou uma vitoria, para uma das equipas, devolvendo um valor respetivo a cada um 
dos casos.*/
int vencedor(int p1, int p2);

/*Funcao vitorias recebe o nome de duas equipas e um resultado de um jogo, e calcula qual o 
vencedor, aumentando o numero de vitorias da respetiva equipa.*/
void vitorias(linkE head, int p1, int p2, char *equipa_1, char *equipa_2, hptr *h1);

/*Funcao retira_pontos recebe um jogo e uma lista de NodesEquipa, e retira pontos a uma 
equipa quando ha alteracao num resultado de um jogo, ou este e eliminado.*/
void retira_pontos(linkJ jogo, linkE headE, hptr *h1);

/*Funcao SelectionSort recebe um vetor de ponteiros para palavras e ordena-o de forma
a deixar as palavras por ordem alfabetica.*/
void SelectionSort(char **nomes, int left, int right);

/*A funcao aumenta recebe um ponteiro para um armazenador e um numero de controlo:
se este for 0, ela inicia uma estrutura do tipo armazenador;
se for diferente de 0, ele apenas incrementa o contador de linhas de input.*/
void aumenta(hptr* pt, int n);

#endif