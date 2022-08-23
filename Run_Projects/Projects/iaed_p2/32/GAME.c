#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "GAME.h"

/*:::::::::::::::::::::::::::FUNCOES PRINCIPAIS:::::::::::::::::::::::::::*/

/*
Recebe os nomes do jogo e das equipas e o resultado
Verifica se o jogo e as equipas existem. Adiciona o jogo na hashtable e
na lista ligada auxiliar para guardar a ordme pela qual foram inseridos*/
void NewGame(int line){
  char* name = malloc(sizeof(char)*MAX_STR);
  char* name1 = malloc(sizeof(char)*MAX_STR);
  char* name2 = malloc(sizeof(char)*MAX_STR);
  int i,i1,i2;
  int score1, score2;
  gamelink t;
  link t1,t2;
  scanf(" %[^:]:%[^:]:%[^:]:%d:%d",name,name1,name2,&score1,&score2);
  getchar();

  i = hash_game(name);
  t = searchHashGame(name, g_heads[i]);
  if(!t){
    i1 = hash_team(name1);
    i2 = hash_team(name2);

    t1 = searchHashTeam(name1, t_heads[i1]);
    t2 = searchHashTeam(name2, t_heads[i2]);

    if(t1 == NULL || t2 == NULL){
      printf("%d Equipa inexistente.\n", line);
    }
    else{
      g_heads[i] = insertHashGame(name,name1,name2, score1, score2, g_heads[i]);
      insertListGames(name);
      if(score1>score2) t1->team->wins++;
      else if(score1<score2) t2->team->wins++;

      if(teams_list != NULL && teams_list->team->wins > 0){
        freeTeamList(teams_list);
        TeamListInit();
      }
    }
  }
  else{
    printf("%d Jogo existente.\n",line);
  }
  free(name);
  free(name1);
  free(name2);
}

/*
Recebe o nome do jogo
Verifica se este existe e faz print das suas caracteristicas*/
void SearchGame(int line){
  char* name = malloc(sizeof(char)*1024);
  gamelink l;
  int i;

  scanf(" %s", name);
  getchar();

  i = hash_game(name);
  l = searchHashGame(name, g_heads[i]);
  if(l!=NULL){
    printf("%d %s %s %s %d %d\n", line, name, l->game->team1, l->game->team2, l->game->score1, l->game->score2);
  }
  else printf("%d Jogo inexistente.\n", line);
  free(name);
}

/*
Recebe o nome do jogo a eliminar
Verifica se existe e elimina da hashtable e da lista ligada auxiliar*/
void DeleteGame(int line){
  char* name = malloc(sizeof(char)*MAX_STR);
  gamelink l;
  int i;

  scanf(" %[^:\n]", name);
  getchar();

  i = hash_game(name);
  l = searchHashGame(name, g_heads[i]);
  if(l != NULL){
    if(l->game->score1 > l->game->score2) decreaseWins(l->game->team1);
    else if(l->game->score1 < l->game->score2) decreaseWins(l->game->team2);
    g_heads[i] = deleteHashGame(name, g_heads[i]);
    delete_gamelist(name);
    freeTeamList(teams_list);
    TeamListInit();
  }
  else{
    printf("%d Jogo inexistente.\n", line);
  }
  free(name);
}

/*
Faz print dos jogos guardados na lista ligada auxiliar*/
void ListAllGames(int line){
  int i;
  GamesList a;
  gamelink link;
  getchar();

  for (a = list_head; a != NULL; a = a->next) {
    i = hash_game(a->name);
    link = searchHashGame(a->name, g_heads[i]);
    printf("%d %s %s %s %d %d\n", line,link->game->name, link->game->team1, link->game->team2, link->game->score1, link->game->score2);
  }
}

/*
Recebe o nome de um jogo e o novo resultado
Verifica se existe e altera o resultado do jogo e o numero de vitorias
das equipas.*/
void Change_Score(int line){
  char* name = malloc(sizeof(char)*MAX_STR);
  int i,score1,score2;
  gamelink l;
  scanf(" %[^:\n]:%d:%d", name,&score1,&score2);
  getchar();

  i = hash_game(name);
  l = searchHashGame(name, g_heads[i]);





  if(l != NULL){
    if(score1>score2 && l->game->score2 > l->game->score1){
      increaseWins(l->game->team1);
      decreaseWins(l->game->team2);
    }
    else if(score1<score2 && l->game->score2 < l->game->score1){
      increaseWins(l->game->team2);
      decreaseWins(l->game->team1);
    }
    else if(score1>score2 && l->game->score2 == l->game->score1){
      increaseWins(l->game->team1);
    }
    else if(score1<score2 && l->game->score2 == l->game->score1){
      increaseWins(l->game->team2);
    }
    else if(score1 == score2){
      if(l->game->score2 > l->game->score1) decreaseWins(l->game->team2);
      else if(l->game->score1 > l->game->score2) decreaseWins(l->game->team1);
    }
    l->game->score1 = score1;
    l->game->score2 = score2;
    free(name);
    freeTeamList(teams_list);
    TeamListInit();
  }
  else{
    printf("%d Jogo inexistente.\n", line);
    free(name);
  }
}


/*:::::::::::::::::::::AUXILIARES HASHTABLE:::::::::::::::::::::*/

/*Funcao hash para os jogos*/
int hash_game(char* v){
  int h = 0, a = 173;
  for (; *v != '\0'; v++)
    h = (a*h + *v) % M_G;
  return h;
}

/*Iniciliazacao da hashtable dos jogos*/
void GameInit(){
  int i;
  g_heads = (gamelink*)malloc(sizeof(gamelink)*M_G);
  for (i = 0; i < M_G; i++)
    g_heads[i] = NULL;
}

/*
Recebe as caracteristicas do jogo a criar
Adiciona na hashtable*/
gamelink insertHashGame(char* name, char*name1, char*name2, int score1, int score2, gamelink head){
  gamelink aux, prev;

  for(aux = head, prev = NULL; aux != NULL; prev = aux,aux = aux->next);
  if(aux == head){
    head = newGameLink(name,name1,name2,score1,score2);
  }
  else{
    prev->next = newGameLink(name,name1,name2,score1,score2);
  }
  return head;
}

/*
Recebe o nome de um jogo
Retorna o gamelink em caso positivo, Null caso contrario*/
gamelink searchHashGame(char* name, gamelink head){
  gamelink aux;
  for (aux = head; aux != NULL; aux = aux -> next) {
		if (strcmp(aux->game->name, name)==0)
			return aux;
  }
  return NULL;
}

/*
Recebe o nome de um jogo
Faz delete
*/
gamelink deleteHashGame(char* name, gamelink head){
  gamelink t, prev;
  for(t = head,  prev = NULL; t != NULL; prev = t, t=t->next){
    if(strcmp(t->game->name, name) == 0){
      if(t == head){
        head = t->next;
      }
      else if(t->next == NULL){
				prev->next = NULL;
			}
      else{
        prev->next = t->next;
      }
      free(t->game->name);
      free(t->game->team1);
      free(t->game->team2);
      free(t->game);
      free(t);
      return head;
    }
  }
  return NULL;
}

/*
Funcao auxiliar para dar free
Free da estrutura hashtables*/
void free_gamelist(gamelink head){
  if(head != NULL){
    free(head->game->name);
    free(head->game->team1);
    free(head->game->team2);
    free(head->game);
    free_gamelist(head->next);
    free(head);
  }
}

/*
Free da estrutura hashtables*/
void freeGameHash(){
  int i;

  for(i=0;i<M;i++){
    free_gamelist(g_heads[i]);
  }
}



/*
Recebe as caracteristicas de um jogo
Cria espaco para um novo gamelink e retorna-o com as novas caracteristicas*/
gamelink newGameLink(char* name, char* name1, char* name2, int score1, int score2){
  size_t size;
  gamelink l = (gamelink)malloc(sizeof(struct GameNode));
  l->game = malloc(sizeof(struct game));

  size = strlen(name) + 1;
  l->game->name = malloc(sizeof(char)*size);
  strncpy(l->game->name, name, size);

  size = strlen(name1) + 1;
  l->game->team1 = malloc(sizeof(char)*size);
  strncpy(l->game->team1, name1, size);

  size = strlen(name2) + 1;
  l->game->team2 = malloc(sizeof(char)*size);
  strncpy(l->game->team2, name2, size);

  l->game->score1 = score1;
  l->game->score2 = score2;

  l->next = NULL;
  return l;
}


/*:::::::::::::::::::::AUXILIARES LISTA LIGADA AUXILIAR:::::::::::::::::::::*/


/*
Recebe o nome do jogo
Adiciona no fim da lista ligada auxliar*/
void insertListGames(char* name) {
	if (list_head == NULL) {
		list_head = tail = new_game_node(name);
	}
	else {
	tail->next = new_game_node(name);
	tail = tail->next;
	}
}

/*
Recebe as caracteristicas de um jogo
Cria espaco para um novo GameList e duarda o nome do jogo*/
GamesList new_game_node(char* name){
  size_t size;
  GamesList game = malloc(sizeof(struct names));

  size = strlen(name) + 1;
  game->name = malloc(sizeof(char*)*size);
  strncpy(game->name,name, size);

  game->next = NULL;
  return game;
}

/*
Recebe o nome do jogo a apagar
Elimina da lista ligada auxliar*/
void delete_gamelist(char* name){
  GamesList t, prev;
  for(t = list_head,  prev = NULL; t != NULL; prev = t, t=t->next){
    if(strcmp(t->name, name) == 0){
      if(t == list_head)
       list_head = t->next;
      else if(t == tail){
        prev->next = NULL;
        tail = prev;
      }
      else
       prev->next = t->next;
      free(t->name);
      free(t);
      return;
    }
  }
}
