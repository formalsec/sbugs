#ifndef GERAL_H
#define GERAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"

#define MAX_NOME 1024

/*-------------------------------------PROTOTIPOS-------------------------------------*/

/*--------------------COMANDOS E AS RESPETIVAS FUNCOES ESPECIFICAS--------------------*/

void a(int cont,table_eq tab_eq,table_jogos tab_j,listagem lst);
pJogo cria_jogo(char *buffer,char *team1,char *team2,int s1, int s2,table_eq tab_eq);
void add_last(listagem l,pJogo match);
Node_jogos InsertBeginJogo(Node_jogos head, pJogo match);
void InsertJogo(pJogo match,table_jogos table);

void l(int cont,listagem lst);

void p(int cont,table_jogos tab_j);

void r(int cont,table_jogos tab_j,table_eq tab_eq,listagem lst);
Node_jogos delete_jogo_hash(char nome[],Node_jogos node_j);
void DeleteJogoHash(char nome[],table_jogos tab_j);
void delete_jogo_lst(listagem lst,pJogo match);

void s(int cont,table_jogos tab_j,table_eq tab_eq);
void Change_Score(pJogo match,int score1,int score2);
void Change_Wins(pJogo match,table_eq tab_eq,char *old_winner);

void A(int cont,table_eq tab_eq);
Equipas cria_equipa(char *nome);
Node_eq insertBeginEquipa(Node_eq head, Equipas equipa);
void InsertEquipa(Equipas equipa,table_eq table);

void P(int cont,table_eq tab_eq);

void g(int cont,table_eq tab_eq);
int comparestr(const void*a, const void*b);

#endif