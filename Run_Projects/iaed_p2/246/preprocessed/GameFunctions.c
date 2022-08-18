/*File generated by PreProcessor.py*/


#include "structs.h"


link_game command_a(link_game *htable_game, link_team *htable_team, char *name, char *t1, char *t2, int r1, int r2, int NL_counter)
{
  int a = hash(name);
  link_game aux = 0;
  link_team aux_1 = lookup_team(htable_team, t1);
  link_team aux_2 = lookup_team(htable_team, t2);
  if (lookup_game(htable_game, name) != 0)
  {
    {
      printf("%d Jogo existente.\n", NL_counter);
    }
  }
  else
  {
    if ((aux_1 == 0) || (aux_2 == 0))
    {
      {
        printf("%d Equipa inexistente.\n", NL_counter);
      }
    }
    else
    {
      {
        aux = NEWgame(name, aux_1, aux_2, r1, r2);
        aux->next = htable_game[a];
        htable_game[a] = aux;
        if (r1 > r2)
        {
          {
            aux_1->v += 1;
          }
        }
        else
        {
          if (r1 < r2)
          {
            {
              aux_2->v += 1;
            }
          }
          else
          {
            
          }

        }

        return aux;
      }
    }

  }

  return aux;
}

void command_l(link_game_order ordergamelist, int NL_counter)
{
  if (ordergamelist == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  command_l(ordergamelist->next, NL_counter);
  printf("%d %s %s %s %d %d\n", NL_counter, ordergamelist->element->name, ordergamelist->element->element_t1->name, ordergamelist->element->element_t2->name, ordergamelist->element->r1, ordergamelist->element->r2);
}

void command_p(link_game *htable_game, char *name, int NL_counter)
{
  link_game game = lookup_game(htable_game, name);
  if (game != 0)
  {
    {
      printf("%d %s %s %s %d %d\n", NL_counter, game->name, game->element_t1->name, game->element_t2->name, game->r1, game->r2);
    }
  }
  else
  {
    {
      printf("%d Jogo inexistente.\n", NL_counter);
    }
  }

  return;
}

link_game_order command_r(link_game *htable_game, link_game_order head, char *text, int NL_counter)
{
  int a = hash(text);
  link_game tempGame;
  link_game_order t;
  link_game_order prev;
  tempGame = lookup_game(htable_game, text);
  if (tempGame == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL_counter);
      return head;
    }
  }
  else
  {
    {
      for (t = head, prev = 0; t != 0; prev = t, t = t->next)
      {
        if (strcmp(t->element->name, text) == 0)
        {
          {
            if (t == head)
            {
              head = t->next;
            }
            else
            {
              prev->next = t->next;
            }

            free(t);
            break;
          }
        }
        else
        {
          
        }

      }

      if (tempGame->r1 > tempGame->r2)
      {
        {
          tempGame->element_t1->v--;
        }
      }
      else
      {
        if (tempGame->r1 < tempGame->r2)
        {
          {
            tempGame->element_t2->v--;
          }
        }
        else
        {
          
        }

      }

      htable_game[a] = deletegame(htable_game[a], text);
    }
  }

  return head;
}

int command_s(link_game *htable_game, char *GameName, int score1, int score2, int NL_counter)
{
  link_game auxGame;
  auxGame = lookup_game(htable_game, GameName);
  if (auxGame == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL_counter);
      return 0;
    }
  }
  else
  {
    {
      if (auxGame->r1 > auxGame->r2)
      {
        {
          auxGame->element_t1->v--;
        }
      }
      else
      {
        
      }

      if (auxGame->r1 < auxGame->r2)
      {
        {
          auxGame->element_t2->v--;
        }
      }
      else
      {
        
      }

      if (score1 > score2)
      {
        {
          auxGame->element_t1->v++;
        }
      }
      else
      {
        
      }

      if (score1 < score2)
      {
        {
          auxGame->element_t2->v++;
        }
      }
      else
      {
        
      }

      auxGame->r1 = score1;
      auxGame->r2 = score2;
      return 1;
    }
  }

  return 0;
}

