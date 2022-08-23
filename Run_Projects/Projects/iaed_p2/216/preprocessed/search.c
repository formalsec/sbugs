/*File generated by PreProcessor.py*/


#include "search.h"


void searchGame()
{
  hashNode * get;
  char name[MAXC];
  for (int name_index = 0; name_index < MAXC; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[MAXC - 1] = '\0';
  get = getNodeGames(name);
  if (get == 0)
  {
    {
      printf("%d Jogo inexistente.\n", counter);
      return;
    }
  }
  else
  {
    printf("%d %s %s %s %d %d\n", counter, get->point->name, get->point->team1, get->point->team2, get->point->score1, get->point->score2);
  }

}

void searchTeam()
{
  hashNode * get;
  char team[MAXC];
  for (int team_index = 0; team_index < MAXC; team_index++)
  {
    team[team_index] = new_sym_var(sizeof(char) * 8);
  }

  team[MAXC - 1] = '\0';
  get = getNodeTeams(team);
  if (get == 0)
  {
    {
      printf("%d Equipa inexistente.\n", counter);
      return;
    }
  }
  else
  {
    printf("%d %s %d\n", counter, get->point->name, get->point->won);
  }

}

