#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes_aux.h"
#include "altera_hash_ou_fila.h"

/*Funcoes que alteram o conteudo da hash da equipa e/ou das equipas e a fila*/
/*------------------------------*/
/*inicializa a fila alocando espaco para a cabeca e para a tail*/
fila* faz_fila(){
  fila *fila_jogos = (fila*)can_fail_malloc(sizeof(fila));
  fila_jogos->cabeca = NULL;
  fila_jogos->tail = NULL;
  return fila_jogos;
}
/*incrementa jogos ganhos de uma equipa*/
void atualiza_jogos_ganhos(noh_equipa *cabeca_equipa[],int chave_equipa1,int chave_equipa2,int score1,int score2, char equipa1[],char equipa2[]){
  noh_equipa *noh_temp;
  /*se score da equipa 1 for maior que o da equipa 2, incrementa os jogos ganhos da equipa 1*/
  if(score1 > score2){
    noh_temp = cabeca_equipa[chave_equipa1];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa1) == 0){
        noh_temp->jogos_ganhos+= 1;
        return;
      }
      noh_temp = noh_temp->prox;
    }
  }
  /*se for o contrario, incrementa o da equipa 2*/
  else if(score2 > score1){
    noh_temp = cabeca_equipa[chave_equipa2];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa2) == 0){
        noh_temp->jogos_ganhos+= 1;
        return;
      } 
      noh_temp = noh_temp->prox;
    }
  }
}
/*adiciona o novo jogo ah hashtable dos jogos e ah fila*/
void adiciona_jogo_lista_fila(int chave, jogo *jogo_temp, noh *cabeca[], fila *fila_jogos) {
  /*aloca espaco na memoria para o noh a colocar*/
  noh *novo_pntr,*novo_pntr_fila;

  /*coloca no conteudo do noh o jogo e no adresso do proximo elemento da lista a null pois sera adicionado ao final da lista*/
  novo_pntr = can_fail_malloc(sizeof(noh));
  novo_pntr->jogo = jogo_temp;
  novo_pntr->prox = NULL;
  novo_pntr->prox_fila = NULL;
  novo_pntr->ant_fila = NULL;
  /*aloca espaco para o noh que vai ser utilizado para a fila*/
  novo_pntr_fila = can_fail_malloc(sizeof(noh));
  novo_pntr_fila->jogo = jogo_temp;
  novo_pntr_fila->prox = NULL;
  novo_pntr_fila->prox_fila = NULL;
  novo_pntr_fila->ant_fila = NULL;

  /*se nao houver nada no primeiro elemento substitui-o pelo novo noh*/
  if (cabeca[chave] == NULL) {
    cabeca[chave] = novo_pntr;
  }
  /*senao vai percorrer a lista ate ao ultimo elemento e adiciona em ultimo lugar*/
  else {
    noh *noh_temp = cabeca[chave];
    while(1>0) {
      if (noh_temp->prox == NULL) {
        noh_temp->prox = novo_pntr;
        break;
      }
    noh_temp = noh_temp->prox;
    }
  }
  /*adicionar os jogos numa so fila separada da hashtable para listar por ordem*/
  /*aqui mudo a fila ao atualizar o prox_fila*/
  if (fila_jogos->cabeca == NULL) {
    fila_jogos->cabeca = novo_pntr_fila;
    fila_jogos->tail = novo_pntr_fila;
  }
  else { /*adicionar no fim*/
    noh *tail_antiga = fila_jogos->tail;
    tail_antiga->prox_fila = novo_pntr_fila;
    novo_pntr->ant_fila = tail_antiga;
    fila_jogos->tail = novo_pntr_fila;
  }
}
/*vai apagar jogo da fila depois de ser apagado da hashtable*/
void apaga_da_fila(char nome[],fila *fila_jogos){
  noh *noh_apagar;
  noh *noh_temp = fila_jogos->cabeca;
  if (noh_temp != NULL) {
    /*se cabeca da fila for o jogo a remover*/
    if (strcmp(noh_temp->jogo->nome,nome)==0) {
       /*ver se e o unico jogo na lista*/
      if (noh_temp->prox_fila != NULL) {
        fila_jogos->cabeca = fila_jogos->cabeca->prox_fila;
        /*free do espaco alocado*/
        free(noh_temp->jogo->nome);
        free(noh_temp->jogo->equipa1);
        free(noh_temp->jogo->equipa2);
        free(noh_temp);
        return;
      } 
      else {
        free(noh_temp->jogo->nome);
        free(noh_temp->jogo->equipa1);
        free(noh_temp->jogo->equipa2);
        free(noh_temp);
        fila_jogos->cabeca = NULL;
        return;
      }
    }
    /*se jogo a remover nao for a cabeca*/
    while (noh_temp != NULL){
      if (strcmp(noh_temp->prox_fila->jogo->nome,nome) == 0){
        /*jogo esta no meio*/
        if (noh_temp->prox_fila->prox_fila != NULL) {
          noh_apagar = noh_temp->prox_fila;
          noh_temp->prox_fila = noh_temp->prox_fila->prox_fila;
          free(noh_apagar->jogo->nome);
          free(noh_apagar->jogo->equipa1);
          free(noh_apagar->jogo->equipa2);
          free(noh_apagar);
          return;
        }
        /*jogo ta no tail*/
        if (noh_temp->prox_fila->prox_fila == NULL){
          noh_apagar = noh_temp->prox_fila;
          free(noh_apagar->jogo->nome);
          free(noh_apagar->jogo->equipa1);
          free(noh_apagar->jogo->equipa2);
          free(noh_apagar);
          noh_temp->prox_fila = NULL;
          fila_jogos->tail = noh_temp;
          return;
        }
      }
      noh_temp = noh_temp->prox_fila;
    }
  }
}
/*incrementa o numero de jogos ganhos de uma equipa e decrementa de outra*/
void incrementa_uma_decrementa_outra(noh_equipa *cabeca_equipa[],char equipa1[],char equipa2[]){
  noh_equipa *noh_temp;
  int chave;
  chave = calcula_chave(equipa1);
  if(cabeca_equipa[chave] != NULL){
    noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa1)==0){
        noh_temp->jogos_ganhos+= 1;
      }
      noh_temp = noh_temp->prox;
    }
  }
  chave = calcula_chave(equipa2);
  if(cabeca_equipa[chave] != NULL){
    noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa2)==0){
        noh_temp->jogos_ganhos-= 1;
      }
      noh_temp = noh_temp->prox;
    }
  }
}
/*incrementa os jogos ganhos de uma equipa*/
void incrementa_uma(noh_equipa *cabeca_equipa[],char equipa[]){
  noh_equipa *noh_temp;
  int chave;
  chave = calcula_chave(equipa);
  if(cabeca_equipa[chave] != NULL){
    noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa)==0){
        noh_temp->jogos_ganhos+= 1;
      }
      noh_temp = noh_temp->prox;
    }
  }
}
/*decrementa os jogos ganhos de uma equipa*/
void decrementa_uma(noh_equipa *cabeca_equipa[],char equipa[]){
  noh_equipa *noh_temp;
  int chave;
  chave = calcula_chave(equipa);
  if(cabeca_equipa[chave] != NULL){
    noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL){
      if(strcmp(noh_temp->equipa,equipa)==0){
        noh_temp->jogos_ganhos-= 1;
      }
      noh_temp = noh_temp->prox;
    }
  }
}