/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Structures.h"


char *cut_the_name(char *name)
{
  int len = strlen(name) + 1;
  if (name[len - 1] == '\n')
  {
    {
      name[len - 1] = '\0';
    }
  }
  else
  {
    
  }

  return name;
}

int main()
{
  int teams_size = 10001;
  int games_size = 10001;
  int max_games_won = 0;
  int second_max_games_won = 0;
  int teams_with_max_games_won = 0;
  int teams_with_second_max_games_won = 0;
  int condition = 0;
  int counter = 0;
  int teams_number = 0;
  int games_number = 0;
  int number = 1;
  int key;
  int team1_score;
  int team2_score;
  char *letter;
  char input[3100];
  team *teams_hash_table = (team *) malloc((sizeof(team)) * teams_size);
  game *games_hash_table = (game *) malloc((sizeof(game)) * games_size);
  char *game_name = malloc((sizeof(char)) * 1024);
  char *team1_name = malloc((sizeof(char)) * 1024);
  char *team2_name = malloc((sizeof(char)) * 1024);
  teams_initialize(teams_hash_table, teams_size);
  games_initialize(games_hash_table, games_size);
  while (condition == 0)
  {
    counter++;
    fgets(input, 3100, stdin);
    letter = strtok(input, " ");
    if (letter[0] == 'x')
    {
      {
        condition = 1;
        break;
      }
    }
    else
    {
      if (strcmp(letter, "a") == 0)
      {
        {
          game_name = strtok(0, ":");
          team1_name = strtok(0, ":");
          team2_name = strtok(0, ":");
          team1_score = atoi(strtok(0, ":"));
          team2_score = atoi(strtok(0, "\n"));
          create_game(game_name, team1_name, team2_name, team1_score, team2_score, games_hash_table, games_size, teams_hash_table, teams_size, counter, &games_number, &max_games_won, &teams_with_max_games_won, &number, &second_max_games_won, &teams_with_second_max_games_won);
        }
      }
      else
      {
        if (strcmp(letter, "A") == 0)
        {
          {
            team1_name = strtok(0, "\n");
            team1_name = cut_the_name(team1_name);
            create_team(team1_name, teams_hash_table, teams_size, counter, &teams_number, max_games_won, &teams_with_max_games_won);
          }
        }
        else
        {
          if (strcmp(letter, "p") == 0)
          {
            {
              game_name = strtok(0, "\n");
              game_name = cut_the_name(game_name);
              key = games_search(game_name, games_hash_table, games_size);
              game_errors(key, games_hash_table, counter);
            }
          }
          else
          {
            if (strcmp(letter, "P") == 0)
            {
              {
                team1_name = strtok(0, "\n");
                team1_name = cut_the_name(team1_name);
                key = teams_search(team1_name, teams_hash_table, teams_size);
                team_errors(key, teams_hash_table, counter);
              }
            }
            else
            {
              if (letter[0] == 'g')
              {
                {
                  find_team_with_more_games_won(teams_hash_table, teams_size, teams_with_max_games_won, max_games_won, counter);
                }
              }
              else
              {
                if (strcmp(letter, "r") == 0)
                {
                  {
                    game_name = strtok(0, "\n");
                    game_name = cut_the_name(game_name);
                    remove_game(game_name, games_hash_table, games_size, teams_hash_table, teams_size, &max_games_won, &teams_with_max_games_won, &second_max_games_won, &teams_with_second_max_games_won, teams_number, &games_number, counter);
                  }
                }
                else
                {
                  if (strcmp(letter, "s") == 0)
                  {
                    {
                      game_name = strtok(0, ":");
                      team1_score = atoi(strtok(0, ":"));
                      team2_score = atoi(strtok(0, "\n"));
                      change_score(game_name, team1_score, team2_score, games_hash_table, games_size, teams_hash_table, teams_size, &max_games_won, &teams_with_max_games_won, &second_max_games_won, &teams_with_second_max_games_won, teams_number, counter);
                    }
                  }
                  else
                  {
                    if (letter[0] == 'l')
                    {
                      {
                        list_all_the_games(games_hash_table, games_size, games_number, counter);
                      }
                    }
                    else
                    {
                      
                    }

                  }

                }

              }

            }

          }

        }

      }

    }

  }

  free_teams(teams_hash_table, teams_size);
  free_games(games_hash_table, games_size);
  free(teams_hash_table);
  free(games_hash_table);
  return 0;
}

