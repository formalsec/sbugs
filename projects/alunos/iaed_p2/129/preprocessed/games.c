#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "games.h"


game_table *init_games()
{
  int i;
  game_table *games = malloc(sizeof(game_table));
  for (i = 0; i < 1009; i++)
  {
    games->table[i] = 0;
  }

  games->first_game = 0;
  games->latest_game = 0;
  return games;
}

int hash_game(char *name)
{
  int key;
  int i;
  for (key = 0, i = 0; name[i] != '\0'; i++)
  {
    key += (1023 - 1) * name[i];
  }

  key = key % 1009;
  return key;
}

void push_game(game_table *games, game *game)
{
  int pos;
  game_node *taken_node;
  game_node *new_node = malloc(sizeof(game_node));
  new_node->game = game;
  new_node->next_game = 0;
  new_node->next_node = 0;
  pos = hash_game(game->name);
  if (games->table[pos] == 0)
  {
    games->table[pos] = new_node;
    new_node->previous_node = 0;
  }
  else
  {
    taken_node = games->table[pos];
    while (taken_node->next_node != 0)
    {
      taken_node = taken_node->next_node;
    }

    taken_node->next_node = new_node;
    new_node->previous_node = taken_node;
  }

  if (games->latest_game == 0)
  {
    games->first_game = new_node;
    games->latest_game = new_node;
    new_node->previous_game = 0;
  }
  else
  {
    new_node->previous_game = games->latest_game;
    games->latest_game->next_game = new_node;
    games->latest_game = new_node;
  }

}

int same_game(game *game_1, game *game_2)
{
  if (!strcmp(game_1->name, game_2->name))
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

game_node *get_node(game_table *games, game *game)
{
  int key;
  game_node *node;
  key = hash_game(game->name);
  node = games->table[key];
  while (!same_game(node->game, game))
  {
    node = node->next_node;
  }

  return node;
}

void delete_game(game_table *games, game *game)
{
  game_node *node;
  int key;
  key = hash_game(game->name);
  node = games->table[key];
  if (same_game(node->game, game))
  {
    games->table[key] = node->next_node;
  }
  else
  {
    while (!same_game(node->game, game))
    {
      node = node->next_node;
    }

    node->previous_node->next_node = node->next_node;
  }

  if (node->next_node != 0)
  {
    node->next_node->previous_node = node->previous_node;
  }
  else
  {
    
  }

  if (same_game(games->first_game->game, game))
  {
    games->first_game = node->next_game;
  }
  else
  {
    node->previous_game->next_game = node->next_game;
  }

  if (same_game(games->latest_game->game, game))
  {
    games->latest_game = node->previous_game;
  }
  else
  {
    node->next_game->previous_game = node->previous_game;
  }

  free_game(node->game);
  free(node);
}

void new_game(game_table *games, char *name, team *team_1, team *team_2, int score_1, int score_2)
{
  game *new_game = malloc(sizeof(game));
  new_game->name = name;
  new_game->team_1 = team_1;
  new_game->team_2 = team_2;
  new_game->score_team_1 = score_1;
  new_game->score_team_2 = score_2;
  push_game(games, new_game);
}

game *get_game(game_table *games, char *name)
{
  int key;
  game_node *node;
  key = hash_game(name);
  node = games->table[key];
  while (node != 0)
  {
    if (!strcmp(node->game->name, name))
    {
      return node->game;
    }
    else
    {
      
    }

    node = node->next_node;
  }

  return 0;
}

void update_score(game *game, int score_1, int score_2)
{
  game->score_team_1 = score_1;
  game->score_team_2 = score_2;
}

game *first_game(game_table *games)
{
  if (games->first_game != 0)
  {
    return games->first_game->game;
  }
  else
  {
    return 0;
  }

}

game *next_game(game_table *games, game *game)
{
  game_node *next_game_node;
  next_game_node = get_node(games, game)->next_game;
  if (next_game_node != 0)
  {
    return next_game_node->game;
  }
  else
  {
    return 0;
  }

}

team *game_winner(game *game)
{
  if (game->score_team_1 > game->score_team_2)
  {
    return game->team_1;
  }
  else
  {
    if (game->score_team_1 < game->score_team_2)
    {
      return game->team_2;
    }
    else
    {
      return 0;
    }

  }

}

void print_game(game *game)
{
  printf("%s %s %s %d %d\n", game->name, get_team_name(game->team_1), get_team_name(game->team_2), game->score_team_1, game->score_team_2);
}

void free_game(game *game)
{
  free(game->name);
  free(game);
}

void free_games(game_table *games)
{
  game_node *node;
  game_node *tmp;
  node = games->first_game;
  while (node != 0)
  {
    free_game(node->game);
    tmp = node->next_game;
    free(node);
    node = tmp;
  }

  free(games);
}

