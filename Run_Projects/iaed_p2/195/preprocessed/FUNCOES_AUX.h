#ifndef _FUNCOES_AUX_
#define _FUNCOES_AUX_

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "Listas_ligadas.h"
#include "Listas_ligadas2.h"

/*
A funcao equipa_in recebe uma string (que corresponde a uma equipa) e faz uma pesquisa linear,
usando um ciclo for, de modo, a encontar a equipa pretendida. Se o haver uma equipa com o mesmo
nome que a string recebida, a funcao devolve 1 (significando que foi encontrado), senao devolve 0
(significando que nao foi encontrado).
*/

int equipa_in(link_v head, char nome[])
{
    link_v t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->v.nome,nome) == 0)
            return 1;
    return 0;
}

/*
A funcao remove espaco recebe uma string como argumento e se o 1o char for um espaco ela percorre
um ciclo for em que todas as posicoes da array sao puxadas uma posicao para tras ficando com a
string sem o espaco no inicio.
*/

void remove_esp(char str[])
{
    if (str[0] == ' ')
    {
        int i;
        for (i = 0; str[i] != '\0'; ++i)
            str[i] = str[i + 1];
    }
}

/*
A funcao atribui_vit recebe uma array de vitorias, as respetivas equipas e a pontuacao desse jogo
e faz os casos de atribuicao possiveis quando se adiciona um jogo (usado na funcao a).
*/

void atribui_vit(char team1[],char team2[],int score1,int score2,link_v conj_vit)
{
    link_v win;
    if (score1 > score2)
    {
        win = lookup_v(conj_vit,team1);
        win->v.vit++;
    }
    else if (score1 < score2)
    {
        win = lookup_v(conj_vit,team2);
        win->v.vit++;
    }
}

/*
A funcao print_jog faz uma pesquisa linear usando um ciclo for ate encontrar o nome pretendido na
linked list de jogos.
Ao encontra-lo imprime a linha do stdin, o nome, as equipas, e a pontucao desse respetivo jogo.
*/

int print_jog(link head, char nome[],int valores[])
{
    link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->game.nome,nome) == 0)
        {
            printf("%d %s %s %s %d %d\n",valores[1],t->game.nome,t->game.equipas[0],
            t->game.equipas[1],t->game.pont[0],t->game.pont[1]);
            return 1;
        }
    return 0;
}

/*
A funcao print_vit faz uma pesquisa linear usando um ciclo for ate encontrar a equipa pretendida na
linked list de vitorias.
Ao encontra-la imprime a linha do stdin, o seu nome, as equipas e o numero de vitorias.
*/

int print_vit(link_v head, char nome[],int valores[])
{
    link_v t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->v.nome,nome) == 0)
        {
            printf("%d %s %d\n",valores[1],t->v.nome,t->v.vit);
            return 1;
        }
    return 0;
}

/*
A funcao atribui_vit2 recebe as respetivas equipas, a pontuacao antiga desse jogo e a pontuacao a
atribuir a esse jogo e faz os casos de atribuicao possiveis quando se altera a pontuacao de um jogo
(usado na funcao s).
*/

void atribui_vit2(char team1[],char team2[],int score1_old,int score2_old,int score1,int score2,
link_v conj_vit)
{
    link_v win,loss;
    if (score1_old > score2_old && score1 == score2)
        {
            win = lookup_v(conj_vit,team1);
            win->v.vit--;
        }
    else if (score1_old > score2_old && score1 < score2)
        {
            loss = lookup_v(conj_vit,team1);
            win = lookup_v(conj_vit,team2);
            loss->v.vit--;
            win->v.vit++;
        } 
    else if (score1_old == score2_old && score1 > score2)
        {
            win = lookup_v(conj_vit,team1);
            win->v.vit++;
        }
    else if (score1_old == score2_old && score1 < score2)
        {
            win = lookup_v(conj_vit,team2);
            win->v.vit++;
        }
    else if (score1_old < score2_old && score1 > score2)
        {
            win = lookup_v(conj_vit,team1);
            loss = lookup_v(conj_vit,team2);
            win->v.vit++;
            loss->v.vit--;
        }
    else if (score1_old < score2_old && score1 == score2)
        {
            win = lookup_v(conj_vit,team2);
            win->v.vit--;
        }
}

/*
A funcao procura_vit faz uma pesquisa linear, usando um ciclo for, de modo, a encontar o maior 
numero de vitorias de qualquer equipa, devolvendo o repestivo numero no final.
*/

void procura_vit_max(link_v head,int val2[])
{
    link_v t;
    for(t = head; t != NULL; t = t->next){
        val2[1]++;
        if (t->v.vit > val2[0])
        {
            val2[0] = t->v.vit;
        }
    }
}


/*A funcao MergeSort aplica o algortimo de ordenacao MergeSort na lista de strings.*/

void MergeSort(struct node_v** headRef)
{ 
    struct node_v* head = *headRef; 
    struct node_v* a; 
    struct node_v* b; 
  
    /* Caso base -- comprimento 0 ou 1 */
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    /* Separa a head em duas sublistas 'a' e 'b'*/
    FrontBackSplit(head, &a, &b); 
  
    /* Ordena recursivamente as sublistas */
    MergeSort(&a); 
    MergeSort(&b); 
  
    /* resposta = juntar as duas sublistas */
    *headRef = SortedMerge(a, b); 
} 

struct node_v* SortedMerge(struct node_v* a, struct node_v* b)
{ 
    struct node_v* result = NULL; 
  
    /* Casos base */
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    /* Escolhe a ou b e faz recursao */
    if (strcmp(a->v.nome,b->v.nome) <= 0) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 

void FrontBackSplit(struct node_v* source, 
                    struct node_v** frontRef, struct node_v** backRef) 
{ 
    struct node_v* fast; 
    struct node_v* slow; 
    slow = source; 
    fast = source->next; 
  
    /* avanca 'fast' dois nodos, e avanca 'slow' um nodo */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    /* 'slow' esta antes do meio da lista, entao nesse ponto separa em dois. */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

/*
A funcao altera_jog recebe as listas de jogos e vitorias, as pontuacoes e o nome do jogo a
alterar, apos isso e feita uma pesquisa linear apartir de um ciclo for, de modo a encontar o
jogo, caso se encontre as respetivas atribuicoes sao feitas e devolvido 1 (significando que
o jogo foi alterado com sucesso),senao devolve 0 (significando que o jogo nao se encontra na lista)
*/

int altera_jog(link head,char nome[],int pont1,int pont2,link_v head2)
{
    link t;
    for(t = head; t != NULL; t = t->next)
    {
        if(strcmp(t->game.nome,nome) == 0)
        {
            atribui_vit2(t->game.equipas[0],t->game.equipas[1],t->game.pont[0],
            t->game.pont[1],pont1,pont2,head2);
            t->game.pont[0] = pont1;
            t->game.pont[1] = pont2;
            return 1;
        }
    }
    return 0;
}

/*A funcao remove_jog recebe a lista de jogos, o nome do jogo, e lista de vitorias, e chamda
a funcao lookup_jog, de modo, a encontar o jogo a ser removido, apos isso faz as respetivas
atribuicoes para o caso de um jogo ser removido, remove o nodo do jogo da lista de jogos
e devolve (significando que o jogo foi removido com sucesso), senao devolve 0 
(significando que o jogo nao se encontra na lista)*/

int remove_jog(link *head,char nome[],link_v *head2)
{
    link win = lookup_jog(*head,nome);
    if (win != NULL)
    {
        if (win->game.pont[0] > win->game.pont[1])
        {
            link_v team_w = lookup_v(*head2,win->game.equipas[0]);
            team_w->v.vit--;
        }
        else if (win->game.pont[0] < win->game.pont[1])
        {
            link_v team_w = lookup_v(*head2,win->game.equipas[1]);
            team_w->v.vit--;
        }
        *head = delete_el_jog(*head,nome);
        return 1;
    }
    return 0;
}

/*A funcao adiciona_eq recebe o nome de uma equipa e a array de valores, e feita a verificacao
se o jogo se encontra na lista de vitorias (devolvendo 1 caso se encontre), senao insere o jogo
na lista de vitorias e declara a flag de controlo valores[3] como 0 e devolve 0.*/

int adiciona_eq(char nome[],link_v* head,int valores[])
{
    link_v t;
    for(t = *head; t != NULL; t = t->next){
        if(strcmp(t->v.nome,nome) == 0)
            return 1;
    }
    *head = insertEnd_v(*head,nome,valores);
    valores[3] = 0;
    return 0;
}

/*A funcao adiciona_jog recebe o nome de um jogo, as equipas, as pontuacoes e a array de valores,
e procura o jogo na lista de jogos (devolvendo 1 caso se encontre), senao depois verifica se as
equipas se encontram na lista de vitorias (devolvendo 2 e fazendo print de um erro).

Caso as condicoes atras sejam cumpridas e inserido o jogo na lista de jogos e atribui-se a vitoria
a equipa vencedora atraves da funcao atribui_vit (caso haja uma equipa vencedora senao nao se faz
nada) e devolvendo-se 0 no final.*/

int adiciona_jog(link *head,char nome[],char team1[],char team2[],int pont1,int pont2,link_v *head2,int valores[])
{
    link t;
    for(t = *head; t != NULL; t = t->next)
    {
        if(strcmp(t->game.nome,nome) == 0)
        {
            return 1;
        }
    }
    if ((equipa_in(*head2,team1) == 0) || (equipa_in(*head2,team2) == 0))
    {
        printf("%d Equipa inexistente.\n",valores[1]);
        return 2;
    }
    else
    {
        *head = insertEnd_jog(*head,nome,team1,team2,pont1,pont2,valores);
        atribui_vit(team1,team2,pont1,pont2,*head2);   
        return 0;
    }
}

#endif