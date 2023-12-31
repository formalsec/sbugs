#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "auxiliary.h"
#include "structures.h"
#include "commands.h"


int main()
{
  int i;
  unsigned int NL = 0;
  game **first_game = malloc(sizeof(game *));
  game **last_game = malloc(sizeof(game *));
  glink **game_table = malloc((sizeof(glink *)) * 419);
  tlink **team_table = malloc((sizeof(tlink *)) * 419);
  *first_game = 0;
  *last_game = 0;
  for (i = 0; i < 419; i++)
  {
    game_table[i] = 0;
    team_table[i] = 0;
  }

  while (1)
  {
    char com;
    NL++;
    switch (com = getchar())
    {
      case 'A':
      {
        getchar();
        add_team(NL, team_table);
        break;
      }

      case 'a':
      {
        getchar();
        add_game(NL, first_game, last_game, game_table, team_table);
        break;
      }

      case 'l':
      {
        getchar();
        list_games(NL, first_game);
        break;
      }

      case 'P':
      {
        getchar();
        search_team(NL, team_table);
        break;
      }

      case 'p':
      {
        getchar();
        search_game(NL, game_table);
        break;
      }

      case 'r':
      {
        getchar();
        remove_game(NL, first_game, last_game, game_table, team_table);
        break;
      }

      case 's':
      {
        getchar();
        change_score(NL, game_table, team_table);
        break;
      }

      case 'g':
      {
        getchar();
        best_teams(NL, team_table);
        break;
      }

      case 'x':
        free_memory(game_table, team_table, first_game, last_game);
        return 0;

      default:
      {
        break;
      }

    }

  }

  return 1;
}

