#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams_struct.h"
#include "games_struct.h"


l_game *init_game_list()
{
  l_game *game_list;
  game_list = malloc(sizeof(l_game));
  game_list->head = 0;
  game_list->last = 0;
  return game_list;
}

void destroy_game_list(l_game *game_list)
{
  while (game_list->head)
  {
    delete_game(game_list->head, game_list);
  }

  free(game_list);
}

game_link **init_hash_games()
{
  int i;
  game_link **hash_games;
  hash_games = malloc((sizeof(game_link)) * 10000);
  for (i = 0; i < 10000; i++)
    hash_games[i] = 0;

  return hash_games;
}

game_link *insert_beguin_hash_game(game_link *head, game_node *game)
{
  game_link *new_head = malloc(sizeof(link_t));
  new_head->link = game;
  new_head->next = head;
  return new_head;
}

void insert_hash_game(game_link **hash_games, game_node *game)
{
  int key = hashU(game->game_name, 10000);
  game_link *new_head = insert_beguin_hash_game(hash_games[key], game);
  hash_games[key] = new_head;
}

game_node *search_game(game_link **hash_games, char *name)
{
  int key = hashU(name, 10000);
  game_node *game = 0;
  game_link *head = hash_games[key];
  while (hash_games[key])
  {
    if (!strcmp(hash_games[key]->link->game_name, name))
    {
      game = hash_games[key]->link;
      break;
    }
    else
    {
      hash_games[key] = hash_games[key]->next;
    }

  }

  hash_games[key] = head;
  return game;
}

void delete_game_hash(game_link **hash_games, l_game *game_list, char *name)
{
  int key = hashU(name, 10000);
  game_link *previous = 0;
  game_link *head = hash_games[key];
  while (hash_games[key])
  {
    if (!strcmp(hash_games[key]->link->game_name, name))
    {
      if (previous)
      {
        previous->next = hash_games[key]->next;
      }
      else
      {
        head = hash_games[key]->next;
      }

      delete_game(hash_games[key]->link, game_list);
      free(hash_games[key]);
      hash_games[key] = head;
      break;
    }
    else
    {
      previous = hash_games[key];
      hash_games[key] = hash_games[key]->next;
    }

  }

}

void destroy_hash_game(game_link **hash_games)
{
  int i;
  game_link *next;
  for (i = 0; i < 10000; i++)
  {
    while (hash_games[i])
    {
      next = hash_games[i]->next;
      free(hash_games[i]);
      hash_games[i] = next;
    }

  }

  free(hash_games);
}

game_node *insert_game(l_game *game_list, char *name, t_node *first_team, t_node *second_team, int first_score, int second_score)
{
  game_node *new_game = malloc(sizeof(game_node));
  new_game->game_name = malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(new_game->game_name, name);
  new_game->team_one = first_team;
  new_game->team_two = second_team;
  new_game->score_one = first_score;
  new_game->score_two = second_score;
  record_update(first_team, second_team, first_score, second_score);
  new_game->previous = game_list->last;
  if (game_list->last)
  {
    game_list->last->next = new_game;
  }
  else
  {
    game_list->head = new_game;
  }

  game_list->last = new_game;
  new_game->next = 0;
  return new_game;
}

void record_update(t_node *team_one, t_node *team_two, int score_one, int score_two)
{
  if (score_one > score_two)
  {
    team_one->wins += 1;
  }
  else
  {
    
  }

  if (score_one < score_two)
  {
    team_two->wins += 1;
  }
  else
  {
    
  }

}

void remove_win(t_node *team_one, t_node *team_two, int score_one, int score_two)
{
  if (score_one > score_two)
  {
    team_one->wins -= 1;
  }
  else
  {
    
  }

  if (score_one < score_two)
  {
    team_two->wins -= 1;
  }
  else
  {
    
  }

}

void free_game(game_node *game)
{
  free(game->game_name);
  free(game);
}

void delete_game(game_node *game, l_game *game_list)
{
  if (game->previous)
  {
    game->previous->next = game->next;
  }
  else
  {
    game_list->head = game->next;
  }

  if (game->next)
  {
    game->next->previous = game->previous;
  }
  else
  {
    game_list->last = game->previous;
  }

  free_game(game);
}

