#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "auxiliary_funcs.h"


int length(char str[1024])
{
  int i;
  int cont = 0;
  for (i = 0; str[i] != '\0'; i++)
    cont++;

  return cont;
}

void strCopy(char *str1, char *str2)
{
  int i;
  for (i = 0; (*(str1 + i)) != '\0'; i++)
    *(str2 + i) = *(str1 + i);

  *(str2 + i) = '\0';
}

char *allocateWrite(char str[1024])
{
  int len = length(str) + 1;
  char *ptr = malloc((sizeof(char)) * len);
  strCopy(str, ptr);
  return ptr;
}

int compareQsort(const void *a, const void *b)
{
  const Team *t1 = (Team *) a;
  const Team *t2 = (Team *) b;
  return strcmp((*t1)->name, (*t2)->name);
}

void withdrawVictory(Ht_teams ht, char *name)
{
  Team t = HTsearchTeam(ht, name);
  t->won--;
  t = 0;
}

void addVictory(Ht_teams ht, char *name)
{
  Team t = HTsearchTeam(ht, name);
  t->won++;
  t = 0;
}

int mostWins(nodeTeam head)
{
  if (head == 0)
  {
    return -1;
  }
  else
  {
    unsigned int w = head->ptr->won;
    nodeTeam aux;
    for (aux = head->next; aux != 0; aux = aux->next)
    {
      if (aux->ptr->won > w)
      {
        w = aux->ptr->won;
      }
      else
      {
        
      }

    }

    aux = 0;
    return w;
  }

}

int countTeams(nodeTeam head, unsigned int w)
{
  int c;
  nodeTeam aux;
  for (c = 0, aux = head; aux != 0; aux = aux->next)
  {
    if (aux->ptr->won == w)
    {
      c++;
    }
    else
    {
      
    }

  }

  aux = 0;
  return c;
}

Team *nWinsTeams(nodeTeam head, int n, unsigned int w)
{
  int i;
  nodeTeam aux;
  Team *teams = malloc(n * (sizeof(Team)));
  for (i = 0, aux = head; aux != 0; aux = aux->next)
  {
    if (aux->ptr->won == w)
    {
      teams[i] = aux->ptr;
      i++;
    }
    else
    {
      
    }

  }

  aux = 0;
  return teams;
}

void changeWins(Ht_teams ht, Game *game, int score1, int score2, int prev1, int prev2)
{
  if (score1 > score2)
  {
    if (prev2 > prev1)
    {
      addVictory(ht, (*game)->team1);
      withdrawVictory(ht, (*game)->team2);
    }
    else
    {
      if (prev1 == prev2)
      {
        addVictory(ht, (*game)->team1);
      }
      else
      {
        
      }

    }

  }
  else
  {
    if (score2 > score1)
    {
      if (prev1 > prev2)
      {
        addVictory(ht, (*game)->team2);
        withdrawVictory(ht, (*game)->team1);
      }
      else
      {
        if (prev1 == prev2)
        {
          addVictory(ht, (*game)->team2);
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (prev1 > prev2)
      {
        withdrawVictory(ht, (*game)->team1);
      }
      else
      {
        if (prev2 > prev1)
        {
          withdrawVictory(ht, (*game)->team2);
        }
        else
        {
          
        }

      }

    }

  }

}

void outputGame(Game game, int outL)
{
  printf("%d %s %s %s %d %d\n", outL, game->name, game->team1, game->team2, game->score1, game->score2);
}

void outputTeam(Team team, int outL)
{
  printf("%d %s %d\n", outL, team->name, team->won);
}

void freeMemory(Ht_games htg, Ht_teams htt, nodeGame hg, nodeTeam ht)
{
  freeHTGames(htg);
  freeHTTeams(htt);
  hg = destroyLinkedGames(hg);
  ht = destroyLinkedTeams(ht);
}
