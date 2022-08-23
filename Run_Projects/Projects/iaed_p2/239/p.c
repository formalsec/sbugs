#include "projeto2.h"

/*
ARGUMENTOS: Nome do jogo que se quer procurar

OBJETIVO: Procurar um jogo com o nome dado, se o jogo nao existir,
dar o error "jogo inexistente". Se o jogo procurado existir no sistema, 
imprimir um linha do formato:
Nome do Jogo - Equipa 1 - Equipa 2 - Score 1 - Score 2. Sendo Equipa 1 
e Equipa 2 as equipas que participam nesse jogo e Score 1 e Score 2 
o Score obtido por ambas as equipas nesse mesmo jogo.

*/

void p(GAME* hashG[], int row)
{
  int index;
  GAME* searcher_game;
  char name[MAX_STRING];
  getchar();
  scanf("%[^\n]", name);
  index = hash_function(name);
  searcher_game = hashG[index];

  while(strcmp(searcher_game->name,name) != 0)
  {
    if(searcher_game->link == NULL)
    {
      printf("%d Jogo inexistente.", row);
      
      return;
    }

    searcher_game = searcher_game->link;
  }

  printf("%d %s %s %s %d %d", row, searcher_game->name,
  searcher_game->team1->name, searcher_game->team2->name,
  searcher_game->team1->score, searcher_game->team2->score);

  return;
}
