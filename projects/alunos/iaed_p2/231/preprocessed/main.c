#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include "team.h"
#include "game.h"


int main()
{
  char *command;
  char *gameName;
  char *team;
  char *team2;
  int nGames = 1;
  int nCommand = 1;
  int score1;
  int score2;
  int M;
  int MT1;
  int MT2;
  int i;
  TeamNode *t;
  TeamNode *t2;
  GameNode *g;
  TeamNode *teamHashTable[101];
  GameNode *gameHashTable[199];
  for (i = 0; i <= (101 - 1); i++)
  {
    teamHashTable[i] = 0;
  }

  for (i = 0; i <= (199 - 1); i++)
  {
    gameHashTable[i] = 0;
  }

  command = malloc(sizeof(char));
  do
  {
    for (int command_index = 0; command_index < 10; command_index++)
    {
      command[command_index] = new_sym_var(sizeof(char) * 8);
    }

    command[10 - 1] = '\0';
    switch (*command)
    {
      case 'a':
        gameName = malloc(1023 * (sizeof(char)));
        team = malloc(1023 * (sizeof(char)));
        team2 = malloc(1023 * (sizeof(char)));
        for (int gameName_index = 0; gameName_index < 10; gameName_index++)
      {
        gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
      }

        gameName[10 - 1] = '\0';
        for (int team_index = 0; team_index < 10; team_index++)
      {
        team[team_index] = new_sym_var(sizeof(char) * 8);
      }

        team[10 - 1] = '\0';
        for (int team2_index = 0; team2_index < 10; team2_index++)
      {
        team2[team2_index] = new_sym_var(sizeof(char) * 8);
      }

        team2[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        M = hashGame(gameName);
        MT1 = hashTeam(team);
        MT2 = hashTeam(team2);
        if (teamHashTable[MT1] == 0)
      {
        printf("%d Equipa inexistente.\n", nCommand);
        free(gameName);
        free(team);
        free(team2);
        break;
      }
      else
      {
        t = searchTeam(teamHashTable[MT1], team);
        if (t->exists == 0)
        {
          printf("%d Equipa inexistente.\n", nCommand);
          free(gameName);
          free(team);
          free(team2);
          break;
        }
        else
        {
          if (teamHashTable[MT2] == 0)
          {
            printf("%d Equipa inexistente.\n", nCommand);
            free(gameName);
            free(team);
            free(team2);
            break;
          }
          else
          {
            t2 = searchTeam(teamHashTable[MT2], team2);
            if (t->exists == 0)
            {
              printf("%d Equipa inexistente.\n", nCommand);
              free(gameName);
              free(team);
              free(team2);
              break;
            }
            else
            {
              if (gameHashTable[M] == 0)
              {
                gameHashTable[M] = addGame(0, gameName, t, t2, score1, score2, nGames);
                nGames++;
              }
              else
              {
                g = searchGame(gameHashTable[M], gameName);
                if (g->id != 0)
                {
                  printf("%d Jogo existente.\n", nCommand);
                  free(gameName);
                  free(team);
                  free(team2);
                  break;
                }
                else
                {
                  gameHashTable[M] = addGame(gameHashTable[M], gameName, t, t2, score1, score2, nGames);
                }

              }

            }

          }

        }

      }

        free(gameName);
        free(team);
        free(team2);
        nCommand++;
        break;

      case 'p':
        gameName = malloc(1023 * (sizeof(char)));
        for (int gameName_index = 0; gameName_index < 10; gameName_index++)
      {
        gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
      }

        gameName[10 - 1] = '\0';
        M = hashGame(gameName);
        if (gameHashTable[M] == 0)
      {
        printf("%d Jogo inexistente.", nCommand);
        free(gameName);
        nCommand++;
        break;
      }
      else
      {
        g = searchGame(gameHashTable[M], gameName);
        if (g->id != 0)
        {
          printf("%d %s %s %s %d %d", nCommand, gameName, g->team1->name, g->team2->name, g->score1, g->score2);
        }
        else
        {
          printf("%d Jogo inexistente.", nCommand);
          free(gameName);
          nCommand++;
          break;
        }

      }

        free(gameName);
        nCommand++;
        break;

      case 'r':
        gameName = malloc(1023 * (sizeof(char)));
        for (int gameName_index = 0; gameName_index < 10; gameName_index++)
      {
        gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
      }

        gameName[10 - 1] = '\0';
        M = hashGame(gameName);
        if (gameHashTable[M] == 0)
      {
        printf("%d Jogo inexistente.", nCommand);
        free(gameName);
        nCommand++;
        break;
      }
      else
      {
        g = searchGame(gameHashTable[M], gameName);
        if (g->id != 0)
        {
          gameHashTable[M] = deleteGame(gameHashTable[M], g);
          nGames--;
        }
        else
        {
          printf("%d Jogo inexistente.", nCommand);
          free(gameName);
          nCommand++;
          break;
        }

      }

        free(gameName);
        nCommand++;
        break;

      case 's':
        gameName = malloc(1023 * (sizeof(char)));
        for (int gameName_index = 0; gameName_index < 10; gameName_index++)
      {
        gameName[gameName_index] = new_sym_var(sizeof(char) * 8);
      }

        gameName[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(int) * 8);
        score2 = new_sym_var(sizeof(int) * 8);
        M = hashGame(gameName);
        if (gameHashTable[M] == 0)
      {
        printf("%d Jogo inexistente.", nCommand);
        free(gameName);
        nCommand++;
        break;
      }
      else
      {
        g = searchGame(gameHashTable[M], gameName);
        if (g->id != 0)
        {
          changeScore(g, score1, score2);
        }
        else
        {
          printf("%d Jogo inexistente.", nCommand);
          free(gameName);
          nCommand++;
          break;
        }

      }

        free(gameName);
        nCommand++;
        break;

      case 'A':
        team = malloc(1023 * (sizeof(char)));
        for (int team_index = 0; team_index < 10; team_index++)
      {
        team[team_index] = new_sym_var(sizeof(char) * 8);
      }

        team[10 - 1] = '\0';
        M = hashTeam(team);
        if (teamHashTable[M] != 0)
      {
        t = searchTeam(teamHashTable[M], team);
        if (t->exists == 0)
        {
          teamHashTable[M] = addTeam(teamHashTable[M], team);
        }
        else
        {
          printf("%d Equipa existente.\n", nCommand);
          free(team);
          nCommand++;
          break;
        }

      }
      else
      {
        teamHashTable[M] = addTeam(0, team);
      }

        free(team);
        nCommand++;
        break;

      case 'P':
        team = malloc(1023 * (sizeof(char)));
        for (int team_index = 0; team_index < 10; team_index++)
      {
        team[team_index] = new_sym_var(sizeof(char) * 8);
      }

        team[10 - 1] = '\0';
        M = hashTeam(team);
        if (teamHashTable[M] != 0)
      {
        t = searchTeam(teamHashTable[M], team);
      }
      else
      {
        printf("%d Equipa inexistente.\n", nCommand);
        free(team);
        nCommand++;
        break;
      }

        if (t->exists == 1)
      {
        printf("%d %s %d\n", nCommand, t->name, t->wins);
      }
      else
      {
        printf("%d Equipa inexistente.", nCommand);
      }

        free(team);
        nCommand++;
        break;

      default:
        return 0;

    }

  }
  while ((*command) != 'x');
  return 0;
}

