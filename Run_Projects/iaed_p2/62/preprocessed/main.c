/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"
#include "games.h"


int main()
{
  TeamHT team_ht = team_ht_init(727);
  GameHT game_ht = game_ht_init(&team_ht, 727);
  unsigned long int NL = 1;
  char command;
  char name_buff[1024];
  char team1_buff[1024];
  char team2_buff[1024];
  int score1_buff;
  int score2_buff;
  while ((command = getchar()) != 'x')
  {
    switch (command)
    {
      case 'a':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        for (int team1_buff_index = 0; team1_buff_index < 10; team1_buff_index++)
      {
        team1_buff[team1_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        team1_buff[10 - 1] = '\0';
        for (int team2_buff_index = 0; team2_buff_index < 10; team2_buff_index++)
      {
        team2_buff[team2_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        team2_buff[10 - 1] = '\0';
        score1_buff = new_sym_var(sizeof(int) * 8);
        score2_buff = new_sym_var(sizeof(int) * 8);
        game_ht_insert(&game_ht, name_buff, team1_buff, team2_buff, score1_buff, score2_buff, NL);
        break;

      case 'l':
        game_ht_print_order(game_ht, NL);
        break;

      case 'p':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        game_ht_search_print(game_ht, name_buff, NL);
        break;

      case 'r':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        game_ht_delete(&game_ht, name_buff, NL);
        break;

      case 's':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        score1_buff = new_sym_var(sizeof(int) * 8);
        score2_buff = new_sym_var(sizeof(int) * 8);
        game_ht_change_score(game_ht, name_buff, score1_buff, score2_buff, NL);
        break;

      case 'A':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        team_ht_insert(&team_ht, name_buff, NL);
        break;

      case 'P':
        for (int name_buff_index = 0; name_buff_index < 10; name_buff_index++)
      {
        name_buff[name_buff_index] = new_sym_var(sizeof(char) * 8);
      }

        name_buff[10 - 1] = '\0';
        team_ht_search_print(team_ht, name_buff, NL);
        break;

      case 'g':
        team_ht_print_best(team_ht, NL);
        break;

      default:
        continue;

    }

    NL++;
  }

  game_ht_free(game_ht);
  team_ht_free(team_ht);
  return 0;
}
