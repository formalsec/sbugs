/*File generated by PreProcessor.py*/


#include "allfunctions.h"


void _addTeam_(HashTeam *table, int NL)
{
  char buffer[1024];
  Team team;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  team = tHashSearch(*table, buffer);
  if (team)
  {
    {
      printf("%d Equipa existente.\n", NL);
    }
  }
  else
  {
    {
      *table = tHashInsert(table, newTeam(buffer));
    }
  }

}

void _searchTeam_(HashTeam table, int NL)
{
  char buffer[1024];
  Team team;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  team = tHashSearch(table, buffer);
  if (!team)
  {
    {
      printf("%d Equipa inexistente.\n", NL);
    }
  }
  else
  {
    {
      printf("%d ", NL);
      printTeam(team);
    }
  }

}

void _addGame_(HashGame *gTable, GameLink *gList, HashTeam tTable, int NL)
{
  int score1;
  int score2;
  char name[1024];
  char team1[1024];
  char team2[1024];
  Game game;
  Team t1;
  Team t2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int team1_index = 0; team1_index < 10; team1_index++)
  {
    team1[team1_index] = new_sym_var(sizeof(char) * 8);
  }

  team1[10 - 1] = '\0';
  for (int team2_index = 0; team2_index < 10; team2_index++)
  {
    team2[team2_index] = new_sym_var(sizeof(char) * 8);
  }

  team2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  game = gHashSearch(*gTable, name);
  t1 = tHashSearch(tTable, team1);
  t2 = tHashSearch(tTable, team2);
  if (game)
  {
    {
      printf("%d Jogo existente.\n", NL);
    }
  }
  else
  {
    if ((!t1) || (!t2))
    {
      {
        printf("%d Equipa inexistente.\n", NL);
      }
    }
    else
    {
      {
        if (score1 > score2)
        {
          {
            t1->wins++;
          }
        }
        else
        {
          if (score2 > score1)
          {
            {
              t2->wins++;
            }
          }
          else
          {
            
          }

        }

        game = newGame(name, t1, t2, score1, score2);
        *gTable = gHashInsert(gTable, game);
        *gList = insertGameList(*gList, game);
      }
    }

  }

}

void _searchGame_(HashGame table, int NL)
{
  char buffer[1024];
  Game game;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  game = gHashSearch(table, buffer);
  if (game)
  {
    {
      printf("%d ", NL);
      printGame(game);
    }
  }
  else
  {
    {
      printf("%u Jogo inexistente.\n", NL);
    }
  }

}

void _deleteGame_(HashGame table, GameLink *list, int NL)
{
  char buffer[1024];
  Game game;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  game = gHashSearch(table, buffer);
  if (!game)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      if (game->score1 > game->score2)
      {
        {
          game->team1->wins--;
        }
      }
      else
      {
        if (game->score1 < game->score2)
        {
          {
            game->team2->wins--;
          }
        }
        else
        {
          
        }

      }

      gHashDelete(table, buffer);
      *list = removeGameList(*list, buffer);
    }
  }

}

void _listGames_(GameLink list, int NL)
{
  GameLink aux;
  if (list)
  {
    {
      aux = list->prev;
      do
      {
        printf("%d ", NL);
        printGame(aux->game);
        aux = aux->prev;
      }
      while (aux != list->prev);
    }
  }
  else
  {
    
  }

}

void _changeScore_(HashGame table, int NL)
{
  char buffer[1024];
  int oldS1;
  int oldS2;
  int score1;
  int score2;
  Game game;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  game = gHashSearch(table, buffer);
  if (!game)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      oldS1 = game->score1;
      oldS2 = game->score2;
      game->score1 = score1;
      game->score2 = score2;
      if (oldS1 == oldS2)
      {
        {
          if (score1 > score2)
          {
            {
              game->team1->wins++;
            }
          }
          else
          {
            if (score2 > score1)
            {
              {
                game->team2->wins++;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        
      }

      if (oldS1 > oldS2)
      {
        {
          if (score1 == score2)
          {
            {
              game->team1->wins--;
            }
          }
          else
          {
            if (score2 > score1)
            {
              {
                game->team1->wins--;
                game->team2->wins++;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        
      }

      if (oldS2 > oldS1)
      {
        {
          if (score2 == score1)
          {
            {
              game->team2->wins--;
            }
          }
          else
          {
            if (score1 > score2)
            {
              {
                game->team2->wins--;
                game->team1->wins++;
              }
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        
      }

    }
  }

}

void _winningTeams_(HashTeam table, int NL)
{
  int i;
  int j = 0;
  int max;
  int qty;
  Team *unsorted;
  Team aux;
  getMaxWins(table, &max, &qty);
  if (max != (-1))
  {
    {
      unsorted = (Team *) malloc(qty * (sizeof(struct team)));
      printf("%d Melhores %d\n", NL, max);
      for (i = 0; i < table->M; i++)
      {
        if (table->teams[i])
        {
          {
            aux = table->teams[i];
            if (aux->wins == max)
            {
              {
                *(unsorted + j) = aux;
                j++;
              }
            }
            else
            {
              
            }

          }
        }
        else
        {
          
        }

      }

      sortAndPrint(unsorted, j, NL);
      free(unsorted);
    }
  }
  else
  {
    
  }

}

int getMaxWins(HashTeam table, int *max, int *qty)
{
  int tempmax = -1;
  int tempqty = 0;
  int i;
  for (i = 0; i < table->M; i++)
  {
    if (table->teams[i])
    {
      {
        if (table->teams[i]->wins > tempmax)
        {
          {
            tempqty = 0;
            tempmax = table->teams[i]->wins;
          }
        }
        else
        {
          
        }

        if (table->teams[i]->wins == tempmax)
        {
          {
            tempqty++;
          }
        }
        else
        {
          
        }

      }
    }
    else
    {
      
    }

  }

  *max = tempmax;
  *qty = tempqty;
  return 0;
}

int myCompare(const void *a, const void *b)
{
  return strcmp((*((Team *) a))->name, (*((Team *) b))->name);
}

void sortAndPrint(Team *unsorted, int qty, int NL)
{
  int i;
  qsort(unsorted, qty, sizeof(Team), myCompare);
  for (i = 0; i < qty; ++i)
  {
    printf("%d * %s\n", NL, unsorted[i]->name);
  }

}

