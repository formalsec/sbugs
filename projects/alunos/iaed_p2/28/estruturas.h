#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"


#define MAX_INPUT_SIZE  3078
#define MAX_SIZE 1024
typedef struct equipa{
  char* nome;
  int jogosGanhos;
} equipa;

typedef struct jogo{
  char* nome;
  char* equipa1;
  char* equipa2;
  int score1;
  int score2;
} jogo;

jogo* createGame(char* nome, char* equipa1, char* equipa2);

void freeEquipa(equipa * team);

void freeGame(jogo * game);

void command_a(int inputLine, char* nome, char* equipa1,
  char* equipa2,int _score1, int _score2,
  ListNode** head_ref, hashtable * jogos, hashtable * equipas);

void command_l(int inputLine, ListNode* tail);

void command_p(int inputLine, char* nome, hashtable * jogos);

void command_r(int inputLine, char* nome, hashtable * jogos,
  hashtable * equipas, ListNode ** head_ref, ListNode ** tail_ref);

void command_s(int inputLine, char* nome, int _score1,
  int _score2, hashtable * jogos, hashtable * equipas);

void command_A(int inputLine, char* nome,
  ListNode ** head_ref, hashtable * equipas);

void command_P(int inputLine, char* nome, hashtable * equipas);

void command_g(int inputLine, ListNode ** head_ref);

#endif /* ESTRUTURAS_H */
