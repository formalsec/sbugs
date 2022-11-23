#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "projeto2.h"

/*
ARGUMENTOS: Nome do jogo que se tencione apagar do sistema.

OBJETIVO: Apagar um jogo dado um nome.
Caso o nome do jogo inserido nao exista no sistema, mostrar o erro
"Jogo inexistente".

*/

void r(GAME* hashG[], int row)
{
  int index;
  GAME* searcher_game;
  GAME* before_link;
  char name[MAX_STRING];
  getchar();
  scanf("%[^\n]", name);
  index = hash_function(name);
  searcher_game = hashG[index];
  before_link = searcher_game->link;

  while(strcmp(searcher_game->name,name) != 0)
  {
    if(searcher_game->link == NULL)
    {
      printf("%d Jogo inexistente.", row);

      return;
    }

    searcher_game = searcher_game->link;
    before_link->link = searcher_game;
  }

  before_link->link = searcher_game->link;
  free(searcher_game);

  return;
}
