/*File generated by PreProcessor.py*/


#include "auxiliary_funcs.h"


void addGame(Ht_games *htg, Ht_teams htt, nodeGame *head_games, char name[1024], char team1[1024], char team2[1024], int score1, int score2, int inL);
void findGame(Ht_games ht, char *game_name, int inL);
nodeGame eraseGame(Ht_games ht, Ht_teams ht_teams, nodeGame head, char *game_name, int inL);
void listGames(nodeGame head, int inL);
void addTeam(Ht_teams *ht, nodeTeam *head, char *team_name, int inL);
void findTeam(Ht_teams ht, char *team_name, int inL);
void updateScore(Ht_games ht, Ht_teams ht_teams, char *game_name, int score1, int score2, int inL);
void bestTeams(nodeTeam head, int inL);
int main()
{
  int NL = 1;
  int not_finished = 1;
  int score1;
  int score2;
  char ch;
  char name[1024] = {0};
  char team1[1024] = {0};
  char team2[1024] = {0};
  nodeGame head_games = {0};
  nodeTeam head_teams = {0};
  Ht_games ht_games = HTGinit(1997);
  Ht_teams ht_teams = HTTinit(997);
  while (not_finished)
  {
    switch (ch = getchar())
    {
      case 'a':
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
        addGame(&ht_games, ht_teams, &head_games, name, team1, team2, score1, score2, NL);
        break;

      case 'p':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        findGame(ht_games, name, NL);
        break;

      case 'r':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        head_games = eraseGame(ht_games, ht_teams, head_games, name, NL);
        break;

      case 'l':
        listGames(head_games, NL);
        break;

      case 'A':
        for (int team1_index = 0; team1_index < 10; team1_index++)
      {
        team1[team1_index] = new_sym_var(sizeof(char) * 8);
      }

        team1[10 - 1] = '\0';
        addTeam(&ht_teams, &head_teams, team1, NL);
        break;

      case 'P':
        for (int team1_index = 0; team1_index < 10; team1_index++)
      {
        team1[team1_index] = new_sym_var(sizeof(char) * 8);
      }

        team1[10 - 1] = '\0';
        findTeam(ht_teams, team1, NL);
        break;

      case 's':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        updateScore(ht_games, ht_teams, name, score1, score2, NL);
        break;

      case 'g':
        bestTeams(head_teams, NL);
        break;

      default:
        not_finished = 0;

    }

    NL++;
    getchar();
  }

  freeMemory(ht_games, ht_teams, head_games, head_teams);
  return 0;
}

void addGame(Ht_games *htg, Ht_teams htt, nodeGame *head_games, char name[1024], char team1[1024], char team2[1024], int score1, int score2, int inL)
{
  Team t1;
  Team t2;
  t1 = HTsearchTeam(htt, team1);
  t2 = HTsearchTeam(htt, team2);
  if (HTsearchGame(*htg, name) != 0)
  {
    {
      printf("%d Jogo existente.\n", inL);
      return;
    }
  }
  else
  {
    if ((t1 == 0) || (t2 == 0))
    {
      {
        printf("%d Equipa inexistente.\n", inL);
        return;
      }
    }
    else
    {
      {
        char *pname = allocateWrite(name);
        char *pteam1 = allocateWrite(team1);
        char *pteam2 = allocateWrite(team2);
        Game new_game = newGame(pname, pteam1, pteam2, score1, score2);
        *htg = HTinsertGame(*htg, new_game);
        *head_games = pushGame(*head_games, new_game);
        if (score1 > score2)
        {
          t1->won++;
        }
        else
        {
          if (score1 < score2)
          {
            t2->won++;
          }
          else
          {
            
          }

        }

        pname = (pteam1 = (pteam2 = 0));
      }
    }

  }

  t1 = (t2 = 0);
}

void findGame(Ht_games ht, char *game_name, int inL)
{
  Game g = HTsearchGame(ht, game_name);
  if (g == 0)
  {
    printf("%d Jogo inexistente.\n", inL);
  }
  else
  {
    outputGame(g, inL);
  }

}

nodeGame eraseGame(Ht_games ht_games, Ht_teams ht_teams, nodeGame head, char *game_name, int inL)
{
  Game aux = HTsearchGame(ht_games, game_name);
  if (aux == 0)
  {
    {
      printf("%d Jogo inexistente.\n", inL);
      return head;
    }
  }
  else
  {
    
  }

  if (aux->score1 > aux->score2)
  {
    withdrawVictory(ht_teams, aux->team1);
  }
  else
  {
    if (aux->score2 > aux->score1)
    {
      withdrawVictory(ht_teams, aux->team2);
    }
    else
    {
      
    }

  }

  head = popGame(head, game_name);
  HTdeleteGame(ht_games, game_name);
  aux = 0;
  return head;
}

void listGames(nodeGame head, int inL)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  listGames(head->next, inL);
  outputGame(head->ptr, inL);
}

void addTeam(Ht_teams *ht, nodeTeam *head, char *team_name, int inL)
{
  char *name;
  Team t;
  Team aux = HTsearchTeam(*ht, team_name);
  if (aux == 0)
  {
    {
      name = allocateWrite(team_name);
      t = newTeam(name, 0);
      *ht = HTinsertTeam(*ht, t);
      *head = pushTeam(*head, t);
      name = 0;
      return;
    }
  }
  else
  {
    
  }

  printf("%d Equipa existente.\n", inL);
}

void findTeam(Ht_teams ht, char *team_name, int inL)
{
  Team t = HTsearchTeam(ht, team_name);
  if (t != 0)
  {
    {
      outputTeam(t, inL);
      return;
    }
  }
  else
  {
    
  }

  printf("%d Equipa inexistente.\n", inL);
}

void updateScore(Ht_games ht_games, Ht_teams ht_teams, char *game_name, int score1, int score2, int inL)
{
  int prevS1;
  int prevS2;
  Game game = HTsearchGame(ht_games, game_name);
  if (game == 0)
  {
    {
      printf("%d Jogo inexistente.\n", inL);
      return;
    }
  }
  else
  {
    
  }

  prevS1 = game->score1;
  prevS2 = game->score2;
  game->score1 = score1;
  game->score2 = score2;
  changeWins(ht_teams, &game, score1, score2, prevS1, prevS2);
  game = 0;
}

void bestTeams(nodeTeam head, int inL)
{
  if (head == 0)
  {
    return;
  }
  else
  {
    {
      int i;
      int w = mostWins(head);
      int n = countTeams(head, w);
      Team *teams = nWinsTeams(head, n, w);
      qsort(teams, n, sizeof(Team *), compareQsort);
      printf("%d Melhores %d\n", inL, w);
      for (i = 0; i < n; i++)
        printf("%d * %s\n", inL, teams[i]->name);

      free(teams);
      teams = 0;
    }
  }

}

