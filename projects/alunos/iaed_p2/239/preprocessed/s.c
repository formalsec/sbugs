#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "projeto2.h"


void s(GAME *hashG[], int row)
{
  int index;
  int score1;
  int score2;
  GAME *searcher_game;
  char name[1023];
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  index = hash_function(name);
  searcher_game = hashG[index];
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
  }

  if ((searcher_game->score1 > searcher_game->score2) && (score2 > score1))
  {
    searcher_game->team1->score--;
    searcher_game->team2->score++;
  }
  else
  {
    if ((searcher_game->score2 > searcher_game->score1) && (score1 > score2))
    {
      searcher_game->team1->score++;
      searcher_game->team2->score--;
    }
    else
    {
      
    }

  }

  searcher_game->score1 = score1;
  searcher_game->score2 = score2;
  return;
}

