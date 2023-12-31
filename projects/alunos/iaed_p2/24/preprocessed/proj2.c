#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "team.h"
#include "match.h"
#include "hashtable.h"
#include "auxiliar.h"


Link addMatch(int nl, Hash matches, Hash teams, char *name, char *team1, char *team2, int score1, int score2);
void listMatches(int nl, Link head);
void searchMatch(int nl, Hash matches, char *name);
Link removeMatch(int nl, Hash matches, Hash teams, char *name);
void changeScore(int nl, Hash matches, Hash teams, char *name, int score1, int score2);
Link addTeam(int nl, Hash teams, char *name);
void searchTeam(int nl, Hash teams, char *name);
void findWinners(int nl, Link firstTeam);
void freeData(Link firstMatch, Link firstTeam);
int main()
{
  char command;
  char name[1024];
  char team1[1024];
  char team2[1024];
  int nl = 0;
  int score1;
  int score2;
  Hash matches = initHash();
  Hash teams = initHash();
  Link temp = 0;
  Link firstMatch = 0;
  Link lastMatch = 0;
  Link firstTeam = 0;
  Link lastTeam = 0;
  while (((command = getchar()) != 'x') && (command != EOF))
  {
    getchar();
    nl++;
    switch (command)
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
        temp = addMatch(nl, matches, teams, name, team1, team2, score1, score2);
        if (temp != 0)
      {
        insertDLL(&firstMatch, &lastMatch, temp);
      }
      else
      {
        
      }

        break;

      case 'l':
        listMatches(nl, firstMatch);
        break;

      case 'p':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        searchMatch(nl, matches, name);
        break;

      case 'r':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        temp = removeMatch(nl, matches, teams, name);
        if (temp != 0)
      {
        removeDLL(&firstMatch, &lastMatch, temp);
      }
      else
      {
        
      }

        break;

      case 's':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        changeScore(nl, matches, teams, name, score1, score2);
        break;

      case 'A':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        temp = addTeam(nl, teams, name);
        if (temp != 0)
      {
        insertDLL(&firstTeam, &lastTeam, temp);
      }
      else
      {
        
      }

        break;

      case 'P':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        searchTeam(nl, teams, name);
        break;

      case 'g':
        findWinners(nl, firstTeam);
        break;

    }

  }

  freeData(firstMatch, firstTeam);
  free(matches);
  free(teams);
  return 0;
}

Link addMatch(int nl, Hash matches, Hash teams, char *name, char *team1, char *team2, int score1, int score2)
{
  Link new = 0;
  Link teamNode = 0;
  Team team;
  Match match;
  if (searchHash(matches, name) == 0)
  {
    if ((searchHash(teams, team1) != 0) && (searchHash(teams, team2) != 0))
    {
      match = newMatch(name, team1, team2, score1, score2);
      new = newNode(name, match);
      insertHash(matches, name, new);
      if (score1 != score2)
      {
        if (score1 > score2)
        {
          teamNode = searchHash(teams, team1);
        }
        else
        {
          if (score1 < score2)
          {
            teamNode = searchHash(teams, team2);
          }
          else
          {
            
          }

        }

        team = (Team) teamNode->data;
        team->victories++;
      }
      else
      {
        
      }

    }
    else
    {
      printf("%d Equipa inexistente.\n", nl);
    }

  }
  else
  {
    printf("%d Jogo existente.\n", nl);
  }

  return new;
}

void listMatches(int nl, Link head)
{
  for (; head != 0; head = head->next_order)
  {
    Match match = (Match) head->data;
    printf("%d ", nl);
    printMatch(match);
  }

}

void searchMatch(int nl, Hash matches, char *name)
{
  Link matchNode = searchHash(matches, name);
  if (matchNode != 0)
  {
    Match match = (Match) matchNode->data;
    printf("%d ", nl);
    printMatch(match);
  }
  else
  {
    printf("%d Jogo inexistente.\n", nl);
  }

}

Link removeMatch(int nl, Hash matches, Hash teams, char *name)
{
  Link matchNode;
  Link teamNode;
  Match match;
  Team team;
  matchNode = searchHash(matches, name);
  if (matchNode != 0)
  {
    match = (Match) matchNode->data;
    removeHash(matches, name);
    if (match->score1 != match->score2)
    {
      if (match->score1 > match->score2)
      {
        teamNode = searchHash(teams, match->team1);
      }
      else
      {
        if (match->score1 < match->score2)
        {
          teamNode = searchHash(teams, match->team2);
        }
        else
        {
          
        }

      }

      team = (Team) teamNode->data;
      team->victories--;
    }
    else
    {
      
    }

    freeMatch((Match) matchNode->data);
  }
  else
  {
    printf("%d Jogo inexistente.\n", nl);
  }

  return matchNode;
}

void changeScore(int nl, Hash matches, Hash teams, char *name, int score1, int score2)
{
  Link matchNode;
  Link teamNode;
  Match match;
  Team team;
  matchNode = searchHash(matches, name);
  if (matchNode != 0)
  {
    match = (Match) matchNode->data;
    if (match->score1 != match->score2)
    {
      if (match->score1 > match->score2)
      {
        teamNode = searchHash(teams, match->team1);
      }
      else
      {
        if (match->score1 < match->score2)
        {
          teamNode = searchHash(teams, match->team2);
        }
        else
        {
          
        }

      }

      team = (Team) teamNode->data;
      team->victories--;
    }
    else
    {
      
    }

    if (score1 != score2)
    {
      if (score1 > score2)
      {
        teamNode = searchHash(teams, match->team1);
      }
      else
      {
        if (score1 < score2)
        {
          teamNode = searchHash(teams, match->team2);
        }
        else
        {
          
        }

      }

      team = (Team) teamNode->data;
      team->victories++;
    }
    else
    {
      
    }

    match->score1 = score1;
    match->score2 = score2;
  }
  else
  {
    printf("%d Jogo inexistente.\n", nl);
  }

}

Link addTeam(int nl, Hash teams, char *name)
{
  Link new = 0;
  if (searchHash(teams, name) == 0)
  {
    Team team = newTeam(name);
    new = newNode(name, team);
    insertHash(teams, name, new);
  }
  else
  {
    printf("%d Equipa existente.\n", nl);
  }

  return new;
}

void searchTeam(int nl, Hash teams, char *name)
{
  Link teamNode = searchHash(teams, name);
  if (teamNode != 0)
  {
    Team team = (Team) teamNode->data;
    printf("%d ", nl);
    printTeam(team);
  }
  else
  {
    printf("%d Equipa inexistente.\n", nl);
  }

}

void findWinners(int nl, Link firstTeam)
{
  Link temp;
  Team team;
  int victories;
  int mostVictories = 0;
  int count = 0;
  int i;
  char **teams = (char **) malloc(sizeof(char *));
  while (firstTeam != 0)
  {
    temp = firstTeam;
    firstTeam = firstTeam->next_order;
    team = (Team) temp->data;
    victories = team->victories;
    if (victories > mostVictories)
    {
      mostVictories = victories;
      count = 0;
    }
    else
    {
      
    }

    if (victories == mostVictories)
    {
      count++;
      teams = (char **) realloc(teams, (sizeof(char *)) * count);
      *((teams + count) - 1) = team->name;
    }
    else
    {
      
    }

  }

  sort(teams, count);
  if (count > 0)
  {
    printf("%d Melhores %d\n", nl, mostVictories);
    for (i = 0; i < count; i++)
    {
      printf("%d * %s\n", nl, teams[i]);
    }

  }
  else
  {
    
  }

  free(teams);
}

void freeData(Link firstMatch, Link firstTeam)
{
  Link temp;
  while (firstMatch != 0)
  {
    temp = firstMatch;
    firstMatch = firstMatch->next_order;
    freeMatch((Match) temp->data);
    freeNode(temp);
  }

  while (firstTeam != 0)
  {
    temp = firstTeam;
    firstTeam = firstTeam->next_order;
    freeTeam((Team) temp->data);
    freeNode(temp);
  }

}

