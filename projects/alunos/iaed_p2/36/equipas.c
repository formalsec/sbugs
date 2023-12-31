#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"

void adicionaVitoria(hashE * e, char * nome){
  equipa * omega, * outra;
  int s;
  s = hash(nome);
  if(strcmp(e->entradas[s]->nome, nome) == 0){
    e->entradas[s]->vitorias++;
    return;
  }
  outra = e->entradas[s];
  omega = outra->next;
  while(omega != NULL){
    if(strcmp(omega->nome, nome) == 0)
    {
      outra->next->vitorias++;
      break;
    }
    outra = omega;
    omega = outra->next;
  }
}

void retiraVitoria(hashE * e, char * nome){
  equipa * omega, * outra;
  int s;
  s = hash(nome);
  if(strcmp(e->entradas[s]->nome, nome) == 0){
    e->entradas[s]->vitorias--;
    return;
  }
  outra = e->entradas[s];
  omega = outra->next;
  while(omega != NULL){
    if(strcmp(omega->nome, nome) == 0)
    {
      outra->next->vitorias--;
      break;
    }
    outra = omega;
    omega = outra->next;
  }
}

int hash(char * nome){
  int i, total, comprimento;
  comprimento = strlen(nome);
  total = 0;
  for(i = 0; i < comprimento; i++)
  {
    total += (nome[i] * 33);
  }
  return total % 1000;
}

hashE * criaHashE(){
  int i;
  hashE * anexo = can_fail_malloc(sizeof(hashE));

  anexo->entradas = can_fail_malloc(sizeof(equipa *) * 1000);
  for(i = 0; i < 1000; i++){
    anexo->entradas[i] = NULL;
  }
  return anexo;
}

equipa * procuraEquipa(hashE * s, char * nome){
  int chave;
  equipa * eq;
  equipa * eq2;
  chave = hash(nome);
  eq = s->entradas[chave];
  while(eq != NULL){
    if(strcmp(eq->nome, nome) == 0) return eq;
    eq2 = eq;
    eq = eq2->next;
  }
  return NULL;
}

int adicionaEquipa(hashE * s, char * nome){
  int chave;
  equipa * eq;
  equipa * eq2, * eq3;
  eq = procuraEquipa(s, nome);
  chave = hash(nome);
  if(eq != NULL) return 0;
  eq3 = s->entradas[chave];
  if(eq3 == NULL){
    eq3 = can_fail_malloc(sizeof(equipa));
    eq3->nome = can_fail_malloc(strlen(nome) + 1);
    strcpy(eq3->nome, nome);
    eq3->vitorias = 0;
    eq3->next = NULL;
    s->entradas[chave] = eq3;
  }
  while(eq3 != NULL){
    eq2 = eq3;
    eq3 = eq2->next;
  }
  eq2->next = can_fail_malloc(sizeof(equipa));
  eq2->next->nome = can_fail_malloc(strlen(nome) + 1);
  strcpy(eq2->next->nome, nome);
  eq2->next->vitorias = 0;
  eq2->next->next = NULL;
  return 1;
}
