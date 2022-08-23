#ifndef _HASHTABLE_EQUIPAS_
#define _HASHTABLE_EQUIPAS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*iniciar a estrutura equipa*/
typedef struct equipa {
  char *nome;
  int vitorias;
} *pEquipa;

/*iniciar um node de equipas*/
typedef struct node_equipa{
  pEquipa equipa;
  struct node_equipa *next;
}*link_equipa;

/*declarar as funcoes*/
void atribui_vitoria(char* nome, link_equipa* tabela_equipas);
void remove_vitoria(char* nome, link_equipa* tabela_equipas);
link_equipa nova_equipa(char *nome);
link_equipa procura_lista_equipa(link_equipa head, char *nome);
link_equipa insere_equipa_lista(link_equipa head, char* nome);
link_equipa remove_equipa_lista(link_equipa, char* nome);
link_equipa* init_equipa(int n);
int hash_strings(char *v, int N);
link_equipa procura_equipa(char* nome, link_equipa* tabela_equipas);
link_equipa* insere_equipa(link_equipa equipa, link_equipa* tabela_equipas);
link_equipa* apaga_equipa(char* nome, link_equipa *tabela_equipas);
link_equipa insere_equipa_2(link_equipa equipa, link_equipa lista_equipas);
link_equipa insere_equipa_lista_2(link_equipa head, link_equipa equipa);
void print_equipas(link_equipa head, int linha);
link_equipa atribui_vitoria_2(char* nome, link_equipa lista_equipas);
link_equipa remove_vitoria_2(char* nome, link_equipa lista_equipas);
link_equipa* liberta_equipas(link_equipa* tabela_equipas);
link_equipa apaga_equipa_2(char *nome, link_equipa lista_equipas);
link_equipa remove_lista_2(link_equipa head);

#endif
