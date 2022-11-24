#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geral.h"
#include "structs.h"

/*-----------------------REFERENTES AO COMANDO a-----------------------*/

pJogo cria_jogo(char *buffer, char *team1,char *team2,int s1,
 int s2,table_eq tab_eq) 
{
    pJogo match;
    /*alocacoes de memoria necessarias ah criacao do novo jogo match*/
    match = (pJogo)can_fail_malloc(sizeof(struct game));
    
    match->nome = can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(match->nome, buffer);

    match->equipa1 = can_fail_malloc(sizeof(char)*(strlen(team1)+1));
    strcpy(match->equipa1, team1);

    match->equipa2 = can_fail_malloc(sizeof(char)*(strlen(team2)+1));
    strcpy(match->equipa2, team2);
    
    match->score1 = s1;
    match->score2 = s2;


    if (s1>s2) {
        match->winner = can_fail_malloc(sizeof(char)*(strlen(team1)+1));
        strcpy(match->winner, team1);
        SearchEquipa(match->winner,tab_eq)->vitorias++;
    }
    else if (s2 > s1) {
        match->winner = can_fail_malloc(sizeof(char)*(strlen(team2)+1));
        strcpy(match->winner, team2);
        SearchEquipa(match->winner,tab_eq)->vitorias++;
    }
    else {
        /*em caso de empate as vitorias mantem-se e nao existe nenhum
        vencedor*/
        match->winner = NULL;
    }
    return match;
}

/*adiciona ao final da lista de jogos um novo jogo, deste modo
 sera mais facil de ordenar no comando 'l'*/
void add_last(listagem l,pJogo match)
{
    match->next = NULL;
    match->previous = l->tail;
    if (l->tail != NULL) {
        l->tail->next = match;
    }
    l->tail=match;
    /*caso do primeiro jogo inserido*/
    if (l->head == NULL) {
        l->head = match;
    }
}

/*funcoes de insercao de um jogo na hash table dos jogos*/

Node_jogos InsertBeginJogo(Node_jogos head, pJogo match)
{
    Node_jogos old_head=head;
    head=(Node_jogos)can_fail_malloc(sizeof(struct node_jogo));
    head->next=old_head;
    head->match=match;
    return head;
}

void InsertJogo(pJogo match,table_jogos table)
{
    /*i sera o indice da hash table onde vai ser colocado o 
    jogo, isto eh, este indice corresponde a uma lista simplesmente
    ligada onde o jogo sera inserido no inicio da mesma*/
    int i = hash_jogos(match->nome,table);
    table->heads[i] = InsertBeginJogo(table->heads[i], match);
}

/*-----------------------REFERENTES AO COMANDO r-----------------------*/

/*funcao que remove um dado jogo da listagem de jogos*/
void delete_jogo_lst(listagem lst,pJogo match)
{
    /*caso em que so ha um jogo na lista, retorna lista vazia*/
    if ((match->previous == NULL) && (match->next == NULL)) {
        lst->head = NULL;
        lst->tail = NULL;
    }
    /*caso em que o jogo eh o ultimo da lista*/
    else if ((match->previous != NULL) && (match->next == NULL)) {
        lst->tail = match->previous;
        match->previous->next = NULL;
    }
    /*caso em que o jogo eh o primeiro da lista*/
    else if ((match->previous == NULL) && (match->next != NULL)) {
        match->next->previous = NULL;
        lst->head = match->next;
    }
    else {
        match->previous->next = match->next;
        match->next->previous = match->previous;
    }
}

/*funcoes que removem o jogo da hash table dos jogos*/

Node_jogos delete_jogo_hash(char nome[],Node_jogos node_j)
{
    /*percorre o node ate encontrar o jogo cujo nome eh igual 
    ao nome recebido*/
    Node_jogos temp = node_j, prev = NULL;
    while(temp != NULL) {
        if (strcmp(temp->match->nome,nome) == 0) {
            /*caso seja o primeiro jogo desse node*/
            if (temp == node_j) {
                node_j = temp->next; 
            }
            else {
                prev->next = temp->next; 
            }
            liberta_no_j(temp);
            break;
        }
        /*prev eh necessario para guardar os jogos que se encontram
        antes do pretendido*/
        prev = temp;
        temp = temp->next;
    }
    return node_j;
}

void DeleteJogoHash(char nome[],table_jogos tab_j) 
{
    /*identifica o indice da hash onde o jogo se encontra*/
    int i = hash_jogos(nome, tab_j);
    tab_j->heads[i] = delete_jogo_hash(nome,tab_j->heads[i]);
}

/*-----------------------REFERENTES AO COMANDO s-----------------------*/

/*funcao que atualiza quer os scores quer os vencedores de cada jogo*/
void Change_Score(pJogo match,int score1,int score2)
{
    match->score1 = score1;
    match->score2 = score2;
    free(match->winner);
    if (score1 > score2) {
        match->winner = can_fail_malloc(sizeof(char)*(strlen(match->equipa1)+1));
        strcpy(match->winner,match->equipa1);
    }
    else if (score2 > score1) {
        match->winner = can_fail_malloc(sizeof(char)*(strlen(match->equipa2)+1));
        strcpy(match->winner,match->equipa2);
    }
    else {
        match->winner = NULL;
    }
}

/*ja atualizados os vencedores e os scores, esta funcao atualizara
 as vitorias de cada equipa*/
void Change_Wins(pJogo match,table_eq tab_eq,char *old_winner)
{
    /*caso em que antes de atualizado o resultado do jogo foi um 
    empate e depois de atualizado tambem*/
    if (match->winner == NULL && old_winner == NULL) {
        /*as vitorias de cada equipa nao se alteram*/
        return;
    }
    /*caso em que mesmo depois de atualizados os scores, o vencedor
    eh o mesmo*/
    if (match->winner != NULL && old_winner != NULL 
    && strcmp(match->winner,old_winner)==0) {
            return;
    }
    /*caso em que antes de atualizados os scores havia um vencedor
    mas que ao atualizar verificou-se um empate*/
    else if (match->winner == NULL && old_winner != NULL) {
        (SearchEquipa(old_winner,tab_eq))->vitorias--;
        return;
    }
    /*caso em que antes de atualizados os scores verificava-se um 
    empate mas depois de atualizados se verifica um vencedor*/
    else if (match->winner != NULL && old_winner == NULL) {
        (SearchEquipa(match->winner,tab_eq))->vitorias++;
        return;
    } 
    /*restantes casos em que se verifica mudanca de vencedor*/
    else {
        SearchEquipa(old_winner,tab_eq)->vitorias--;
        SearchEquipa(match->winner,tab_eq)->vitorias++;
        return;
    }
}

/*-----------------------REFERENTES AO COMANDO A-----------------------*/

Equipas cria_equipa(char * nome)
{
    Equipas equipa;
    equipa = (Equipas)can_fail_malloc(sizeof(struct eq));

    equipa->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(equipa->nome, nome);

    equipa->vitorias = 0;

    return equipa;
}


/*funcoes de insercao de uma equipa na hash table das equipas*/

Node_eq insertBeginEquipa(Node_eq head, Equipas equipa)
{
    Node_eq old_head=head;
    head=(Node_eq)can_fail_malloc(sizeof(struct node_eq));
    head->next=old_head;
    head->equipa=equipa;
    return head;
}

void InsertEquipa(Equipas equipa,table_eq table)
{
    /*i sera o indice da hash table onde vai ser colocado a
    equipa, isto eh, este indice corresponde a uma lista simplesmente
    ligada onde a equipa sera inserida no inicio da mesma*/
    int i = hash_eq(equipa->nome,table);
    table->heads[i] = insertBeginEquipa(table->heads[i], equipa);
}

 