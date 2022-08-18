#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes_aux.h"

/*Funcoes com estrutura propria, nao altera o contuedo das hashes nem da fila (apenas faz free de espacos alocados).*/
/*---------------------------------*/
/*calcula a chave (indice) onde vai ser colocado o desejado na hashtable*/
int calcula_chave(char nome[]){
  int a=0,len,i,chave;
  len = strlen(nome);
  for(i=0;i<len;i++){
    a += nome[i];
  }
  chave = ((strlen(nome)*a*nome[0]*nome[len-1]) % N_MOD);
  return chave;
}
/*procura o nome de um jogo na hashtable de jogos a ver se existe ou nao*/
int verifica_se_jogo_existe(int chave, char nome[],noh *cabeca[]){
  if (cabeca[chave] != NULL){
    noh *noh_temp = cabeca[chave];
    while(noh_temp != NULL){
      /*encontra*/
      if (strcmp(noh_temp->jogo->nome,nome) == 0){
        return 1;
      }
      /*nao encontra, passa para proximo noh*/
      else{
        noh_temp = noh_temp->prox;
      }
    }
  }
  return 0;
}
/*procura o nome de uma equipa na hashtable de equipas a ver se existe ou nao*/
int verifica_se_equipa_existe(int chave, char equipa[],noh_equipa *cabeca_equipa[]){
  if (cabeca_equipa[chave] != NULL){
    noh_equipa *noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL){
      if (strcmp(noh_temp->equipa,equipa) == 0){
        return 1;
      }
      else {
        noh_temp = noh_temp->prox;
      }
    }
  }
  return 0;
}
/*funcao de comparacao para o qsort*/
int cmp (const void * a, const void * b) {
   return ( strcmp(*(char**)a,*(char**)b ));
}
/*faz free de toda a memoria alocada durante a execucao do programa*/
void free_total(int *contador_input,noh *cabeca[],noh_equipa *cabeca_equipa[],fila *fila_jogos){
  int i;
  noh *noh_temp,*noh_apagar;
  noh_equipa *noh_temp_eq, *noh_apagar_eq;

  free(contador_input);

  for(i=0;i<N_MOD;i++){
    /*percorre todas as cabecas da hashtable e a respetiva sucessao de nohs e faz free da memoria dos jogos e dos nohs*/
    if (cabeca[i] != NULL){
      noh_temp = cabeca[i];
      while(noh_temp != NULL){
        noh_apagar = noh_temp;
        noh_temp = noh_temp->prox;
        free(noh_apagar->jogo->nome);
        free(noh_apagar->jogo->equipa1);
        free(noh_apagar->jogo->equipa2);
        free(noh_apagar->jogo);
        free(noh_apagar);
      }
    }
    if (cabeca_equipa[i] != NULL){
      noh_temp_eq = cabeca_equipa[i];
      while(noh_temp_eq != NULL){
        noh_apagar_eq = noh_temp_eq;
        noh_temp_eq = noh_temp_eq->prox;
        free(noh_apagar_eq->equipa);
        free(noh_apagar_eq);
      }
    }  
  }
    /*free da fila de jogos*/
  if(fila_jogos->cabeca != NULL){
    noh_temp = fila_jogos->cabeca;
    while(noh_temp != NULL){
      noh_apagar = noh_temp;
      noh_temp = noh_temp->prox_fila;
      free(noh_apagar);
    }
  }
  /*free da cabeca e tail*/
  free(fila_jogos);	
}
/*vai buscar equipas com maior numero de jogos ganhos, ordena e imprime*/
void lista_com_equipas_melhores_e_sort(int *contador_input, int max, noh_equipa *cabeca_equipa[]){
  char **lista;
  int i,cont,len;
  noh_equipa *noh_temp_eq;
  /*alocar espaco para 500 equipas, inicialmente*/
  lista = malloc(sizeof(char*) * 500);
  cont = 0;
  /*vai as equipas com jogos ganhos == max e adiciona o seu nome ah lista. Depois lista eh ordenada e impressa*/
  for(i=0;i<N_MOD;i++){
    if(cabeca_equipa[i] != NULL){
      noh_temp_eq = cabeca_equipa[i];
      while(noh_temp_eq != NULL){
        /*se numero de wins for o pretendido*/
        if(noh_temp_eq->jogos_ganhos == max){
          len = strlen(noh_temp_eq->equipa);
          /*alocar espaco para cada string de nome de equipa*/
          lista[cont] = malloc(sizeof(char)*(len+1));
          strcpy(lista[cont],noh_temp_eq->equipa);
          cont++;
          if(cont >= 500){
            lista = realloc(lista, sizeof(char*)*1000);
          }
        }
      noh_temp_eq = noh_temp_eq->prox;
      }
    }
  }
  qsort(lista, cont, sizeof(char*), cmp);
  for (i=0;i<cont;i++){
    printf("%d * %s\n",*contador_input,lista[i]);
    free(lista[i]);
  }
  free(lista);
}