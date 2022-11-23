#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"

/* retorna o jogo se existir. se houver colisao continua a procurar para a frente na cadeia ate encontrar, se nao encontrar devolve NULL */

jogo * procuraJogo(hashJ * s, char * nome){
  int chave;
  jogo * auxx;
  jogo * auxy;
  chave = hash(nome);
  auxx = s->entradas[chave];
  while(auxx != NULL){
    if(strcmp(auxx->nome, nome) == 0) return auxx;
    auxy = auxx;
    auxx = auxy->next;
  }
  return NULL;
}

/* adiciona um jogo na hashtable e tambem na lista (array) ordenada de jogos para o comando l */

int adicionaJogo(hashJ * tabelaJogos, hashE * tabelaEquipas, char * nome, char * nomeequipa1, char * nomeequipa2, int resultado1, int resultado2){
  equipa * equipa1, * equipa2;
  jogo * jogo1, * quilho;
  int chave;
  jogo1 = procuraJogo(tabelaJogos, nome);
  if(jogo1 != NULL) return 1;
  equipa1 = procuraEquipa(tabelaEquipas, nomeequipa1);
  equipa2 = procuraEquipa(tabelaEquipas, nomeequipa2);
  if(equipa1 == NULL || equipa2 == NULL){
    return 2;
  }
  chave = hash(nome);
  jogo1 = tabelaJogos->entradas[chave];
  if(jogo1 == NULL){
    jogo1 = can_fail_malloc(sizeof(jogo));
    jogo1->nome = can_fail_malloc(strlen(nome) + 1);
    strcpy(jogo1->nome, nome);
    jogo1->equipa1 = can_fail_malloc(strlen(nomeequipa1) + 1);
    strcpy(jogo1->equipa1, nomeequipa1);
    jogo1->equipa2 = can_fail_malloc(strlen(nomeequipa2) + 1);
    strcpy(jogo1->equipa2, nomeequipa2);
    if(resultado1 > resultado2) adicionaVitoria(tabelaEquipas, nomeequipa1);
    if(resultado1 < resultado2) adicionaVitoria(tabelaEquipas, nomeequipa2);
    jogo1->pontos1 = resultado1;
    jogo1->pontos2 = resultado2;
    tamanhoLista++;
    listaL = can_fail_realloc(listaL, sizeof(jogo) * tamanhoLista);
    listaL[tamanhoLista - 1] = *jogo1;
    tabelaJogos->entradas[chave] = jogo1;
    return 0;
  }
  while(jogo1 != NULL){
    quilho = jogo1;
    jogo1 = quilho->next;
  }
  jogo1 = can_fail_malloc(sizeof(jogo));
  jogo1->nome = can_fail_malloc(strlen(nome) + 1);
  strcpy(jogo1->nome, nome);
  jogo1->equipa1 = can_fail_malloc(strlen(nomeequipa1) + 1);
  strcpy(jogo1->equipa1, nomeequipa1);
  jogo1->equipa2 = can_fail_malloc(strlen(nomeequipa2) + 1);
  strcpy(jogo1->equipa2, nomeequipa2);
  if(resultado1 > resultado2) adicionaVitoria(tabelaEquipas, nomeequipa1);
  if(resultado1 < resultado2) adicionaVitoria(tabelaEquipas, nomeequipa2);
  jogo1->pontos1 = resultado1;
  jogo1->pontos2 = resultado2;
  tamanhoLista++;
  listaL = can_fail_realloc(listaL, sizeof(jogo) * tamanhoLista);
  listaL[tamanhoLista - 1] = *jogo1;
  return 0;
}

hashJ * criaHash(){
  int i;
  hashJ * anexo = can_fail_malloc(sizeof(hashJ));

  anexo->entradas = can_fail_malloc(sizeof(jogo *) * 1000);
  for(i = 0; i < 1000; i++){
    anexo->entradas[i] = NULL;
  }
  return anexo;
}

void imprimeLista(int nl){
  int i;
  for(i = 0; i < tamanhoLista; i++){
    printf("%d %s %s %s %d %d\n", nl, listaL[i].nome, listaL[i].equipa1, listaL[i].equipa2, listaL[i].pontos1, listaL[i].pontos2);
  }
}

void removeLista(char * nome){
  int i, t;
  for(i = 0; i < tamanhoLista; i++){
    if(strcmp(listaL[i].nome, nome) == 0){
      t = i;
      break;
    }
  }
  for(i = t; i < (tamanhoLista - 1); i++){
    listaL[i] = listaL[i + 1];
  }
  tamanhoLista--;
  listaL = can_fail_realloc(listaL, sizeof(jogo) * tamanhoLista);
}

/* remove jogo da hashtable, da lista ordenada, e depois remove a vitoria da equipa que ganhou porque o jogo deixa de existir */

void removeJogo(hashJ * lolada, hashE * e, char * nome, int nl){
  int chave;
  jogo * jogoz, * outro;
  chave = hash(nome);
  jogoz = lolada->entradas[chave];
  if(!jogoz){
    printf("%d Jogo inexistente.\n", nl);
    return;
  }
  if(strcmp(lolada->entradas[chave]->nome, nome)== 0){
  if(lolada->entradas[chave]->pontos1 > lolada->entradas[chave]->pontos2){
      retiraVitoria(e, lolada->entradas[chave]->equipa1);
    }
    if(lolada->entradas[chave]->pontos1 < lolada->entradas[chave]->pontos2){
      retiraVitoria(e, lolada->entradas[chave]->equipa2);
    }
    lolada->entradas[chave] = lolada->entradas[chave]->next;
removeLista(nome);
    free(jogoz->nome);
    free(jogoz);
    return;
  }

  outro = jogoz;
  jogoz = outro->next;

  while(jogoz != NULL){
    if(strcmp(outro->next->nome, nome) == 0){
      outro->next = jogoz->next;
      if(outro->pontos1 > outro->pontos2){
        retiraVitoria(e, outro->equipa1);
      }
      if(outro->pontos1 < outro->pontos2){
        retiraVitoria(e, outro->equipa2);
      }
      removeLista(nome);
      free(jogoz->nome);
      free(jogoz);
      return;
    }
  }
}

/* ajusta os pontos e depois muda a vitoria para a nova equipa correta, se mudar de vencedor */

void alterapontos(hashJ * omega, hashE * e, char * nome, int pontos1, int pontos2, int nl) {
  jogo * tau;
  tau = procuraJogo(omega, nome);
  if(!tau){
    printf("%d Jogo inexistente.\n", nl);
    return;
  }
  if(tau->pontos1 > tau->pontos2 && pontos1 < pontos2){
    retiraVitoria(e, tau->equipa1);
    adicionaVitoria(e, tau->equipa2);
  } else if(tau->pontos1 > tau->pontos2 && pontos1 == pontos2){
    retiraVitoria(e, tau->equipa1);
  } else if(tau->pontos1 == tau->pontos2 && pontos1 > pontos2){
    adicionaVitoria(e, tau->equipa1);
  } else if(tau->pontos1 == tau->pontos2 && pontos1 < pontos2){
    adicionaVitoria(e, tau->equipa2);
  } else if(tau->pontos1 < tau->pontos2 && pontos1 > pontos2){
    adicionaVitoria(e, tau->equipa1);
    retiraVitoria(e, tau->equipa2);
  }else if(tau->pontos1 < tau->pontos2 && pontos1 == pontos2){
    retiraVitoria(e, tau->equipa2);
  }
  tau->pontos1 = pontos1;
  tau->pontos2 = pontos2;
}
