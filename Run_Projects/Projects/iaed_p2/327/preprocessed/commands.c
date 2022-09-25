/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"


void cmd_a(int line, game_list *game_lst, game_ht *games, team_ht *teams)
{
  char name[1024];
  char t1_name[1024];
  char t2_name[1024];
  int score1;
  int score2;
  team *team1;
  team *team2;
  game *new_game;
  game_node *node;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int t1_name_index = 0; t1_name_index < 10; t1_name_index++)
  {
    t1_name[t1_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t1_name[10 - 1] = '\0';
  for (int t2_name_index = 0; t2_name_index < 10; t2_name_index++)
  {
    t2_name[t2_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t2_name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  team1 = team_ht_search(teams, t1_name);
  team2 = team_ht_search(teams, t2_name);
  if (game_ht_search(games, name))
  {
    printf("%d Jogo existente.\n", line);
    return;
  }
  else
  {
    if ((!team1) || (!team2))
    {
      printf("%d Equipa inexistente.\n", line);
      return;
    }
    else
    {
      
    }

  }

  new_game = mk_game(name, team1, team2, score1, score2);
  node = add_game_list(game_lst, new_game);
  game_ht_insert(games, node, true);
  return;
}

void cmd_A(int line, team_ht *teams)
{
  char name[1024];
  team *new_team;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if (team_ht_search(teams, name))
  {
    printf("%d Equipa existente.\n", line);
    return;
  }
  else
  {
    
  }

  new_team = mk_team(name);
  team_ht_insert(teams, new_team);
  return;
}

void cmd_l(int line, game_list *game_lst)
{
  print_game_list(line, game_lst);
  return;
}

void cmd_p(int line, game_ht *games)
{
  char name[1024];
  game_node *node;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  node = game_ht_search(games, name);
  if (node)
  {
    print_game(line, node->gm);
  }
  else
  {
    printf("%d Jogo inexistente.\n", line);
  }

  return;
}

void cmd_P(int line, team_ht *teams)
{
  char name[1024];
  team *t;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  t = team_ht_search(teams, name);
  if (t)
  {
    printf("%d %s %d\n", line, name, t->wins);
  }
  else
  {
    printf("%d Equipa inexistente.\n", line);
  }

  return;
}

void cmd_r(int line, game_list *game_lst, game_ht *games)
{
  char name[1024];
  game_node *node;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  node = game_ht_delete(games, name);
  if (!node)
  {
    printf("%d Jogo inexistente.\n", line);
    return;
  }
  else
  {
    
  }

  rm_game_list(game_lst, node);
  return;
}

void cmd_s(int line, game_ht *games)
{
  char name[1024];
  int score1;
  int score2;
  game_node *node;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  node = game_ht_search(games, name);
  if (node)
  {
    set_game_score(node->gm, score1, score2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", line);
  }

  return;
}

void cmd_g(int line, team_ht *teams)
{
  team_ht_print_most_wins(line, teams);
  return;
}

