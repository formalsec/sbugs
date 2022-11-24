#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "FUNCTIONS.h"
#include "TEAM.h"
#include "MATCH.h"
#include "TEAMHTABLE.h"
#include "MATCHHTABLE.h"

/*Recebe o input e adiciona um novo jogo a hashtable e a linked list de jogos,
  sendo o input as informacoes do novo jogo.
  Elimina a lista de equipas com mais vitorias se a equipa vencedora tiver o
  score maior ou igual ao da(s) equipa(s) com mais vitorias.
  Devolve erro caso ja exista alguma equipa com o nome recebido no input,
  os se as equipas recebidas nao existirem.*/
void fa(int counter){
  char* name;
  char* team1;
  char* team2;
  Match m;
  int score1, score2;

  name = (char*)can_fail_malloc(sizeof(char)*STR);
  team1 = (char*)can_fail_malloc(sizeof(char)*STR);
  team2 = (char*)can_fail_malloc(sizeof(char)*STR);

  scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d%*c",name, team1, team2, &score1, &score2);

  if (matchSearch(name) != NULL){
    printf("%d Jogo existente.\n",counter);
  }
  else{
    if (teamSearch(team1) == NULL || teamSearch(team2) == NULL){
      printf("%d Equipa inexistente.\n",counter);
    }
    else{
      Team t;
      m = newMatch(name, team1, team2, score1, score2);
      matchInsert(m);
      t = getWinTeam(m);
      if(THeadList != NULL && ((t != NULL && t->score >= THeadList->team->score) ||
        (t == NULL && score1 >= THeadList->team->score))){
        TfreeHead(THeadList);
        TlistInit();
      }
    }
  }
  free(name);
  free(team1);
  free(team2);
}

/*Adiciona uma nova equipa a hashtable, sendo o input recebido o nome da nova equipa.
  Elimina a lista de equipas com maior numero de vitorias se o seu score nao for
  inferior ao maximo de vitorias das equipas, ou seja, elimina a lista caso o
  maximo de vitorias seja 0. Imprime erro se a equipa nao existir*/
void fA(int counter){
  Team t;
  char* name = (char*)can_fail_malloc(sizeof(char)*STR);
  scanf(" %[^:\n]%*c",name);

  if (teamSearch(name) == NULL){
    t = newTeam(name);
    teamInsert(t);
    if(!(THeadList != NULL && t != NULL && t->score < THeadList->team->score)){
      TfreeHead(THeadList);
      TlistInit();
    }
  }
  else{
    printf("%d Equipa existente.\n",counter);
  }
  free(name);
}

/*Imprime os jogos e respetivas informacoes pela ordem em que foram inseridos,
  recorrendo a linked list de jogos, nao imprime os jogos cujos nomes sao ':,
  uma vez que estes correspondem a jogos eliminados'*/
void fl(int counter){
  matchNode a;
  getchar();

  for(a=head; a!=NULL; a=a->next){
    if(strcmp(a->match->name,":") != 0){
      printf("%d %s %s %s %d %d\n", counter, a->match->name, a->match->team1->name,
        a->match->team2->name, a->match->score1, a->match->score2);
    }
  }
}

/*Recebe como o input o nome do jogo e imprime as suas informacoes. Caso o jogo
  nao exista e devolvido um erro.*/
void fp(int counter){
  matchNode a;
  char* name = (char*)can_fail_malloc(sizeof(char)*STR);

  scanf(" %[^:\n]%*c",name);
  a = matchSearch(name);
  if (a == NULL){
    printf("%d Jogo inexistente.\n",counter);
  }
  else{
    printf("%d %s %s %s %d %d\n", counter, a->match->name, a->match->team1->name,
      a->match->team2->name, a->match->score1, a->match->score2);
  }
  free(name);
}

/*Recebe como o input o nome da equipa a pesquisar e imprime as suas informacoes.
  Caso esta nao exista e devolvido um erro.*/
void fP(int counter){
  teamNode n;
  char* name = (char*)can_fail_malloc(sizeof(char)*STR);

  scanf(" %[^:\n]%*c",name);
  n = teamSearch(name);
  if (n == NULL){
    printf("%d Equipa inexistente.\n",counter);
  }
  else{
    printf("%d %s %d\n",counter, n->team->name, n->team->score);
  }
  free(name);
}

/*Recebe como input o nome do jogo a remover. A lista de equipas com mais vitorias
  e apagada caso o a equipa vencedora (ou, em caso de empate, ambas as equipas)
  esteja na lista. Se o jogo nao existir, e retornado um erro.*/
void fr(int counter){
  matchNode m;
  char* name = (char*)can_fail_malloc(sizeof(char)*STR);
  scanf(" %[^:\n]%*c",name);
  m = matchSearch(name);
  if (m == NULL){
    printf("%d Jogo inexistente.\n",counter);
  }
  else{
    Team t;
    int tscore, eq;
    t = getWinTeam(m->match);
    if (t != NULL){
      tscore = t->score;
    }
    eq = m->match->team1->score;
    removeScores(m->match);
    matchDelete(m->match);
    if(THeadList != NULL && ((t != NULL && tscore >= THeadList->team->score) ||
    (t == NULL && eq >= THeadList->team->score))){
      TfreeHead(THeadList);
      TlistInit();
    }
  }
  free(name);
}

/*Recebe como input o nome do jogo e os novos scores de cada equipa. Caso o jogo
  nao exista, e retornado um erro.
  Caso contrario, sao alterados os scores no determinado jogo e corrigidos os
  scores das equipas vencedoras, caso seja necessario. Se a equipa vencedora (ou
  ambas as equipas, em caso de empate) antes da alteracao se encontre na lista
  de maior numero de vitorias, ou se o score da nova equipa vencedora for maior
   ou igual ao score maximo das equipas, a lista que contem as equipas de score
   maximo e eiminada.
  */
void fs(int counter){
  matchNode match;
  int s1, s2;
  char* name = (char*)can_fail_malloc(sizeof(char)*STR);
  scanf(" %[^:\n]:%d:%d%*c",name , &s1, &s2);
  match = matchSearch(name);
  if (match == NULL){
    printf("%d Jogo inexistente.\n",counter);
  }
  else{
    Team win1, win2, loser1;
    int win1score;
    win1 = getWinTeam(match->match);
    if(win1 != NULL){
      win1score = win1->score;
    }
    loser1 = getLoserTeam(match->match);

    changeScores(match->match, s1, s2);
    win2 = getWinTeam(match->match);
    if((THeadList != NULL) && ((win1 != NULL && win2 != NULL && win1 != win2 && win1score >= THeadList->team->score) || (loser1 != NULL && win2 != NULL && win2 == loser1 && loser1->score >= THeadList->team->score)
        || (win1 == NULL && win2 != NULL && win2->score >= THeadList->team->score) || (win1!=NULL && win2 == NULL && win1score >= THeadList->team->score))){
      TfreeHead(THeadList);
      TlistInit();
    }
  }
  free(name);
}

/*Imprime as equipas com maior numero de vitorias, utilizando a linked list.
  Caso a lista seja NULL, e percorrida a hashtable para encontrar as equipas com
  maior numero de vitorias, caso contrario, imprime a lista ja existente.
  Nao devolve nada caso nao exista nenhuma equipa*/
void fg(int counter){
  teamNode aux;
  int i, max = -1;
  getchar();

  if(THeadList == NULL){
    for (i = 0; i < MAXTEAM; i++){
      for(aux=teamHeads[i]; aux!=NULL; aux=aux->next){
        if(aux->team->score > max){
          TfreeHead(THeadList);
          TlistInit();
          addTeamNodeList(aux->team);
          max = aux->team->score;
        }
        else if(aux->team->score == max){
          addTeamNodeList(aux->team);
        }
      }
    }
  }

  if(THeadList != NULL){
    printf("%d Melhores %d\n",counter,THeadList->team->score);
    for(aux=THeadList; aux!=NULL; aux=aux->next){
      printf("%d * %s\n", counter, aux->team->name);
    }
  }
}

/*Chama funcoes auxiliares para dar free da hashtable das equipas e dos jogos,
  da linked list de maior numero de vitorias e a dos jogos ordenados.*/
void fx(){
  MfreeHead(head);
  TfreeHead(THeadList);
  matchHashFREE();
  teamHashFREE();

}
