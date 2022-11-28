#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "Team_b2.h"


Team Tnew(char *name)
{
  Team new = (Team) malloc(sizeof(struct team));
  new->wins = 0;
  new->name = my_strdup(name);
  return new;
}

void Tdelete(Team team)
{
  free(team->name);
  free(team);
}

Team TchangeWins(Team team, int to_add)
{
  if ((Tgetwins(team) + to_add) >= 0)
  {
    team->wins += to_add;
  }
  else
  {
    
  }

  return team;
}

char *Tgetname(Team team)
{
  return team->name;
}

int Tgetwins(Team team)
{
  return team->wins;
}

int Tless(Team team1, Team team2)
{
  if (Tgetwins(team1) < Tgetwins(team2))
  {
    return 1;
  }
  else
  {
    if (Tgetwins(team1) == Tgetwins(team2))
    {
      return !(strcmp(team1->name, team2->name) < 0);
    }
    else
    {
      return 0;
    }

  }

}
