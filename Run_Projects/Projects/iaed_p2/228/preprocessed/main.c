/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "hash_table.h"


int main()
{
  char cmd;
  ht *games = create_ht(572, free_game, get_game_name);
  ht *teams = create_ht(572, free_team, get_team_name);
  while (1)
  {
    cmd = new_sym_var(sizeof(char) * 8);
    switch (cmd)
    {
      case 'a':
        cmd_a(games, teams);
        break;

      case 'A':
        cmd_A(teams);
        break;

      case 'l':
        cmd_l(games);
        break;

      case 'p':
        cmd_p(games);
        break;

      case 'P':
        cmd_P(teams);
        break;

      case 'r':
        cmd_r(games, teams);
        break;

      case 's':
        cmd_s(games, teams);
        break;

      case 'g':
        cmd_g(teams);
        break;

      case 'x':
        free_ht(teams);
        free_ht(games);
        return 0;

    }

  }

  return 0;
}
