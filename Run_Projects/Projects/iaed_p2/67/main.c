#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_jogos.h"
#include "hash_equipas.h"

#define SIZE 1069
#define UM 1
#define DOIS 2

void insertion(char* a[], int left, int right){
  int i,j;
  for (i = left+1; i < right; i++){
    char* v = a[i];
    j = i-1;
    while ( j >= left && strcmp(v, a[j])<0) {
      a[j+1] = a[j];
      j--;
    }
    a[j+1] = v;
  }
}


int main(){
  char x;
  int linha = 0;
  link_jogo lista_jogos = NULL;
  link_equipa lista_equipas = NULL;
  link_jogo* tabela_jogos;
  link_equipa* tabela_equipas;
  tabela_jogos = init_jogo(SIZE);
  tabela_equipas = init_equipa(SIZE);
  x = getchar();
  while (x!= 'x'){
    /*adiciona um novo jogo */
    if (x=='a'){
      link_jogo jogo;
      int score1, score2;
      char buf[1024], buf1[1024], buf2[1024];
      char *equipa1, *equipa2, *nome;
      linha++;
      scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",buf, buf1, buf2, &score1, &score2);
      nome = (char*) malloc((strlen(buf) + 1) * sizeof(char));
      strcpy(nome, buf);
      equipa1 = (char*) malloc((strlen(buf1) + 1) * sizeof(char));
      strcpy(equipa1, buf1);
      equipa2 = (char*) malloc((strlen(buf2) + 1) * sizeof(char));
      strcpy(equipa2, buf2);
      if( procura_jogo(nome, tabela_jogos) != NULL){
        printf("%d Jogo existente.\n",linha);
      }
      else if (procura_equipa(equipa1, tabela_equipas)== NULL){
        printf("%d Equipa inexistente.\n",linha);
      }
      else if (procura_equipa(equipa2, tabela_equipas)== NULL){
        printf("%d Equipa inexistente.\n",linha);
      }
      else{
        jogo = novo_jogo(nome, equipa1, equipa2, score1, score2);
        tabela_jogos = insere_jogo(jogo, tabela_jogos);
        lista_jogos = insere_jogo_2(jogo, lista_jogos);
        if (score1 > score2){
          atribui_vitoria(equipa1, tabela_equipas);
          lista_equipas = atribui_vitoria_2(equipa1, lista_equipas);
        }
        else if (score1 <score2){
          atribui_vitoria(equipa2, tabela_equipas);
          lista_equipas = atribui_vitoria_2(equipa2, lista_equipas);
        }
      }
      free(nome);
      free(equipa1);
      free(equipa2);
    }
    /*adiciona uma nova equipa */
    else if(x=='A'){
      char *nome;
      char buffer[1024];
      link_equipa new_equipa;
      linha++;
      scanf(" %[^:\n]", buffer);
      nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(nome, buffer);
      if(procura_equipa(nome, tabela_equipas)!= NULL){
        printf("%d Equipa existente.\n",linha);
      }
      else{
        new_equipa = nova_equipa(nome);
        tabela_equipas = insere_equipa(new_equipa, tabela_equipas);
        lista_equipas = insere_equipa_2(new_equipa, lista_equipas);
      }
      free(nome);
    }
    /*lista todos os jogos pela ordem em que foram introduzidos*/
    else if (x=='l'){
      linha++;
      print_jogos(lista_jogos, linha);
    }
    /*procura um jogo*/
    else if(x=='p'){
      link_jogo x;
      char *nome;
      char buffer[1024];
      linha++;
      scanf(" %[^:\n]", buffer);
      nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(nome, buffer);
      x = procura_jogo(nome, tabela_jogos);
      if (x==NULL){
        printf("%d Jogo inexistente.\n",linha);
      }
      else{
      printf("%d %s %s %s %d %d\n",linha, x->jogo->nome, x->jogo->equipa1, x->jogo->equipa2, x->jogo->score1, x->jogo->score2);
      }
      free(nome);
    }
    /*Procura uma equipa*/
    else if (x=='P'){
      link_equipa equipa;
      char buffer[1024];
      char *nome;
      linha++;
      scanf(" %[^:\n]", buffer);
      nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(nome, buffer);
      equipa = procura_equipa(nome, tabela_equipas);
      if (equipa==NULL){
        printf("%d Equipa inexistente.\n",linha);
      }
      else{
        printf("%d %s %d\n",linha, equipa->equipa->nome, equipa->equipa->vitorias);
      }
      free(nome);
    }
    /*apaga um jogo*/
    else if(x=='r'){
      link_jogo jogo;
      char buffer[1024];
      char *nome;
      linha++;
      scanf(" %[^:\n]", buffer);
      nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(nome, buffer);
      jogo = procura_jogo(nome, tabela_jogos);
      if (jogo == NULL){
        printf("%d Jogo inexistente.\n",linha);
      }
      else{
        if (jogo->jogo->score1 > jogo->jogo->score2){
          remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
          lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
        }
        else if (jogo->jogo->score1 < jogo->jogo->score2){
          remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
          lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
        }
        tabela_jogos = apaga_jogo(nome, tabela_jogos);
        lista_jogos = apaga_jogo_2(nome, lista_jogos);
      }
      free(nome);
    }
    /*altera o score de um jogo*/
    else if(x=='s'){
      link_jogo jogo;
      char *nome;
      int score1, score2;
      int old_score1 = 0, old_score2 = 0;
      char buffer[1024];
      linha++;
      scanf(" %[^:\n]:%d:%d", buffer, &score1, &score2);
      nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(nome, buffer);
      jogo = procura_jogo(nome, tabela_jogos);
      if (jogo== NULL){
        printf("%d Jogo inexistente.\n",linha );
      }
      else{
        old_score1 = jogo->jogo->score1;
        old_score2 = jogo->jogo->score2;
        altera_jogo(jogo, score1, score2);
        lista_jogos = altera_jogo_2(nome, score1, score2, lista_jogos);
        /*caso de empate*/
        if (old_score1 == old_score2){
          if (score1 > score2){
            atribui_vitoria(jogo->jogo->equipa1, tabela_equipas);
            lista_equipas = atribui_vitoria_2(jogo->jogo->equipa1, lista_equipas);
          }
          else if (score1 < score2){
          atribui_vitoria(jogo->jogo->equipa2, tabela_equipas);
          lista_equipas = atribui_vitoria_2(jogo->jogo->equipa2, lista_equipas);
          }
        }
        /*caso de vitoria equipa1*/
        else if (old_score1 > old_score2){
          if (score1 < score2){
            remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
            lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
            atribui_vitoria(jogo->jogo->equipa2, tabela_equipas);
            lista_equipas = atribui_vitoria_2(jogo->jogo->equipa2, lista_equipas);
          }
          if (score1==score2){
            remove_vitoria(jogo->jogo->equipa1, tabela_equipas);
            lista_equipas = remove_vitoria_2(jogo->jogo->equipa1, lista_equipas);
          }
        }
        /*caso de vitoria equipa2*/
        else if (old_score1 < old_score2){
          if (score1 > score2){
            remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
            lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
            atribui_vitoria(jogo->jogo->equipa1, tabela_equipas);
            lista_equipas = atribui_vitoria_2(jogo->jogo->equipa1, lista_equipas);
          }
          if (score1==score2){
            remove_vitoria(jogo->jogo->equipa2, tabela_equipas);
            lista_equipas = remove_vitoria_2(jogo->jogo->equipa2, lista_equipas);
          }
        }
      }
    }

    /*encontra as equipas que venceram mais jogos*/
    else if (x=='g'){
      int max = 0, i = 0,j;
      link_equipa t,x;
      char* lista_melhores[1000];
      linha++;
      for (t = lista_equipas; t!= NULL; t = t->next){
        if (t->equipa->vitorias >= max){
          max = t->equipa->vitorias;
        }
      }
      for(x = lista_equipas; x!= NULL; x = x->next){
        if (x->equipa->vitorias == max){
          lista_melhores[i] = (char*) malloc(sizeof(char) * (strlen(x->equipa->nome)+1));
          strcpy(lista_melhores[i], x->equipa->nome);
          i++;
        }
      }
      insertion(lista_melhores, 0, i);
      if (lista_equipas != NULL){
        printf("%d Melhores %d\n",linha, max );
      }
      for (j = 0; j<=i-1; j++){
        printf("%d * %s\n",linha, lista_melhores[j]);
      }
      for(j = 0 ; j < i; j++){
          free(lista_melhores[j]);
      }
    }
    x = getchar();
  }
  /*liberta tudo*/
  tabela_jogos = liberta_jogos(tabela_jogos);
  lista_jogos = remove_lista( lista_jogos);
  tabela_equipas = liberta_equipas(tabela_equipas);
  lista_equipas = remove_lista_2(lista_equipas);
  free(tabela_jogos);
  free(tabela_equipas);
  return 0;
}
