#ifndef _FUNCOES_MAIN_
#define _FUNCOES_MAIN_

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "Listas_ligadas.h"
#include "Listas_ligadas2.h"
#include "FUNCOES_AUX.h"

/*
A funcao A recebe o nome de uma equipa, a lista de vitorias e a array de valores e chamada a funcao
adiciona_eq para ver se a equipa ja se encontra na lista de vitorias, caso se encontre e atribuido
0 a variavel check e e adicionada a equipa a lista de equipas, senao e atribuido 1 e e feito
print de um erro significando que a equipa ja se encontra na lista de vitorias.
*/

void A(char nome[],link_v* head2,int valores[])
{
    int check;
    check = adiciona_eq(nome,&*head2,valores);
    if (check == 1)
        printf("%d Equipa existente.\n",valores[1]);
    
}

/*
A funcao A recebe o nome de um jogo, as equipas, as pontuacoes e a array de valores, e chamada a 
funcao adiciona_jog para ver se o jogo ja se encontra na lista de jogos, e se as equipas se 
encontram na lista de vitorias (sendo feito print de um caso nao se encontrem), caso o jogo nao 
se encontre e atribuido 0 a variavel check e e adicionado o jogo a lista de jogos, senao e 
atribuido 1 e e feito print de um erro significando que o jogo ja se encontra na lista de jogos.
*/

void a(link* head,char nome[],int valores[],link_v* head2, char team1[],char team2[],
int pont1,int pont2)
{
    int check;
    check = adiciona_jog(&*head,nome,team1,team2,pont1,pont2,&*head2,valores);
    if (check == 1)
        printf("%d Jogo existente.\n",valores[1]);
}

/*
A funcao r recebe o nome de um jogo, a array de valores e as listas de jogos e vitorias, e
e chamada a funcao remove_jog  
*/

void r(char nome[],link* head,link_v* head2,int valores[])
{
    int check;
    check = remove_jog(&*head,nome,&*head2);
    if (check == 0)
        printf("%d Jogo inexistente.\n",valores[1]);
}

/*
A funcao s recebe o nome de um jogo e as listas de vitorias e jogos e a pontucao a alterar
e verifica se o nome se encontra na lista de jogos (caso nao se encontre e devolvido 0),
apos isso e chamada a funcao altera_jog e sao feitas as atribuicoes das respetivas vitorias 
e e alterada a pontuacao desse jogo sendo devolvido 1, sendo 0 ou 1 atribuido a varivel check.
*/

void s(link* head,char nome[],int pont1,int pont2,link_v* head2,int valores[])
{
    int check;
    check = altera_jog(*head,nome,pont1,pont2,*head2);
    if (check == 0)
        printf("%d Jogo inexistente.\n",valores[1]);
}

/*
A funcao P recebe o nome de uma equipa, a array de valores e a lista de vitorias e verifica se 
ele se encontra na lista de vitorias (caso nao se encontre e devolvido 1) e atribuido esse valor a
vraivel check originando um erro, senao e atribuido 1 e feito print da linhado stdin do comando, do
seu nome e o numero de vitorias.
*/

void P(link_v* head2,char nome[],int valores[])
{
    int check;
    check = print_vit(*head2,nome,valores);
    if (check == 0)
        printf("%d Equipa inexistente.\n",valores[1]);
}

/*
A funcao p recebe o nome de um jogo, a array de valores e a lista de jogos e verifica se 
ele se encontra na lista de jogos (caso nao se encontre e devolvido 1) e atribuido esse valor a
vraivel check originando um erro, senao e atribuido 1 e feito print da linhado stdin do comando,
do nome do jogo, das equipas e da pontuacao do jogo.
*/

void p(link* head,char nome[],int valores[])
{
    int check;
    check = print_jog(*head,nome,valores);
    if (check == 0)
        printf("%d Jogo inexistente.\n",valores[1]);
}

/*
A funcao g e recebe uma lista de vitorias e a array de valores e outra array de valores2 que
guarda o tamanho da lista de vitorias e a vitoria maxima, depois e aplicada
a funcao procura vit max para encontrar o numero maximo de vitorias e o len da lista, de modo,
a obter o tamanho da lista de vitorias e se a lista nao for vazia e feita a sua ordenacao 
(caso a o comando g nao tenha sido chamado antes ou caso nao tenha sido adicionada uma nova equipa)
e print da lista ordenada, no final e atribuido 0 ao tamanho da lista de vitorias e a vitoria
maxima, dado que a lista ja foi processada.
*/

void g(link_v* head2,int valores[],int val2[])
{
    procura_vit_max(*head2,val2);
    if (val2[1] > 0)
    {
        printf("%d Melhores %d\n",valores[1],val2[0]);
        if (valores[3] == 0)
            MergeSort(&*head2);
        print_lista_v(*head2,valores,val2[0]);
        valores[3] = 1;
    }
    val2[0] = 0;
    val2[1] = 0;
}

#endif