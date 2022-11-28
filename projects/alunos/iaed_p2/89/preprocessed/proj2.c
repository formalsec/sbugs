#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <string.h>
#include "Team2.h"
#include "Game2.h"


void getcmd(char *cmd);
int main()
{
  char cmd;
  int NL = 0;
  BTlink Tree_team = BTinit();
  BGlink Tree_game = BGinit();
  int Game_elem = 0;
  Team team;
  char name[1025];
  char team1[1025];
  char team2[1025];
  int s1;
  int s2;
  getcmd(&cmd);
  NL++;
  while (cmd != 'x')
  {
    switch (cmd)
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
        s1 = new_sym_var(sizeof(int) * 8);
        s2 = new_sym_var(sizeof(int) * 8);
        team = addGame(name, team1, team2, s1, s2, &Tree_game, Tree_team, &Game_elem, NL);
        if (team)
      {
        TchangeWins(team, 1);
      }
      else
      {
        
      }

        break;

      case 'l':
        listAllGames(Tree_game, Game_elem, NL);
        break;

      case 'A':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        addTeam(name, &Tree_team, NL);
        break;

      case 'p':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        searchGame(name, Tree_game, NL);
        break;

      case 'P':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        searchTeam(name, Tree_team, NL);
        break;

      case 'r':
        for (int name_index = 0; name_index < 10; name_index++)
      {
        name[name_index] = new_sym_var(sizeof(char) * 8);
      }

        name[10 - 1] = '\0';
        team = deleteGame(name, &Tree_game, &Game_elem, NL);
        if (team)
      {
        TchangeWins(team, -1);
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
        s1 = new_sym_var(sizeof(int) * 8);
        s2 = new_sym_var(sizeof(int) * 8);
        change_scores(name, s1, s2, Tree_game, NL);
        break;

      case 'g':
        showwinners(Tree_team, NL);
        break;

    }

    getcmd(&cmd);
    NL++;
  }

  freeAllGames(&Tree_game);
  freeAllTeams(&Tree_team);
  return 0;
}

void getcmd(char *cmd)
{
  char c;
  while (((c = getchar()) < 65) || (c > 122))
    ;

  *cmd = c;
}
