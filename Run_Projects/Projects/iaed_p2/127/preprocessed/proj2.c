/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "teams.h"
#include "commands.h"


void execute_command(char c, team ***teams_t_ptr, link **game_t_ptr, link *game_list, team **last_team, long int *cont, long int *max_len)
{
  switch (c)
  {
    case 'a':
      *game_t_ptr = command_a(game_list, *game_t_ptr, *teams_t_ptr, cont, max_len);
      getchar();
      break;

    case 'A':
      *teams_t_ptr = command_A(*teams_t_ptr, last_team, cont, max_len);
      getchar();
      break;

    case 'l':
      command_l(game_list, cont);
      getchar();
      break;

    case 'p':
      command_p(*game_t_ptr, cont, *max_len);
      getchar();
      break;

    case 'P':
      command_P(*teams_t_ptr, cont, *(max_len + 2));
      getchar();
      break;

    case 'r':
      command_r(game_list, *game_t_ptr, *teams_t_ptr, cont, max_len);
      getchar();
      break;

    case 's':
      command_s(*game_t_ptr, *teams_t_ptr, cont, max_len);
      getchar();
      break;

    case 'g':
      command_g(*last_team, cont, max_len);
      getchar();
      break;

  }

}

int main()
{
  long int cont = 0;
  long int *max_len;
  char c;
  link *game_tab;
  team **teams_tab;
  link *game_list;
  team **last_team;
  max_len = malloc((sizeof(long int)) * 4);
  *max_len = 883;
  *(max_len + 1) = 0;
  *(max_len + 2) = 883;
  *(max_len + 3) = 0;
  game_tab = malloc((sizeof(link)) * (*max_len));
  table_g_init(game_tab, *max_len);
  teams_tab = malloc((sizeof(team *)) * (*(max_len + 2)));
  table_t_init(teams_tab, *(max_len + 2));
  game_list = malloc((sizeof(link)) * 2);
  *game_list = 0;
  *(game_list + 1) = 0;
  last_team = malloc(sizeof(team *));
  *last_team = 0;
  while ((c = getchar()) != 'x')
  {
    execute_command(c, &teams_tab, &game_tab, game_list, last_team, &cont, max_len);
  }

  free(max_len);
  destroy_game_st(game_list);
  free(game_list);
  free(game_tab);
  destroy_team_st(*last_team);
  free(last_team);
  free(teams_tab);
  return 0;
}

