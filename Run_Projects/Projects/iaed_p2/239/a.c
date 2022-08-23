#include "projeto2.h"

/*
ARGUMENTOS: Um nome para o jogo com maximo de 1023 caracteres, cada jogo vai ser constituido por duas equipas
cujo nome dessas tem tambem o maximo de 1023 caracteres e ainda um score que tem dois numeros, o resultado
de uma equipa e o resultado da outra, esses numeros tem que ser inteiros positivos

OBJETIVO: Adicionar um novo jogo verificando se esse jogo nao existe ja e, se existir um jogo com esse nome
 no sistema, deteta um dos erros.
 Se se tentar adicionar uma equipa a um jogo que nao exista, deteta-se o outro erro existente.
 Se um dos erros ocorrer, nao se consegue criar um novo jogo.
*/

void a(GAME* hashG[], TEAM* hashT[], int row)
{
  char team1[MAX_STRING];
  char team2[MAX_STRING];
  int score1;
  int score2;
  int index;
  char name[MAX_STRING];
  TEAM* searcher_team = *hashT;
  GAME* searcher_game = *hashG;
  GAME* new_game;
  getchar();
  scanf("%[^:]:%[^:]:%[^:]:%d:%d", name, team1, team2, &score1, &score2);

  index = hash_function(team1);
  searcher_team = hashT[index];

  while(strcmp(searcher_team->name,team1) != 0)
  {
    if(searcher_team == NULL)
    {
      printf("%d Equipa inexistente.",row);
      return;
    }
    searcher_team = searcher_team->link;
  }

  index = hash_function(team2);
  searcher_team = hashT[index];
  while(strcmp(searcher_team->name,team2) != 0)
  {
    if(searcher_team == NULL)
    {
      printf("%d Equipa inexistente.",row);
      return;
    }
    searcher_team = searcher_team->link;
  }

  index = hash_function(name);
  searcher_game = hashG[index];
  while(strcmp(searcher_game->name,name) != 0)
  {
    if((searcher_game->link == NULL) && (strcmp(searcher_game->name,"\0") == 0))
    {
      new_game = (GAME*)calloc(1,sizeof(GAME*));
      strcpy(new_game->name,name);
      index = hash_function(team1);
      searcher_team = hashT[index];

      while(strcmp(searcher_team->name,team1) != 0)
        searcher_team = searcher_team->link;

      if(score1 > score2)
        searcher_team->score++;
      new_game->team1 = searcher_team;
      index = hash_function(team2);
      searcher_team = hashT[index];

      while(strcmp(searcher_team->name,team2) != 0)
        searcher_team = searcher_team->link;

      if(score2 > score1)
        searcher_team->score++;
      new_game->team2 = searcher_team;
      new_game->score1 = score1;
      new_game->score2 = score2;
      return;
    }

    searcher_game = searcher_game->link;
  }

  printf("%d Jogo existente",row);
  
  return;
}
