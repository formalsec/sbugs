/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"


void init()
{
  tableJInit(200);
  initArrayJ(100);
  tableEInit(200);
  initArrayE(100);
}

void add_game(char *name, int linha, char *nameE1, char *nameE2, int score1, int score2)
{
  equipa e1;
  equipa e2;
  jogo toAdd;
  if (tableJSearch(name) == 0)
  {
    {
      e1 = tableESearch(nameE1);
      e2 = tableESearch(nameE2);
      if ((e2 != 0) && (e1 != 0))
      {
        {
          toAdd = newJogo(name, e1, e2, score1, score2);
          tableJInsert(toAdd, insertArrayJ(toAdd));
          if (score1 > score2)
          {
            {
              e1->victorys++;
            }
          }
          else
          {
            
          }

          if (score2 > score1)
          {
            {
              e2->victorys++;
            }
          }
          else
          {
            
          }

        }
      }
      else
      {
        {
          printf("%d Equipa inexistente.\n", linha);
        }
      }

    }
  }
  else
  {
    {
      printf("%d Jogo existente.\n", linha);
    }
  }

}

void add_team(char *name, int linha)
{
  equipa e;
  if (tableESearch(name) == 0)
  {
    {
      e = newEquipa(name);
      insertArrayE(e);
      tableEInsert(e);
    }
  }
  else
  {
    {
      printf("%d Equipa existente.\n", linha);
    }
  }

}

void search_game(char *name)
{
  element searched = tableJSearch(name);
  if (searched != 0)
  {
    {
      printJogo(searched->game);
    }
  }
  else
  {
    {
      printf("Jogo inexistente.\n");
    }
  }

}

void search_team(char *name)
{
  equipa searched = tableESearch(name);
  if (searched != 0)
  {
    {
      printEquipa(searched);
    }
  }
  else
  {
    {
      printf("Equipa inexistente.\n");
    }
  }

}

void delete_game(char *name, int linha)
{
  element searched = tableJSearch(name);
  if (searched == 0)
  {
    {
      printf("%d Jogo inexistente.\n", linha);
    }
  }
  else
  {
    {
      tableJDelete(searched->game);
      freeJogo(searched->game);
      searched->game = 0;
    }
  }

}

void change_score(char *name, int score1, int score2, int linha)
{
  element searched = tableJSearch(name);
  if (searched != 0)
  {
    {
      if (searched->game->r1 > searched->game->r2)
      {
        {
          if (score1 == score2)
          {
            {
              removeVictory(searched->game->equipa1);
            }
          }
          else
          {
            
          }

          if (score1 < score2)
          {
            {
              removeVictory(searched->game->equipa1);
              addVictory(searched->game->equipa2);
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

      if (searched->game->r1 < searched->game->r2)
      {
        {
          if (score1 == score2)
          {
            {
              removeVictory(searched->game->equipa2);
            }
          }
          else
          {
            
          }

          if (score1 > score2)
          {
            {
              removeVictory(searched->game->equipa2);
              addVictory(searched->game->equipa1);
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

      if (searched->game->r1 == searched->game->r2)
      {
        {
          if (score1 > score2)
          {
            {
              addVictory(searched->game->equipa1);
            }
          }
          else
          {
            
          }

          if (score1 < score2)
          {
            {
              addVictory(searched->game->equipa2);
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

      changeScore(searched->game, score1, score2);
    }
  }
  else
  {
    {
      printf("%d Jogo inexistente.\n", linha);
    }
  }

}

void print_games(int linha)
{
  printJogos(linha);
}

void print_teams(int linha)
{
  if (getNequipas() > 0)
  {
    {
      int n = putBiggerOnTop();
      heapsort(n);
      printEquipas(linha, n);
    }
  }
  else
  {
    
  }

}

void free_all()
{
  freeArrayJ();
  freeArrayE();
  freeTableE();
  freeTableJ();
}

