/*File generated by PreProcessor.py*/


#include "add.h"


void addWin(list *tms, char *name)
{
  node *ptr = tms->head;
  while (ptr != 0)
  {
    ptr = ptr->next;
  }

  while (ptr)
  {
    if (strcmp(ptr->name, name) == 0)
    {
      ptr->won++;
      break;
    }
    else
    {
      
    }

    ptr = ptr->next;
  }

}

void push(int idx, node *n_node, int flag)
{
  hashNode *info = (hashNode *) malloc(sizeof(hashNode));
  info->point = n_node;
  if (flag == 0)
  {
    info->next = games[idx].head;
    games[idx].head = info;
  }
  else
  {
    info->next = teams[idx].head;
    teams[idx].head = info;
  }

}

void addGame(list *ls, list *tms)
{
  node *n_game;
  hashNode *testName;
  hashNode *testTeam1;
  hashNode *testTeam2;
  int idx;
  int score1;
  int score2;
  char name[1024];
  char team1[1024];
  char team2[1024];
  n_game = (node *) malloc(sizeof(node));
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
  testName = getNodeGames(name);
  testTeam1 = getNodeTeams(team1);
  testTeam2 = getNodeTeams(team2);
  if (testName != 0)
  {
    printf("%d Jogo existente.\n", counter);
    free(n_game);
    return;
  }
  else
  {
    if ((testTeam1 == 0) || (testTeam2 == 0))
    {
      printf("%d Equipa inexistente.\n", counter);
      free(n_game);
      return;
    }
    else
    {
      n_game->name = (char *) malloc((sizeof(char)) * (strlen(name) + 1));
      n_game->team1 = (char *) malloc((sizeof(char)) * (strlen(team1) + 1));
      n_game->team2 = (char *) malloc((sizeof(char)) * (strlen(team2) + 1));
      strcpy(n_game->name, name);
      strcpy(n_game->team1, team1);
      strcpy(n_game->team2, team2);
      n_game->score1 = score1;
      n_game->score2 = score2;
      n_game->next = (n_game->previous = 0);
      if (ls->head == 0)
      {
        ls->head = n_game;
        idx = getHashKey(n_game->name);
        push(idx, n_game, 0);
      }
      else
      {
        n_game->previous = ls->end;
        ls->end->next = n_game;
        idx = getHashKey(n_game->name);
        push(idx, n_game, 0);
      }

      if (score1 > score2)
      {
        addWin(tms, team1);
        testTeam1->point->won++;
      }
      else
      {
        if (score1 < score2)
        {
          addWin(tms, team2);
          testTeam2->point->won++;
        }
        else
        {
          
        }

      }

      ls->end = n_game;
    }

  }

}

void addTeam(list *ls)
{
  node *n_team;
  hashNode *testTeam;
  int idx;
  char name[1024];
  n_team = (node *) malloc(sizeof(node));
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  n_team->name = (char *) malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(n_team->name, name);
  n_team->won = 0;
  n_team->next = (n_team->previous = 0);
  testTeam = getNodeTeams(n_team->name);
  if (testTeam != 0)
  {
    printf("%d Equipa existente.\n", counter);
    free(n_team->name);
    free(n_team);
    return;
  }
  else
  {
    if (ls->head == 0)
    {
      ls->head = n_team;
      idx = getHashKey(n_team->name);
      push(idx, n_team, 1);
    }
    else
    {
      n_team->previous = ls->end;
      ls->end->next = n_team;
      idx = getHashKey(n_team->name);
      push(idx, n_team, 1);
    }

    ls->end = n_team;
  }

}

