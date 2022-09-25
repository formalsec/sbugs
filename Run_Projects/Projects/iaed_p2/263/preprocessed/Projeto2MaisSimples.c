/*File generated by PreProcessor.py*/


#include "estruturas_info.h"  


game *NEWGAME(char *name_game, char *team1, char *team2, int score1, int score2, int order)
{
  game *newgame = malloc(sizeof(game));
  newgame->name_game = malloc((sizeof(char)) * (strlen(name_game) + 1));
  newgame->team1 = malloc((sizeof(char)) * (strlen(team1) + 1));
  newgame->team2 = malloc((sizeof(char)) * (strlen(team2) + 1));
  newgame->name_game = strcpy(newgame->name_game, name_game);
  newgame->team1 = strcpy(newgame->team1, team1);
  newgame->team2 = strcpy(newgame->team2, team2);
  newgame->score1 = score1;
  newgame->score2 = score2;
  newgame->order = order;
  newgame->next = 0;
  return newgame;
}

team *NEWTEAM(char *name_team)
{
  team *newteam = malloc(sizeof(team));
  newteam->name_team = malloc((sizeof(char)) * (strlen(name_team) + 1));
  newteam->name_team = strcpy(newteam->name_team, name_team);
  newteam->wins = 0;
  newteam->next = 0;
  return newteam;
}

game *PutsAsHeadListGame(game *head, char *name_game, char *team1, char *team2, int score1, int score2, int order)
{
  game *newgame = NEWGAME(name_game, team1, team2, score1, score2, order);
  newgame->next = head;
  return newgame;
}

team *PutsAsHeadListTeam(team *head, char *name_team)
{
  team *newteam = NEWTEAM(name_team);
  newteam->next = head;
  return newteam;
}

int ReturnsHashGameIndex(char *name_game)
{
  int h = 0;
  int a = 127;
  for (; (*name_game) != '\0'; name_game++)
    h = ((a * h) + (*name_game)) % 1997;

  return h;
}

int ReturnsHashTeamIndex(char *name_team)
{
  int h = 0;
  int a = 127;
  for (; (*name_team) != '\0'; name_team++)
    h = ((a * h) + (*name_team)) % 1997;

  return h;
}

game *LooksUpInGameHash(game **hashtablegame, char *name_game)
{
  int index = ReturnsHashGameIndex(name_game);
  game *aux;
  aux = hashtablegame[index];
  while (aux != 0)
  {
    if (strcmp(aux->name_game, name_game) == 0)
    {
      return aux;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return aux;
}

void FreeGameInfo(game *t)
{
  free(t->name_game);
  free(t->team1);
  free(t->team2);
  free(t);
}

game *DeleteGame(game *head, char *name_game)
{
  game *t;
  game *prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->name_game, name_game) == 0)
    {
      if (t == head)
      {
        head = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      FreeGameInfo(t);
      return head;
    }
    else
    {
      
    }

  }

  return head;
}

team *LooksUpInTeamHash(team **hashtableteam, char *name_team)
{
  int index = ReturnsHashTeamIndex(name_team);
  team *aux;
  aux = hashtableteam[index];
  while (aux != 0)
  {
    if (strcmp(aux->name_team, name_team) == 0)
    {
      return aux;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return aux;
}

void InitializesHashTableGame(game **hashtablegame)
{
  int i;
  for (i = 0; i < 1997; i++)
    hashtablegame[i] = 0;

}

void InitializesHashTableTeam(team **hashtableteam)
{
  int i;
  for (i = 0; i < 1997; i++)
    hashtableteam[i] = 0;

}

void AddsGame(char *name_game, char *team1, char *team2, int score1, int score2, game **hashtablegame, team **hashtableteam, int NL, int order)
{
  int index;
  team *aux;
  game *auxgame;
  if (LooksUpInGameHash(hashtablegame, name_game) != 0)
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if (LooksUpInTeamHash(hashtableteam, team1) == 0)
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      if (LooksUpInTeamHash(hashtableteam, team2) == 0)
      {
        printf("%d Equipa inexistente.\n", NL);
      }
      else
      {
        index = ReturnsHashGameIndex(name_game);
        hashtablegame[index] = PutsAsHeadListGame(hashtablegame[index], name_game, team1, team2, score1, score2, order);
        auxgame = LooksUpInGameHash(hashtablegame, name_game);
        if (auxgame->score1 > auxgame->score2)
        {
          aux = LooksUpInTeamHash(hashtableteam, team1);
          aux->wins += 1;
        }
        else
        {
          if (auxgame->score1 < auxgame->score2)
          {
            aux = LooksUpInTeamHash(hashtableteam, team2);
            aux->wins += 1;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void AddsTeam(char *name_team, team **hashtableteam, int NL)
{
  int index;
  if (LooksUpInTeamHash(hashtableteam, name_team) != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    index = ReturnsHashTeamIndex(name_team);
    hashtableteam[index] = PutsAsHeadListTeam(hashtableteam[index], name_team);
  }

}

void PrintsGame(char *name_game, game **hashtablegame, int NL)
{
  game *auxgame;
  if (LooksUpInGameHash(hashtablegame, name_game) == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    auxgame = LooksUpInGameHash(hashtablegame, name_game);
    printf("%d %s %s %s %d %d\n", NL, auxgame->name_game, auxgame->team1, auxgame->team2, auxgame->score1, auxgame->score2);
  }

}

void PrintsTeam(char *name_team, team **hashtableteam, int NL)
{
  team *aux;
  if (LooksUpInTeamHash(hashtableteam, name_team) == 0)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    aux = LooksUpInTeamHash(hashtableteam, name_team);
    printf("%d %s %d\n", NL, aux->name_team, aux->wins);
  }

}

void ChangesScore(char *name_game, int score1, int score2, game **hashtablegame, team **hashtableteam, int NL)
{
  game *oldgame;
  team *aux;
  team *aux1;
  team *aux2;
  oldgame = LooksUpInGameHash(hashtablegame, name_game);
  if (oldgame == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    if (oldgame->score1 > oldgame->score2)
    {
      if (score1 == score2)
      {
        aux = LooksUpInTeamHash(hashtableteam, oldgame->team1);
        aux->wins -= 1;
      }
      else
      {
        if (score1 < score2)
        {
          aux1 = LooksUpInTeamHash(hashtableteam, oldgame->team1);
          aux2 = LooksUpInTeamHash(hashtableteam, oldgame->team2);
          aux1->wins -= 1;
          aux2->wins += 1;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (oldgame->score1 == oldgame->score2)
      {
        if (score1 > score2)
        {
          aux = LooksUpInTeamHash(hashtableteam, oldgame->team1);
          aux->wins += 1;
        }
        else
        {
          if (score1 < score2)
          {
            aux = LooksUpInTeamHash(hashtableteam, oldgame->team2);
            aux->wins += 1;
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (oldgame->score1 < oldgame->score2)
        {
          if (score1 > score2)
          {
            aux1 = LooksUpInTeamHash(hashtableteam, oldgame->team1);
            aux2 = LooksUpInTeamHash(hashtableteam, oldgame->team2);
            aux1->wins += 1;
            aux2->wins -= 1;
          }
          else
          {
            if (score1 == score2)
            {
              aux = LooksUpInTeamHash(hashtableteam, oldgame->team2);
              aux->wins -= 1;
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

    }

    oldgame->score1 = score1;
    oldgame->score2 = score2;
  }

}

void ListsGames(game **hashtablegame, int order, int NL)
{
  game *aux;
  int i;
  int e;
  for (e = 0; e < order; e++)
  {
    for (i = 0; i < 1997; i++)
    {
      aux = hashtablegame[i];
      while (aux != 0)
      {
        if (aux->order == e)
        {
          printf("%d %s %s %s %d %d\n", NL, aux->name_game, aux->team1, aux->team2, aux->score1, aux->score2);
          break;
        }
        else
        {
          
        }

        aux = aux->next;
      }

    }

  }

}

void ErasesGame(char *name_game, game **hashtablegame, team **hashtableteam, int NL)
{
  game *erasinggame;
  team *aux;
  int index = ReturnsHashGameIndex(name_game);
  erasinggame = LooksUpInGameHash(hashtablegame, name_game);
  if (erasinggame == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    if (erasinggame->score1 > erasinggame->score2)
    {
      aux = LooksUpInTeamHash(hashtableteam, erasinggame->team1);
      aux->wins -= 1;
    }
    else
    {
      if (erasinggame->score1 < erasinggame->score2)
      {
        aux = LooksUpInTeamHash(hashtableteam, erasinggame->team2);
        aux->wins -= 1;
      }
      else
      {
        
      }

    }

  }

  hashtablegame[index] = DeleteGame(hashtablegame[index], name_game);
}

int main()
{
  int NL = 1;
  int running = 1;
  int c;
  int score1 = 0;
  int score2 = 0;
  int order = 0;
  char name_team[1023];
  char name_game[1023];
  char team1[1023];
  char team2[1023];
  team *hashtableteam[1997];
  game *hashtablegame[1997];
  InitializesHashTableTeam(hashtableteam);
  InitializesHashTableGame(hashtablegame);
  while (running == 1)
  {
    switch (c = getchar())
    {
      case 'A':
        getchar();
        for (int name_team_index = 0; name_team_index < 10; name_team_index++)
      {
        name_team[name_team_index] = new_sym_var(sizeof(char) * 8);
      }

        name_team[10 - 1] = '\0';
        AddsTeam(name_team, hashtableteam, NL);
        NL++;
        break;

      case 'P':
        getchar();
        for (int name_team_index = 0; name_team_index < 10; name_team_index++)
      {
        name_team[name_team_index] = new_sym_var(sizeof(char) * 8);
      }

        name_team[10 - 1] = '\0';
        PrintsTeam(name_team, hashtableteam, NL);
        NL++;
        break;

      case 'a':
        getchar();
        for (int name_game_index = 0; name_game_index < 10; name_game_index++)
      {
        name_game[name_game_index] = new_sym_var(sizeof(char) * 8);
      }

        name_game[10 - 1] = '\0';
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
        AddsGame(name_game, team1, team2, score1, score2, hashtablegame, hashtableteam, NL, order);
        NL++;
        order++;
        break;

      case 'p':
        getchar();
        for (int name_game_index = 0; name_game_index < 10; name_game_index++)
      {
        name_game[name_game_index] = new_sym_var(sizeof(char) * 8);
      }

        name_game[10 - 1] = '\0';
        PrintsGame(name_game, hashtablegame, NL);
        NL++;
        break;

      case 's':
        getchar();
        for (int name_game_index = 0; name_game_index < 10; name_game_index++)
      {
        name_game[name_game_index] = new_sym_var(sizeof(char) * 8);
      }

        name_game[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        ChangesScore(name_game, score1, score2, hashtablegame, hashtableteam, NL);
        NL++;
        break;

      case 'l':
        getchar();
        ListsGames(hashtablegame, order, NL);
        NL++;
        break;

      case 'r':
        getchar();
        for (int name_game_index = 0; name_game_index < 10; name_game_index++)
      {
        name_game[name_game_index] = new_sym_var(sizeof(char) * 8);
      }

        name_game[10 - 1] = '\0';
        ErasesGame(name_game, hashtablegame, hashtableteam, NL);
        NL++;
        break;

      case 'x':
        running = 0;
        break;

    }

  }

  return 0;
}

