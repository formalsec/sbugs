/*File generated by PreProcessor.py*/


#include "MainFunctions.h"


void NewGame(Node *hash_game, Team *hash_team, List l, int NL, int *m_game, int *m_team, int *n_games)
{
  char name[1024];
  char team_1[1024];
  char team_2[1024];
  int score_1;
  int score_2;
  Game g;
  Team t1;
  Team t2;
  Team winner;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int team_1_index = 0; team_1_index < 10; team_1_index++)
  {
    team_1[team_1_index] = new_sym_var(sizeof(char) * 8);
  }

  team_1[10 - 1] = '\0';
  for (int team_2_index = 0; team_2_index < 10; team_2_index++)
  {
    team_2[team_2_index] = new_sym_var(sizeof(char) * 8);
  }

  team_2[10 - 1] = '\0';
  score_1 = new_sym_var(sizeof(int) * 8);
  score_2 = new_sym_var(sizeof(int) * 8);
  getchar();
  if (GameSearch(name, m_game, hash_game) != (-1))
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if (((t1 = TeamSearch(team_1, m_team, hash_team)) == 0) || ((t2 = TeamSearch(team_2, m_team, hash_team)) == 0))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      g = InitGame();
      SetName(name, g);
      SetScore(score_1, score_2, g);
      SetTeams(t1, t2, g);
      InsertEnd(l, g);
      HashGamesInsert(hash_game, End(l), m_game);
      if ((winner = Winner(g)) != 0)
      {
        IncWins(winner);
      }
      else
      {
        
      }

      (*n_games)++;
    }

  }

}

void NewTeam(Team *hash_team, int *m, int NL, int *n_teams)
{
  char name[1024];
  Team t;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if (TeamSearch(name, m, hash_team) != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    t = InitTeam();
    SetTeamName(t, name);
    HashTeamsInsert(hash_team, t, m);
    (*n_teams)++;
  }

}

void ListGames(int NL, List l)
{
  Node head = Head(l);
  getchar();
  for (; head != 0; head = Next(head))
    WriteGame(NodeGame(head), NL);

}

void SearchGame(Node *hash_game, int *m, int NL)
{
  char name[1024];
  int i;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if ((i = GameSearch(name, m, hash_game)) != (-1))
  {
    WriteGame(NodeGame(hash_game[i]), NL);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void SearchTeam(Team *hash_team, int *m, int NL)
{
  char name[1024];
  Team t;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if ((t = TeamSearch(name, m, hash_team)) != 0)
  {
    WriteTeam(t, NL);
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

void DeleteGame(Node *hash_game, List l, int *m, int NL, int *n_games)
{
  char name[1024];
  Node node;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  if ((node = HashRemoveGame(name, m, hash_game)) != 0)
  {
    RemoveGame(node, l);
    (*n_games)--;
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void ChangeScore(Node *hash_game, int *m, int NL)
{
  char name[1024];
  Node node;
  int i;
  int score_1;
  int score_2;
  Team old_winner;
  Team new_winner;
  getchar();
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  score_1 = new_sym_var(sizeof(int) * 8);
  score_2 = new_sym_var(sizeof(int) * 8);
  getchar();
  if ((i = GameSearch(name, m, hash_game)) == (-1))
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  node = hash_game[i];
  old_winner = Winner(NodeGame(node));
  SetScore(score_1, score_2, NodeGame(node));
  new_winner = Winner(NodeGame(node));
  if (old_winner == new_winner)
  {
    return;
  }
  else
  {
    if (old_winner == 0)
    {
      IncWins(new_winner);
    }
    else
    {
      if (new_winner == 0)
      {
        DecWins(old_winner);
      }
      else
      {
        DecWins(old_winner);
        IncWins(new_winner);
      }

    }

  }

}

void FindBest(Team *hash_team, int *n_teams, int NL)
{
  int i = 0;
  int best = 0;
  int count = 0;
  int n = 0;
  char **team_names = 0;
  getchar();
  if (!(*n_teams))
  {
    return;
  }
  else
  {
    
  }

  for (; n < (*n_teams); i++)
  {
    if (hash_team[i] != 0)
    {
      n++;
      if (Wins(hash_team[i]) > best)
      {
        best = Wins(hash_team[i]);
        count = 1;
      }
      else
      {
        if (Wins(hash_team[i]) == best)
        {
          count++;
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

  team_names = CreatesTeamNames(team_names, hash_team, count, best);
  Quick_Sort(team_names, 0, count - 1);
  printf("%d Melhores %d\n", NL, best);
  for (i = 0; i < count; i++)
  {
    printf("%d * %s\n", NL, team_names[i]);
    free(team_names[i]);
  }

  free(team_names);
}
