/*File generated by PreProcessor.py*/


#include "games.h"


int read_score()
{
  int score;
  score = new_sym_var(sizeof(int) * 8);
  return score;
}

game create_game(node_teams **teams_table)
{
  game new_game;
  node_teams node_aux_t1;
  node_teams node_aux_t2;
  node_teams *p_node_aux_t1;
  node_teams *p_node_aux_t2;
  char name[1024] = {0};
  char name_t1[1024] = {0};
  char name_t2[1024] = {0};
  int score1;
  int score2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int name_t1_index = 0; name_t1_index < 10; name_t1_index++)
  {
    name_t1[name_t1_index] = new_sym_var(sizeof(char) * 8);
  }

  name_t1[10 - 1] = '\0';
  for (int name_t2_index = 0; name_t2_index < 10; name_t2_index++)
  {
    name_t2[name_t2_index] = new_sym_var(sizeof(char) * 8);
  }

  name_t2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  new_game.name = malloc((strlen(name) + 1) * (sizeof(char)));
  strcpy(new_game.name, name);
  node_aux_t1.t.name = malloc((strlen(name_t1) + 1) * (sizeof(char)));
  strcpy(node_aux_t1.t.name, name_t1);
  p_node_aux_t1 = &node_aux_t1;
  node_aux_t2.t.name = malloc((strlen(name_t2) + 1) * (sizeof(char)));
  strcpy(node_aux_t2.t.name, name_t2);
  p_node_aux_t2 = &node_aux_t2;
  new_game.score1 = score1;
  new_game.score2 = score2;
  new_game.t_1 = in_table_teams(teams_table, p_node_aux_t1);
  new_game.t_2 = in_table_teams(teams_table, p_node_aux_t2);
  free(node_aux_t1.t.name);
  free(node_aux_t2.t.name);
  return new_game;
}

void destroy_game(game g)
{
  free(g.name);
}

node_games create_node_game(game new_game)
{
  node_games node_new_game;
  node_new_game.g = new_game;
  node_new_game.next = 0;
  node_new_game.next_in_hash_table = 0;
  node_new_game.prev = 0;
  node_new_game.prev_in_hash_table = 0;
  return node_new_game;
}

node_teams *get_winner(node_games *game)
{
  if (game->g.score1 > game->g.score2)
  {
    return game->g.t_1;
  }
  else
  {
    
  }

  if (game->g.score1 < game->g.score2)
  {
    return game->g.t_2;
  }
  else
  {
    
  }

  return 0;
}

node_games *push_game(node_games *head, game g)
{
  node_games *new = malloc(sizeof(node_games));
  new->g = g;
  new->next = 0;
  if (head == 0)
  {
    new->prev = 0;
    head = new;
    return head;
  }
  else
  {
    
  }

  head->next = new;
  new->prev = head;
  return new;
}

void free_game(node_games *game)
{
  free(game->g.name);
  free(game);
}

node_games *destroy_games(node_games *head)
{
  node_games *tmp;
  while (head != 0)
  {
    tmp = head->prev;
    free_game(head);
    head = tmp;
  }

  return 0;
}

node_games *find_game(node_games **games_table)
{
  game g;
  node_games node_g;
  node_games *p_node_g;
  node_games *head_g;
  char name[1024];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  g.name = malloc((strlen(name) + 1) * (sizeof(char)));
  strcpy(g.name, name);
  node_g = create_node_game(g);
  p_node_g = &node_g;
  head_g = in_table_games(games_table, p_node_g);
  destroy_game(g);
  return head_g;
}

void apply_score(node_games *game, int score1, int score2)
{
  game->g.score1 = score1;
  game->g.score2 = score2;
}

node_teams *get_t1(node_games *game)
{
  return game->g.t_1;
}

node_teams *get_t2(node_games *game)
{
  return game->g.t_2;
}

char *get_game_name(node_games *game)
{
  return game->g.name;
}

char *get_name_t1(node_games *game)
{
  return game->g.t_1->t.name;
}

char *get_name_t2(node_games *game)
{
  return game->g.t_2->t.name;
}

int get_score1(node_games *game)
{
  return game->g.score1;
}

int get_score2(node_games *game)
{
  return game->g.score2;
}

node_games *get_next_list(node_games *node)
{
  return node->next;
}

node_games *get_prev_list(node_games *node)
{
  return node->prev;
}

node_games *get_next_table(node_games *node)
{
  return node->next_in_hash_table;
}

node_games *get_prev_table(node_games *node)
{
  return node->prev_in_hash_table;
}

void print_games_in_order(node_games *head, int line_counter)
{
  node_games *tmp;
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  for (tmp = head; tmp->prev != 0; tmp = tmp->prev)
    ;

  while (tmp != 0)
  {
    printf("%d %s %s %s %d %d\n", line_counter, get_game_name(tmp), get_name_t1(tmp), get_name_t2(tmp), get_score1(tmp), get_score2(tmp));
    tmp = tmp->next;
  }

}

void delete_swaps(node_games **head_games, node_games **games_table, node_games *game_found)
{
  node_games *game_next_l;
  node_games *game_prev_l;
  node_games *game_next_t;
  node_games *game_prev_t;
  int index;
  index = hash_game(game_found);
  game_next_l = get_next_list(game_found);
  game_prev_l = get_prev_list(game_found);
  game_next_t = get_next_table(game_found);
  game_prev_t = get_prev_table(game_found);
  if ((game_next_l == 0) && (game_prev_l == 0))
  {
    *head_games = 0;
  }
  else
  {
    if ((game_next_l == 0) && (game_prev_l != 0))
    {
      game_prev_l->next = 0;
      *head_games = game_prev_l;
    }
    else
    {
      game_next_l->prev = game_prev_l;
      if (game_prev_l != 0)
      {
        game_prev_l->next = game_next_l;
      }
      else
      {
        
      }

    }

  }

  if ((game_next_t == 0) && (game_prev_t == 0))
  {
    games_table[index] = 0;
  }
  else
  {
    if ((game_next_t == 0) && (game_prev_t != 0))
    {
      game_prev_t->next_in_hash_table = 0;
      games_table[index] = game_prev_t;
    }
    else
    {
      game_next_t->prev_in_hash_table = game_prev_t;
      if (game_prev_t != 0)
      {
        game_prev_t->next_in_hash_table = game_next_t;
      }
      else
      {
        
      }

    }

  }

}

