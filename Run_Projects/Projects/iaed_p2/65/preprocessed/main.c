/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"
#include "hashtables.h"


void add_game(int, nodeGame *[], nodeTeam *[], indexNode **, int *, int *);
void list_all(int, nodeGame *[], indexNode *, int, int);
void copy_addr_games(Game **, nodeGame *[], indexNode *);
void copy_addr_g(Game **, nodeGame *);
void search_game(int, nodeGame *[]);
void del_game(int, nodeGame *[], nodeTeam *[], int *);
void edit_score(int, nodeGame *[], nodeTeam *[]);
void add_team(int, nodeTeam *[], indexNode **, int *);
void search_team(int, nodeTeam *[]);
void list_winners(int, nodeTeam *[], indexNode *, int);
int copy_addr_teams(Team *[], nodeTeam *[], indexNode *);
void copy_addr_t(int *, Team *[], nodeTeam *, int *);
int not_in_list_t(int, char *, Team **);
int compare(const void *, const void *);
int compare_indexNodes(indexNode *, indexNode *);
void change_win(int, int, nodeGame *, nodeTeam *[], int);
int main(void)
{
  int command;
  int i;
  int total_g = 0;
  int current_g = 0;
  int t = 0;
  int NL = 1;
  nodeGame *games_ht[7919];
  nodeTeam *teams_ht[7919];
  indexNode *index_games;
  indexNode *index_teams;
  for (i = 0; i < 7919; i++)
  {
    games_ht[i] = 0;
    teams_ht[i] = 0;
  }

  index_games = 0;
  index_teams = 0;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        add_game(NL, games_ht, teams_ht, &index_games, &total_g, &current_g);
        NL++;
        break;

      case 'l':
        list_all(NL, games_ht, index_games, current_g, total_g);
        NL++;
        break;

      case 'p':
        search_game(NL, games_ht);
        NL++;
        break;

      case 'r':
        del_game(NL, games_ht, teams_ht, &current_g);
        NL++;
        break;

      case 's':
        edit_score(NL, games_ht, teams_ht);
        NL++;
        break;

      case 'A':
        add_team(NL, teams_ht, &index_teams, &t);
        NL++;
        break;

      case 'P':
        search_team(NL, teams_ht);
        NL++;
        break;

      case 'g':
        list_winners(NL, teams_ht, index_teams, t);
        NL++;
        break;

    }

  }

  destroy_games_ht(games_ht, index_games);
  destroy_teams_ht(teams_ht, index_teams);
  _destroy_list_(index_games);
  _destroy_list_(index_teams);
  return 0;
}

void add_game(int NL, nodeGame *games_ht[], nodeTeam *teams_ht[], indexNode **index_games, int *total_g, int *current_g)
{
  char game_name[1024];
  char team1_name[1024];
  char team2_name[1024];
  int score1;
  int score2;
  nodeTeam *team1_addr;
  nodeTeam *team2_addr;
  nodeGame *game_addr;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  for (int team1_name_index = 0; team1_name_index < 10; team1_name_index++)
  {
    team1_name[team1_name_index] = new_sym_var(sizeof(char) * 8);
  }

  team1_name[10 - 1] = '\0';
  for (int team2_name_index = 0; team2_name_index < 10; team2_name_index++)
  {
    team2_name[team2_name_index] = new_sym_var(sizeof(char) * 8);
  }

  team2_name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  team1_addr = search_team_ht(teams_ht, team1_name, 7919);
  team2_addr = search_team_ht(teams_ht, team2_name, 7919);
  game_addr = search_game_ht(games_ht, game_name, 7919);
  if (game_addr != 0)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if ((team1_addr == 0) || (team2_addr == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      add_game_ht(games_ht, index_games, game_name, *total_g, score1, score2, team1_name, team2_name, 7919);
      game_addr = search_game_ht(games_ht, game_name, 7919);
      change_win(score1, score2, game_addr, teams_ht, 1);
      (*current_g)++;
      (*total_g)++;
    }

  }

}

void list_all(int NL, nodeGame *games_ht[], indexNode *index_games, int current_g, int total_g)
{
  Game **games_played;
  int i;
  int j;
  if (current_g == 0)
  {
    return;
  }
  else
  {
    
  }

  games_played = (Game **) malloc((sizeof(Game *)) * total_g);
  for (j = 0; j < total_g; j++)
  {
    games_played[j] = 0;
  }

  copy_addr_games(games_played, games_ht, index_games);
  for (i = 0; i < total_g; i++)
  {
    print_game(NL, games_played[i]);
  }

  free(games_played);
}

void copy_addr_games(Game **games_played, nodeGame *games_ht[], indexNode *index_games)
{
  while (index_games != 0)
  {
    copy_addr_g(games_played, games_ht[index_games->s]);
    index_games = index_games->next;
  }

}

void copy_addr_g(Game **games_played, nodeGame *games_list)
{
  while (games_list != 0)
  {
    games_played[games_list->game->id] = games_list->game;
    games_list = games_list->next;
  }

}

void search_game(int NL, nodeGame *games_ht[])
{
  nodeGame *addr;
  char game_name[1024];
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  addr = search_game_ht(games_ht, game_name, 7919);
  if (addr == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    print_game(NL, addr->game);
  }

}

void del_game(int NL, nodeGame *games_ht[], nodeTeam *teams_ht[], int *current_g)
{
  nodeGame *game_addr;
  char game_name[1024];
  int score1;
  int score2;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  game_addr = search_game_ht(games_ht, game_name, 7919);
  if (game_addr == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    score1 = game_addr->game->score1;
    score2 = game_addr->game->score2;
    change_win(score1, score2, game_addr, teams_ht, -1);
    del_game_ht(games_ht, game_name, 7919);
    (*current_g)--;
  }

}

void edit_score(int NL, nodeGame *games_ht[], nodeTeam *teams_ht[])
{
  nodeGame *game_addr;
  char game_name[1024];
  int score1;
  int score2;
  int new_score1;
  int new_score2;
  for (int game_name_index = 0; game_name_index < 10; game_name_index++)
  {
    game_name[game_name_index] = new_sym_var(sizeof(char) * 8);
  }

  game_name[10 - 1] = '\0';
  new_score1 = new_sym_var(sizeof(int) * 8);
  new_score2 = new_sym_var(sizeof(int) * 8);
  game_addr = search_game_ht(games_ht, game_name, 7919);
  if (game_addr == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    score1 = game_addr->game->score1;
    score2 = game_addr->game->score2;
    change_win(score1, score2, game_addr, teams_ht, -1);
    change_win(new_score1, new_score2, game_addr, teams_ht, 1);
    game_addr->game->score1 = new_score1;
    game_addr->game->score2 = new_score2;
  }

}

void add_team(int NL, nodeTeam *teams_ht[], indexNode **index_teams, int *t)
{
  nodeTeam *team_addr;
  char team_name[1024];
  for (int team_name_index = 0; team_name_index < 10; team_name_index++)
  {
    team_name[team_name_index] = new_sym_var(sizeof(char) * 8);
  }

  team_name[10 - 1] = '\0';
  team_addr = search_team_ht(teams_ht, team_name, 7919);
  if (team_addr != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    add_team_ht(teams_ht, index_teams, team_name, 7919);
    (*t)++;
  }

}

void search_team(int NL, nodeTeam *teams_ht[])
{
  nodeTeam *team_addr;
  char team_name[1024];
  for (int team_name_index = 0; team_name_index < 10; team_name_index++)
  {
    team_name[team_name_index] = new_sym_var(sizeof(char) * 8);
  }

  team_name[10 - 1] = '\0';
  team_addr = search_team_ht(teams_ht, team_name, 7919);
  if (team_addr == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    print_team(NL, team_addr->team);
  }

}

void list_winners(int NL, nodeTeam *teams_ht[], indexNode *index_teams, int t)
{
  Team **teams;
  int i;
  int j;
  int length;
  if (t == 0)
  {
    return;
  }
  else
  {
    
  }

  teams = (Team **) malloc((sizeof(Team *)) * t);
  for (i = 0; i < t; i++)
  {
    teams[i] = 0;
  }

  length = copy_addr_teams(teams, teams_ht, index_teams);
  qsort(teams, length, sizeof(Team *), compare);
  printf("%d Melhores %d\n", NL, teams[0]->wins);
  for (j = 0; j < length; j++)
  {
    printf("%d * %s\n", NL, teams[j]->name);
  }

  free(teams);
}

int copy_addr_teams(Team **teams, nodeTeam *teams_ht[], indexNode *index_teams)
{
  int acc = 0;
  int most_wins = 0;
  while (index_teams != 0)
  {
    copy_addr_t(&acc, teams, teams_ht[index_teams->s], &most_wins);
    index_teams = index_teams->next;
  }

  return acc;
}

void copy_addr_t(int *acc, Team **teams, nodeTeam *teams_list, int *wins)
{
  while (teams_list != 0)
  {
    if ((teams_list->team->wins == (*wins)) && not_in_list_t(*acc, teams_list->team->name, teams))
    {
      teams[*acc] = teams_list->team;
      (*acc)++;
    }
    else
    {
      if (teams_list->team->wins > (*wins))
      {
        *acc = 0;
        teams[*acc] = teams_list->team;
        *wins = teams_list->team->wins;
        (*acc)++;
      }
      else
      {
        
      }

    }

    teams_list = teams_list->next;
  }

}

int not_in_list_t(int boundary, char *team_name, Team **teams)
{
  int i;
  for (i = 0; i < boundary; i++)
  {
    if (strcmp(team_name, teams[i]->name) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

int compare(const void *team1, const void *team2)
{
  const Team *t1 = *((const Team **) team1);
  const Team *t2 = *((const Team **) team2);
  return strcmp(t1->name, t2->name);
}

void change_win(int score1, int score2, nodeGame *game_addr, nodeTeam *teams_ht[], int value)
{
  nodeTeam *winner_addr;
  if (score1 > score2)
  {
    winner_addr = search_team_ht(teams_ht, game_addr->game->team1, 7919);
    change_wins_directly(winner_addr, value);
  }
  else
  {
    if (score2 > score1)
    {
      winner_addr = search_team_ht(teams_ht, game_addr->game->team2, 7919);
      change_wins_directly(winner_addr, value);
    }
    else
    {
      
    }

  }

}

