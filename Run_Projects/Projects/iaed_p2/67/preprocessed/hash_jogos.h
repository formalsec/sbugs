#ifndef _HASH_JOGOS_
#define _HASH_JOGOS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* estrura jogo*/
typedef struct jogo{
  char *nome;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
}*pJogo;

/* criar um node de jogos*/
typedef struct node_jogos{
  pJogo jogo;
  struct node_jogos *next;
}*link_jogo;


/*declarar as funcoes*/
link_jogo* init_jogo(int m);
link_jogo novo_jogo(char* nome, char*equipa1, char*equipa2, int score1, int score2);
link_jogo procura_lista_jogo(link_jogo head, char *nome);
link_jogo insere_lista_jogo(link_jogo head, link_jogo jogo);
link_jogo remove_jogo_lista(link_jogo head, char* nome);
int hash_string(char *v, int M);
link_jogo procura_jogo(char *nome, link_jogo* tabela_jogos);
link_jogo* insere_jogo(link_jogo jogo, link_jogo* tabela_jogos);
link_jogo* apaga_jogo(char *nome, link_jogo* tabela_jogos);
link_jogo apaga_jogo_2(char *nome, link_jogo lista_jogos);
link_jogo insere_jogo_2(link_jogo jogo, link_jogo lista_jogos);
link_jogo insere_lista_jogo_2(link_jogo head, link_jogo jogo);
void print_jogos(link_jogo head, int linha);
void altera_jogo(link_jogo jogo, int score1, int score2);
link_jogo altera_jogo_2(char *nome, int score1, int score2, link_jogo lista_jogos);
link_jogo* liberta_jogos(link_jogo* tabela_jogos);
link_jogo remove_lista(link_jogo head);

#endif
