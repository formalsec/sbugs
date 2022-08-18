/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sistema.h"


void adiciona_jogo(Sistema *system, int cont_line)
{
  int score_1;
  int score_2;
  Jogo *new_game;
  Team *t1;
  Team *t2;
  char nome_jogo[1024];
  char equipa_1[1024];
  char equipa_2[1024];
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  for (int equipa_1_index = 0; equipa_1_index < 10; equipa_1_index++)
  {
    equipa_1[equipa_1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa_1[10 - 1] = '\0';
  for (int equipa_2_index = 0; equipa_2_index < 10; equipa_2_index++)
  {
    equipa_2[equipa_2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa_2[10 - 1] = '\0';
  score_1 = new_sym_var(sizeof(int) * 8);
  score_2 = new_sym_var(sizeof(int) * 8);
  t1 = encontra_t(system->tabela_teams, equipa_1);
  t2 = encontra_t(system->tabela_teams, equipa_2);
  if (encontra(system->tabela_jogos, nome_jogo) != 0)
  {
    {
      printf("%d Jogo existente.\n", cont_line);
    }
  }
  else
  {
    if (t1 == 0)
    {
      printf("%d Equipa inexistente.\n", cont_line);
    }
    else
    {
      if (t2 == 0)
      {
        printf("%d Equipa inexistente.\n", cont_line);
      }
      else
      {
        {
          new_game = cria_jogo(nome_jogo, equipa_1, equipa_2, score_1, score_2);
          if (score_1 > score_2)
          {
            {
              t1->numero_wins++;
              introduz_table(system->tabela_jogos, new_game);
              system->lista = add_last(system->lista, new_game);
            }
          }
          else
          {
            if (score_1 < score_2)
            {
              {
                t2->numero_wins++;
                introduz_table(system->tabela_jogos, new_game);
                system->lista = add_last(system->lista, new_game);
              }
            }
            else
            {
              {
                introduz_table(system->tabela_jogos, new_game);
                system->lista = add_last(system->lista, new_game);
              }
            }

          }

        }
      }

    }

  }

}

void adiciona_equipa(Sistema *system, int cont_line)
{
  Team *new_team;
  char name_team[1024];
  for (int name_team_index = 0; name_team_index < 10; name_team_index++)
  {
    name_team[name_team_index] = new_sym_var(sizeof(char) * 8);
  }

  name_team[10 - 1] = '\0';
  if (encontra_t(system->tabela_teams, name_team) != 0)
  {
    {
      printf("%d Equipa existente.\n", cont_line);
      return;
    }
  }
  else
  {
    {
      new_team = cria_team(name_team);
      introduz_table_t(system->tabela_teams, new_team);
      return;
    }
  }

}

void procura_equipa(Sistema *system, int cont_line)
{
  Team *t;
  char name_team[1024];
  for (int name_team_index = 0; name_team_index < 10; name_team_index++)
  {
    name_team[name_team_index] = new_sym_var(sizeof(char) * 8);
  }

  name_team[10 - 1] = '\0';
  t = encontra_t(system->tabela_teams, name_team);
  if (t == 0)
  {
    printf("%d Equipa inexistente.\n", cont_line);
  }
  else
  {
    printf("%d %s %d\n", cont_line, name_team, t->numero_wins);
  }

}

void lista_jogos(Sistema *system, int cont_line)
{
  print_lista(system->lista, cont_line);
}

void procura_jogo(Sistema *system, int cont_line)
{
  Jogo *j;
  char nome_jogo[1024];
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  j = encontra(system->tabela_jogos, nome_jogo);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", cont_line);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", cont_line, nome_jogo, j->equipa_1, j->equipa_2, j->score_1, j->score_2);
  }

}

void apaga_jogo(Sistema *system, int cont_line)
{
  Jogo *j;
  char nome_jogo[1024];
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  j = encontra(system->tabela_jogos, nome_jogo);
  if (j == 0)
  {
    printf("%d Jogo inexistente.\n", cont_line);
  }
  else
  {
    {
      if (j->score_1 > j->score_2)
      {
        {
          encontra_t(system->tabela_teams, j->equipa_1)->numero_wins--;
          system->lista = Modifica_next_jogo(system->lista, j->nome_jogo);
          Remove_table(system->tabela_jogos, j);
        }
      }
      else
      {
        if (j->score_2 > j->score_1)
        {
          {
            encontra_t(system->tabela_teams, j->equipa_2)->numero_wins--;
            system->lista = Modifica_next_jogo(system->lista, j->nome_jogo);
            Remove_table(system->tabela_jogos, j);
          }
        }
        else
        {
          {
            system->lista = Modifica_next_jogo(system->lista, j->nome_jogo);
            Remove_table(system->tabela_jogos, j);
          }
        }

      }

    }
  }

}

void altera_jogo(Sistema *system, int cont_line)
{
  Jogo *aux;
  int score1;
  int score2;
  int estava_1;
  int estava_2;
  char nome_jogo[1024];
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  aux = encontra(system->tabela_jogos, nome_jogo);
  if (aux == 0)
  {
    printf("%d Jogo inexistente.\n", cont_line);
  }
  else
  {
    {
      estava_1 = aux->score_1;
      estava_2 = aux->score_2;
      aux->score_1 = score1;
      aux->score_2 = score2;
      if (score1 > score2)
      {
        {
          if (estava_2 > estava_1)
          {
            {
              encontra_t(system->tabela_teams, aux->equipa_1)->numero_wins++;
              encontra_t(system->tabela_teams, aux->equipa_2)->numero_wins--;
            }
          }
          else
          {
            if (estava_1 == estava_2)
            {
              encontra_t(system->tabela_teams, aux->equipa_1)->numero_wins++;
            }
            else
            {
              return;
            }

          }

        }
      }
      else
      {
        if (score1 == score2)
        {
          {
            if (estava_2 == estava_1)
            {
              return;
            }
            else
            {
              if (estava_1 > estava_2)
              {
                encontra_t(system->tabela_teams, aux->equipa_1)->numero_wins--;
              }
              else
              {
                encontra_t(system->tabela_teams, aux->equipa_2)->numero_wins--;
              }

            }

          }
        }
        else
        {
          {
            if (estava_1 > estava_2)
            {
              {
                encontra_t(system->tabela_teams, aux->equipa_1)->numero_wins--;
                encontra_t(system->tabela_teams, aux->equipa_2)->numero_wins++;
              }
            }
            else
            {
              if (estava_2 == estava_1)
              {
                encontra_t(system->tabela_teams, aux->equipa_2)->numero_wins++;
              }
              else
              {
                return;
              }

            }

          }
        }

      }

    }
  }

}

void lista_teams(Sistema *system, int Equipa_existe, int cont_line)
{
  int mais_wins;
  int i;
  int size;
  int l;
  char **pointer;
  char **pointer_1;
  if (Equipa_existe == 0)
  {
    return;
  }
  else
  {
    {
      pointer = malloc(((sizeof(char *)) * 1551) / 20);
      for (i = 0; i < (1551 / 20); i++)
        pointer[i] = malloc((sizeof(char)) * 1024);

      mais_wins = ve_maior(system->tabela_teams);
      size = teams_maiores(system->tabela_teams, pointer, mais_wins);
      pointer_1 = malloc((sizeof(char *)) * size);
      merge_principal(pointer, pointer_1, 0, size - 1);
      printf("%d Melhores %d\n", cont_line, mais_wins);
      for (l = 0; l < size; l++)
      {
        printf("%d * %s\n", cont_line, pointer[l]);
      }

      for (i = 0; i < (1551 / 20); i++)
        free(pointer[i]);

      free(pointer);
      free(pointer_1);
    }
  }

}

int main()
{
  int run = 1;
  int control;
  int cont_line = 0;
  int Equipa_existe = 0;
  Sistema *system;
  system = init_sistema();
  while (run)
  {
    control = getchar();
    switch (control)
    {
      case 'A':
        cont_line++;
        Equipa_existe = 1;
        adiciona_equipa(system, cont_line);
        break;

      case 'a':
        cont_line++;
        adiciona_jogo(system, cont_line);
        break;

      case 'P':
        cont_line++;
        procura_equipa(system, cont_line);
        break;

      case 'p':
        cont_line++;
        procura_jogo(system, cont_line);
        break;

      case 'l':
        cont_line++;
        lista_jogos(system, cont_line);
        break;

      case 'r':
        cont_line++;
        apaga_jogo(system, cont_line);
        break;

      case 's':
        cont_line++;
        altera_jogo(system, cont_line);
        break;

      case 'g':
        cont_line++;
        lista_teams(system, Equipa_existe, cont_line);
        break;

      case 'x':
        run = 0;
        break;

      default:
        run = 0;
        break;

    }

    getchar();
  }

  liberta_sistema(system);
  return 0;
}

