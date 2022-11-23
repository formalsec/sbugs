#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes_aux.h"
#include "altera_hash_ou_fila.h"
/*tamanho de cabecas das hashtables*/
#define N_MOD 3013
/*dimensao maxima das strings*/
#define MAX_CHAR 1024
/*---------------------------------------------------*/
/*adiciona novo jogo a base de dados*/
void novo_jogo(int *contador_input,noh *cabeca[],noh_equipa *cabeca_equipa[], fila *fila_jogos){
  int chave,chave_equipa1,chave_equipa2,len,score1,score2;
  char nome[MAX_CHAR]={0},equipa1[MAX_CHAR]={0},equipa2[MAX_CHAR]={0};
  char *nome_temp,*equipa1_temp,*equipa2_temp;
  jogo *jogo_temp;
  *contador_input+= 1;

  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",nome,equipa1,equipa2,&score1,&score2);

  /*vai calcular o indice da hashtable onde por o jogo*/
  chave = calcula_chave(nome);
  if (verifica_se_jogo_existe(chave,nome,cabeca) == 1){
    printf("%d Jogo existente.\n",*contador_input);
    return;
  }

  chave_equipa1 = calcula_chave(equipa1);
  if (verifica_se_equipa_existe(chave_equipa1,equipa1,cabeca_equipa) == 0){
    printf("%d Equipa inexistente.\n",*contador_input);
    return;
  }
  chave_equipa2 = calcula_chave(equipa2);
  if (verifica_se_equipa_existe(chave_equipa2,equipa2,cabeca_equipa) == 0){
    printf("%d Equipa inexistente.\n",*contador_input);
    return;
  }

  /*alocar espaco para cada jogo. quando se adicionar o jogo a uma lista vai se buscar o ponteiro para este espaco*/
  jogo_temp = can_fail_malloc(sizeof(jogo));
  /*copia todos os detalhes do jogo para a estrutura jogo*/
  len = strlen(nome);
  nome_temp = can_fail_malloc(sizeof(char)*(len+1));
  strcpy(nome_temp,nome);
  jogo_temp->nome=nome_temp;

  len = strlen(equipa1);
  equipa1_temp = can_fail_malloc(sizeof(char)*(len+1));
  strcpy(equipa1_temp,equipa1);
  jogo_temp->equipa1=equipa1_temp;

  len = strlen(equipa2);
  equipa2_temp = can_fail_malloc(sizeof(char)*(len+1));
  strcpy(equipa2_temp,equipa2);
  jogo_temp->equipa2=equipa2_temp;

  jogo_temp->score1 = score1;
  jogo_temp->score2 = score2;

  /*vai ao indice da hashtable adicionar a lista interligada o jogo*/
  adiciona_jogo_lista_fila(chave,jogo_temp,cabeca,fila_jogos);
  atualiza_jogos_ganhos(cabeca_equipa,chave_equipa1,chave_equipa2,score1,score2,equipa1,equipa2);
}
/*imprime todos os elementos na fila de jogos*/
void lista_jogos(int *contador_input, fila *fila_jogos) {
  *contador_input+= 1;

  if (fila_jogos->cabeca != NULL){ 
    noh *noh_fila = fila_jogos->cabeca;
    while (noh_fila != NULL){
      printf("%d %s %s %s %d %d\n", *contador_input, noh_fila->jogo->nome, noh_fila->jogo->equipa1, noh_fila->jogo->equipa2, noh_fila->jogo->score1,noh_fila->jogo->score2);
      noh_fila = noh_fila->prox_fila;
    }
  }
}
/*procura nome de jogo na hashtable de jogos e imprime os seus detalhes*/
void procura_jogo(int *contador_input, noh *cabeca[]) {
  char nome[MAX_CHAR];
  int chave;
  *contador_input+= 1;

  scanf(" %[^:\n]",nome);
  chave = calcula_chave(nome);
  
  if(cabeca[chave] != NULL) {
    noh *noh_temp = cabeca[chave];
    while (noh_temp != NULL) {
      /*encontra jogo*/
      if (strcmp(noh_temp->jogo->nome,nome)==0){
        printf("%d %s %s %s %d %d\n",*contador_input, noh_temp->jogo->nome, noh_temp->jogo->equipa1, noh_temp->jogo->equipa2, noh_temp->jogo->score1,noh_temp->jogo->score2);
        return;
      }
      noh_temp = noh_temp->prox;
    }
  }
  printf("%d Jogo inexistente.\n",*contador_input);
}
/*apaga jogo da base de dados, ou seja, da hashtable de jogos e da fila de jogos*/
void apaga_jogo(int *contador_input, noh *cabeca[], noh_equipa *cabeca_equipa[],fila *fila_jogos){
  char nome[MAX_CHAR];
  int chave;
  noh *noh_temp;
  *contador_input+= 1;

  scanf(" %[^:\n]",nome);
  chave = calcula_chave(nome);  

  noh_temp = cabeca[chave];

  if (verifica_se_jogo_existe(chave,nome,cabeca)==0){
    printf("%d Jogo inexistente.\n",*contador_input);
    return;
  }

  /*apagar da hashtable*/
  if (cabeca[chave] != NULL){
    /*se jogo estiver na cabeca*/
    if (strcmp(cabeca[chave]->jogo->nome, nome) == 0){

      /*fazer update aos jogos ganhos das equipas*/
      if(cabeca[chave]->jogo->score1 > cabeca[chave]->jogo->score2){
        decrementa_uma(cabeca_equipa, cabeca[chave]->jogo->equipa1);
      }
      else if(cabeca[chave]->jogo->score2 > cabeca[chave]->jogo->score1){
        decrementa_uma(cabeca_equipa, cabeca[chave]->jogo->equipa2);
      }
      /*ver se e o unico jogo na lista*/
      if (cabeca[chave]->prox != NULL) {
        cabeca[chave] = cabeca[chave]->prox;
        /*apaga jogo da fila*/
        apaga_da_fila(nome,fila_jogos);
        free(noh_temp->jogo);
        free(noh_temp);
        return;
      } 
      else {
        apaga_da_fila(nome,fila_jogos);
        free(noh_temp->jogo);
        free(noh_temp);
        cabeca[chave] = NULL;
        return;
      }
    }
    /*se jogo nao esta na cabeca*/
    while(noh_temp != NULL){
      if (strcmp(noh_temp->prox->jogo->nome,nome) == 0) {
        /*update jogos ganhos*/
        if(noh_temp->prox->jogo->score1 > noh_temp->prox->jogo->score2){
          decrementa_uma(cabeca_equipa, noh_temp->prox->jogo->equipa1);
        }
        else if(noh_temp->prox->jogo->score2 > noh_temp->prox->jogo->score1){
          decrementa_uma(cabeca_equipa, noh_temp->prox->jogo->equipa2);
        }
        /*jogo esta no meio*/
        if (noh_temp->prox->prox != NULL) {
          noh *noh_apagar = noh_temp->prox;
          noh_temp->prox = noh_temp->prox->prox;
          apaga_da_fila(nome,fila_jogos);
          free(noh_apagar->jogo);
          free(noh_apagar);
          return;
        }
        /*jogo esta no tail*/
        if (noh_temp->prox->prox == NULL){
          noh *noh_apagar = noh_temp->prox;
          noh_temp->prox = NULL;
          apaga_da_fila(nome,fila_jogos);
          free(noh_apagar->jogo);
          free(noh_apagar);
          return;
        }
      }
    noh_temp = noh_temp->prox;
    }
  }

}
/*altera score de um jogo*/
void altera_score(int *contador_input, noh* cabeca[], noh_equipa *cabeca_equipa[]){
  int chave,score1,score2,var;
  char nome[MAX_CHAR];
  *contador_input+= 1;

  scanf(" %[^:\n]:%d:%d",nome,&score1,&score2);

  /*vai calcular o indice da hashtable onde por o jogo dependendo do comprimento do seu nome*/
  chave = calcula_chave(nome);

  if (verifica_se_jogo_existe(chave,nome,cabeca) == 0){
    printf("%d Jogo inexistente.\n",*contador_input);
  }
  /*vai percorrer a hashtable de jogos ate encontrar o pretendido, e, ao ver os seus scores antigo e o novo decide o que fazer*/
  if (cabeca[chave] != NULL) {
    noh *noh_temp = cabeca[chave];
    while (noh_temp != NULL){
      if (strcmp(noh_temp->jogo->nome,nome)==0){

        if(noh_temp->jogo->score1 > noh_temp->jogo->score2){
          var = 0;
        }
        else if(noh_temp->jogo->score2 > noh_temp->jogo->score1){
          var = 1;
        }
        else if(noh_temp->jogo->score1 == noh_temp->jogo->score2){
          var = 2;
        }

        noh_temp->jogo->score1 = score1;
        noh_temp->jogo->score2 = score2;

        if(noh_temp->jogo->score1 > noh_temp->jogo->score2){
          if (var == 1){
            /*incrementa jogos ganhos equipa 1 e decrementa equipa 2*/
            incrementa_uma_decrementa_outra(cabeca_equipa,noh_temp->jogo->equipa1,noh_temp->jogo->equipa2);
          }
          else if(var == 2){
            /*incrementa equipa 1*/
            incrementa_uma(cabeca_equipa,noh_temp->jogo->equipa1);
          }
        }
        else if(noh_temp->jogo->score2 > noh_temp->jogo->score1){
          if (var == 0){
            /*incrementa jogos ganhos equipa 2 e decrementa equipa 1*/
            incrementa_uma_decrementa_outra(cabeca_equipa,noh_temp->jogo->equipa2,noh_temp->jogo->equipa1);
          }
          else if(var == 2){
            /*incrementa equipa 2*/
            incrementa_uma(cabeca_equipa,noh_temp->jogo->equipa2);
          }
        }
        else if(noh_temp->jogo->score1 == noh_temp->jogo->score2){
          if (var == 0){
            /*decrementa jogos ganhos equipa 1*/
            decrementa_uma(cabeca_equipa,noh_temp->jogo->equipa1);
          }
          else if(var == 1){
            /*decrementa jogos ganhos equipa 2*/
            decrementa_uma(cabeca_equipa,noh_temp->jogo->equipa2);
          }
        }
        break;
      }
      noh_temp = noh_temp->prox;
    }
  }
}
/*adiciona uma nova equipa a base de dados */
void nova_equipa(int *contador_input,noh_equipa *cabeca_equipa[]){
  char equipa[MAX_CHAR];
  int chave;
  char *equipa_mem;
  noh_equipa *novo_noh;
  *contador_input+= 1;

  scanf(" %[^:\n]",equipa);
  chave = calcula_chave(equipa);

  if (verifica_se_equipa_existe(chave, equipa,cabeca_equipa)==1){
    printf("%d Equipa existente.\n",*contador_input);
    return;
  }
  /*aloca espaco para um novo noh na memoria*/
  novo_noh = can_fail_malloc(sizeof(noh_equipa)); 
  /*aloca espaco oara a string do nome da equipa*/
  equipa_mem = can_fail_malloc(sizeof(char) * strlen(equipa)+1);
  strcpy(equipa_mem,equipa);
  novo_noh->equipa = equipa_mem;
  novo_noh->jogos_ganhos = 0;
  novo_noh->prox = NULL;
  /*adiciona a hash das equipas*/
  if (cabeca_equipa[chave] == NULL){
    cabeca_equipa[chave] = novo_noh;
  }
  else {
    noh_equipa *noh_temp = cabeca_equipa[chave];
    while(noh_temp != NULL) {
      if (noh_temp->prox == NULL){
        noh_temp->prox = novo_noh;
        break;
      }
      noh_temp = noh_temp->prox;
    }
  }
}
/*procura equipa na hashtable das equipas e faz imprime os jogos ganhos*/
void procura_equipa(int *contador_input, noh_equipa *cabeca_equipa[]){
  char equipa[MAX_CHAR];
  int chave;
  noh_equipa *noh_temp;
  *contador_input+= 1;

  scanf(" %[^:\n]",equipa);
  chave = calcula_chave(equipa);

  if(verifica_se_equipa_existe(chave, equipa, cabeca_equipa) == 0){
    printf("%d Equipa inexistente.\n",*contador_input);
    return;
  }

  /*vai a hashtable das equipas e devolve o numero de jogos ganhos*/
  noh_temp = cabeca_equipa[chave];
  while(noh_temp != NULL){
    if(strcmp(noh_temp->equipa,equipa)==0){
      printf("%d %s %d\n",*contador_input,equipa,noh_temp->jogos_ganhos);
      return;
    }
    noh_temp = noh_temp->prox;
  }
}
/*imprime as equipas com maior numero de wins*/
void melhores_equipas(int *contador_input, noh_equipa *cabeca_equipa[]){
  noh_equipa *noh_temp_eq;
  int i,max,cont=0;
  *contador_input+= 1;

  /*verifica se hashtable esta vazia em todas as posicoes*/
  for(i=0;i<N_MOD;i++){
    if(cabeca_equipa[i] == NULL){
      cont++;
    }
  }
  if (cont == N_MOD){
    return;
  }

  /*vai percorrer a hashtable dos jogos e ver o numero mais alto de jogos ganhos, que vai ficar guardado em max*/
  max = -1;
  for(i=0;i<N_MOD;i++){
    if(cabeca_equipa[i] != NULL){
      noh_temp_eq = cabeca_equipa[i];
      while (noh_temp_eq != NULL){
        if(noh_temp_eq->jogos_ganhos > max){
          max = noh_temp_eq->jogos_ganhos;
        }
        noh_temp_eq = noh_temp_eq->prox;
      }
    }
  }
  /*se ha equipas e nao ha jogos percorre hashtable das equipas e imprime-as todas a 0*/
  if (max == -1){
    printf("%d Melhores 0\n",*contador_input);
    lista_com_equipas_melhores_e_sort(contador_input,0,cabeca_equipa);
    return;
  }

  printf("%d Melhores %d\n",*contador_input,max);
  lista_com_equipas_melhores_e_sort(contador_input,max,cabeca_equipa);
}
/*---------------------------------------------------*/
int main() {
  /*primeira letra do input*/
  char c;
  /*quantos inputs ja foram postos para ajudar no debug*/
  int *contador_input = can_fail_malloc(sizeof(int));
  /*fila onde se poe os elementos da lista por ordem de insercao*/
  fila *fila_jogos = faz_fila();
  /*hashtable equipas*/
  noh_equipa *cabeca_equipa[N_MOD] = {NULL};
  /*hashtable*/
  noh *cabeca[N_MOD] = {NULL};
  *contador_input = 0;
  /*---------------------------------------------------*/
  while (1>0){
    c = getchar();
    if (c == 'a'){
      novo_jogo(contador_input,cabeca,cabeca_equipa,fila_jogos);
    }
    if (c == 'A'){
      nova_equipa(contador_input,cabeca_equipa);
    }
    if (c == 'l'){
      lista_jogos(contador_input,fila_jogos);
    }
    if (c == 'p'){
      procura_jogo(contador_input,cabeca);
    }
    if (c == 'P'){
      procura_equipa(contador_input,cabeca_equipa);
    }
    if (c == 'r'){
      apaga_jogo(contador_input,cabeca,cabeca_equipa,fila_jogos);
    }
    if (c == 's'){
      altera_score(contador_input,cabeca,cabeca_equipa);
    }
    if (c == 'g'){
      melhores_equipas(contador_input,cabeca_equipa);
    }
    if (c == 'x'){
      free_total(contador_input,cabeca,cabeca_equipa,fila_jogos);
      return 0;
    }
  }
}