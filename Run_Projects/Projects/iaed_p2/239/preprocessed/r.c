/*File generated by PreProcessor.py*/


#include "projeto2.h"


void r(GAME *hashG[], int row)
{
  int index;
  GAME *searcher_game;
  GAME *before_link;
  char name[1023];
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  index = hash_function(name);
  searcher_game = hashG[index];
  before_link = searcher_game->link;
  while (strcmp(searcher_game->name, name) != 0)
  {
    if (searcher_game->link == 0)
    {
      printf("%d Jogo inexistente.", row);
      return;
    }
    else
    {
      
    }

    searcher_game = searcher_game->link;
    before_link->link = searcher_game;
  }

  before_link->link = searcher_game->link;
  free(searcher_game);
  return;
}

