/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "shared.h"


void init_games(games **lst_games, int size)
{
  int i;
  for (i = 0; i <= size; i++)
  {
    lst_games[i] = 0;
  }

}

games *new_game(games *game, char *name, char *team1, char *team2, int score1, int score2)
{
  game->name = strduplicate(name);
  game->team1 = strduplicate(team1);
  game->team2 = strduplicate(team2);
  game->score1 = score1;
  game->score2 = score2;
  game->next = 0;
  return game;
}

int look_game(games **lst_games, char *name)
{
  int i = hash(name);
  games *head = lst_games[i];
  for (; head != 0; head = head->next)
  {
    if (strcmp(head->name, name) == 0)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

void insert_new_game(games **lst_games, games *new)
{
  games *head;
  int i = hash(new->name);
  head = lst_games[i];
  lst_games[i] = new;
  new->next = head;
}

games *get_game(games **lst_games, char *name)
{
  int i = hash(name);
  games *head = lst_games[i];
  for (; head != 0; head = head->next)
  {
    if (strcmp(head->name, name) == 0)
    {
      break;
    }
    else
    {
      
    }

  }

  return head;
}

int who_won(int score1, int score2)
{
  if (score1 > score2)
  {
    return 1;
  }
  else
  {
    if (score2 > score1)
    {
      return 2;
    }
    else
    {
      return 0;
    }

  }

}

void remove_game(games **lst_games, games *game)
{
  int i = hash(game->name);
  games *head = lst_games[i];
  if ((strcmp(head->name, game->name) == 0) && (head->next == 0))
  {
    lst_games[i] = 0;
  }
  else
  {
    if (strcmp(head->name, game->name) == 0)
    {
      lst_games[i] = game->next;
    }
    else
    {
      for (; head != 0; head = head->next)
      {
        if (strcmp(head->next->name, game->name) == 0)
        {
          break;
        }
        else
        {
          
        }

      }

      head->next = game->next;
    }

  }

  free(game->name);
  free(game->team1);
  free(game->team2);
  free(game);
}

void clear_the_games(games **lst_games)
{
  games *i;
  games *follow;
  int j;
  for (j = 0; j < 517; j++)
  {
    for (i = lst_games[j], follow = i; follow != 0;)
    {
      i = follow;
      follow = i->next;
      free(i->name);
      free(i->team1);
      free(i->team2);
      free(i);
    }

  }

  free(lst_games);
}

