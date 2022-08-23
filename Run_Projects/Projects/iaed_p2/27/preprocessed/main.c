/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "hashtable_team.h"
#include "hashtable_game.h"


int NL = 1;
int main()
{
  ht_team *ht_team = ht_create_hteam();
  ht_game *ht_game = ht_create_hgame();
  GAME *linkedlist = 0;
  while (1)
  {
    unsigned int j = 0;
    char command = '\0';
    char input[3080] = "\0";
    command = new_sym_var(sizeof(char) * 8);
    switch (command)
    {
      case 'a':
      {
        linkedlist = addGame(NL, ht_game, ht_team, linkedlist);
        NL++;
        break;
      }

      case 'A':
      {
        TEAM *team = 0;
        for (int input_index = 0; input_index < 10; input_index++)
        {
          input[input_index] = new_sym_var(sizeof(char) * 8);
        }

        input[10 - 1] = '\0';
        team = getTeam(input);
        ht_set_team(NL, ht_team, team);
        NL++;
        break;
      }

      case 'l':
      {
        GAME *paux = 0;
        if (linkedlist == 0)
        {
          {
            NL++;
            break;
          }
        }
        else
        {
          
        }

        paux = linkedlist;
        while (paux != 0)
        {
          printf("%d %s %s %s %d %d\n", NL, paux->name, paux->team1->name, paux->team2->name, paux->score[0], paux->score[1]);
          if (paux->pnext != 0)
          {
            {
              paux = paux->pnext;
            }
          }
          else
          {
            {
              break;
            }
          }

        }

        NL++;
        break;
      }

      case 'p':
      {
        GAME *game = 0;
        for (int input_index = 0; input_index < 10; input_index++)
        {
          input[input_index] = new_sym_var(sizeof(char) * 8);
        }

        input[10 - 1] = '\0';
        game = ht_get_game(ht_game, input);
        if (game != 0)
        {
          {
            printf("%d %s %s %s %d %d\n", NL, game->name, game->team1->name, game->team2->name, game->score[0], game->score[1]);
          }
        }
        else
        {
          {
            printf("%d Jogo inexistente.\n", NL);
          }
        }

        NL++;
        break;
      }

      case 'P':
      {
        TEAM *team = 0;
        for (int input_index = 0; input_index < 10; input_index++)
        {
          input[input_index] = new_sym_var(sizeof(char) * 8);
        }

        input[10 - 1] = '\0';
        team = ht_get_team(ht_team, input);
        if (team != 0)
        {
          {
            printf("%d %s %d\n", NL, team->name, team->gameswon);
          }
        }
        else
        {
          {
            printf("%d Equipa inexistente.\n", NL);
          }
        }

        NL++;
        break;
      }

      case 'r':
      {
        GAME *game = 0;
        for (int input_index = 0; input_index < 10; input_index++)
        {
          input[input_index] = new_sym_var(sizeof(char) * 8);
        }

        input[10 - 1] = '\0';
        game = ht_get_game(ht_game, input);
        if (game != 0)
        {
          {
            linkedlist = ht_remove_game(ht_game, ht_team, game, linkedlist);
          }
        }
        else
        {
          {
            printf("%d Jogo inexistente.\n", NL);
          }
        }

        NL++;
        break;
      }

      case 's':
      {
        GAME *auxgame = 0;
        char name[1024] = "\0";
        int score1 = 0;
        int score2 = 0;
        for (int name_index = 0; name_index < 10; name_index++)
        {
          name[name_index] = new_sym_var(sizeof(char) * 8);
        }

        name[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        auxgame = ht_get_game(ht_game, name);
        if (auxgame == 0)
        {
          {
            printf("%d Jogo inexistente.\n", NL);
            NL++;
            break;
          }
        }
        else
        {
          {
            if (auxgame->score[0] > auxgame->score[1])
            {
              {
                j = 1;
              }
            }
            else
            {
              if (auxgame->score[1] > auxgame->score[0])
              {
                {
                  j = 2;
                }
              }
              else
              {
                {
                  j = 3;
                }
              }

            }

          }
        }

        auxgame->score[0] = score1;
        auxgame->score[1] = score2;
        if ((auxgame->score[1] > auxgame->score[0]) && (j == 1))
        {
          {
            TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
            TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
            team->gameswon++;
            auxteam->gameswon--;
          }
        }
        else
        {
          if ((auxgame->score[1] == auxgame->score[0]) && (j == 1))
          {
            {
              TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
              auxteam->gameswon--;
            }
          }
          else
          {
            if ((auxgame->score[1] > auxgame->score[0]) && (j == 3))
            {
              {
                TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                team->gameswon++;
              }
            }
            else
            {
              if ((auxgame->score[0] > auxgame->score[1]) && (j == 3))
              {
                {
                  TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                  auxteam->gameswon++;
                }
              }
              else
              {
                if ((auxgame->score[0] > auxgame->score[1]) && (j == 2))
                {
                  {
                    TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                    TEAM *auxteam = ht_get_team(ht_team, auxgame->team1->name);
                    auxteam->gameswon++;
                    team->gameswon--;
                  }
                }
                else
                {
                  if ((auxgame->score[0] == auxgame->score[1]) && (j == 2))
                  {
                    {
                      TEAM *team = ht_get_team(ht_team, auxgame->team2->name);
                      team->gameswon--;
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

        NL++;
        break;
      }

      case 'g':
      {
        find_max(ht_team, NL);
        NL++;
        break;
      }

      case 'x':
      {
        ht_dump_game(ht_game);
        ht_dump_team(ht_team);
        free(ht_game->entries);
        free(ht_team->entries);
        free(ht_game);
        free(ht_team);
        return 0;
      }

      default:
        break;

    }

  }

}

