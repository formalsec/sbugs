#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "projeto2.h"

void x(TEAM* hashT[], GAME* hashG[])
{
  TEAM* searcher_team;
  TEAM* next_team;
  GAME* searcher_game;
  GAME* next_game;
  int i;

  for (i = 0; i < hash_size ; i++)
  {
    searcher_team = hashT[i];

    while(searcher_team->link != NULL)
    {
      next_team = searcher_team->link;
      free(searcher_team);
      searcher_team = next_team;
    }

    free(searcher_team);
    searcher_game = hashG[i];

    while(searcher_game->link != NULL)
    {
      next_game = searcher_game->link;
      free(searcher_game);
      searcher_game = next_game;
    }

    free(searcher_game);
  }
  
  return;
}
