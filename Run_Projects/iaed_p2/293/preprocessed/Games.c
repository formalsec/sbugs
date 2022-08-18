/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Games.h"
#include "list.h"
#include "hashtabel.h"


void Solve(FILE *fpIn, FILE *fpOut)
{
  char *valor = "";
  char *nome = 0;
  char *team1 = 0;
  char *team2 = 0;
  int NL = 1;
  char *string = (char *) malloc((sizeof(char)) * 1023);
  char *s1 = 0;
  char *s2 = 0;
  Game *headG = 0;
  Team *headT = 0;
  int score1;
  int score2;
  while (!EOF)
  {
    for (int string_index = 0; string_index < 10; string_index++)
    {
      string[string_index] = new_sym_var(sizeof(char) * 8);
    }

    string[10 - 1] = '\0';
    switch (string[0])
    {
      case 'a':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
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
        for (int s1_index = 0; s1_index < 10; s1_index++)
      {
        s1[s1_index] = new_sym_var(sizeof(char) * 8);
      }

        s1[10 - 1] = '\0';
        for (int s2_index = 0; s2_index < 10; s2_index++)
      {
        s2[s2_index] = new_sym_var(sizeof(char) * 8);
      }

        s2[10 - 1] = '\0';
        score1 = atoi(s1);
        score2 = atoi(s2);
        Funcaocaso_a(fpOut, headG, headT, nome, team1, team2, score1, score2, NL);
        break;

      case 'l':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        Funcaocaso_l(headG, fpOut, NL);
        break;

      case 'p':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        Funcaocaso_p(headG, fpOut, nome, NL);
        break;

      case 'r':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        Funcaocaso_r(nome, headG, fpOut, NL);
        break;

      case 's':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        for (int s1_index = 0; s1_index < 10; s1_index++)
      {
        s1[s1_index] = new_sym_var(sizeof(char) * 8);
      }

        s1[10 - 1] = '\0';
        for (int s2_index = 0; s2_index < 10; s2_index++)
      {
        s2[s2_index] = new_sym_var(sizeof(char) * 8);
      }

        s2[10 - 1] = '\0';
        score1 = atoi(s1);
        score2 = atoi(s2);
        Funcaocaso_s(headT, nome, score1, score2, headG, fpOut, NL);
        break;

      case 'A':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        Funcaocaso_A(nome, fpOut, headT, NL);
        break;

      case 'P':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        for (int nome_index = 0; nome_index < 10; nome_index++)
      {
        nome[nome_index] = new_sym_var(sizeof(char) * 8);
      }

        nome[10 - 1] = '\0';
        Funcaocaso_P(nome, headT, fpOut, NL);
        break;

      case 'g':
        for (int valor_index = 0; valor_index < 10; valor_index++)
      {
        valor[valor_index] = new_sym_var(sizeof(char) * 8);
      }

        valor[10 - 1] = '\0';
        Funcaocaso_g(headT, fpOut, NL);
        break;

    }

    NL += 1;
  }

  free(string);
  free(nome);
  free(team1);
  free(team2);
  FreeAll(headG);
  FreeT(headT);
}

void Funcaocaso_a(FILE *fpOut, Game *headG, Team *headT, char *nome, char *team1, char *team2, int score1, int score2, int NL)
{
  Game *aux1 = 0;
  Game *newG = 0;
  Team *aux = 0;
  if (headT == 0)
  {
    {
      fprintf(fpOut, "%d Equipa inexistente.\n", NL);
      exit(0);
    }
  }
  else
  {
    {
      for (aux = headT; GetNext_team(aux) != 0; aux = GetNext_team(aux))
      {
        if ((strcmp(team1, Getteam_name(aux)) == 0) && (strcmp(team2, Getteam_name(aux)) == 0))
        {
          {
            break;
          }
        }
        else
        {
          
        }

      }

      for (aux1 = headG; GetNext_game(aux1) != 0; aux1 = GetNext_game(aux1))
      {
        if (strcmp(nome, GetName(aux1)) == 0)
        {
          {
            fprintf(fpOut, "%d Jogo existente.\n", NL);
            exit(0);
          }
        }
        else
        {
          
        }

      }

      newG = InitGameNode();
      if (newG == 0)
      {
        {
          printf("Erro alocacao novo node\n.");
          exit(0);
        }
      }
      else
      {
        
      }

      headG = SetGameNode(newG, headG, nome, team1, team2, score1, score2, NL);
      Determinewins(headT, newG);
      fprintf(fpOut, "\n");
    }
  }

  free(aux);
  free(aux1);
}

void Funcaocaso_l(Game *headG, FILE *fpOut, int NL)
{
  Game *aux = 0;
  Game *aux1 = 0;
  Game *tail = 0;
  if (headG == 0)
  {
    {
      fprintf(fpOut, "\n");
      exit(0);
    }
  }
  else
  {
    {
      for (aux = headG; GetNext_game(aux) != 0; aux = GetNext_game(aux))
      {
        tail = aux;
        tail = GetPrev_game(aux);
      }

      for (aux1 = tail; GetPrev_game(aux1) != 0; aux1 = GetPrev_game(aux1))
        fprintf(fpOut, "%d %s %s %s %d %d\n", NL, GetName(aux1), GetTeam1(aux1), GetTeam2(aux), Getscore1(aux1), Getscore2(aux1));

    }
  }

  free(tail);
  free(aux);
  free(aux1);
}

void Funcaocaso_p(Game *headG, FILE *fpOut, char *nome, int NL)
{
  Game *aux = 0;
  for (aux = headG; GetNext_game(aux) != 0; aux = GetNext_game(aux))
  {
    if (strcmp(GetName(aux), nome) == 0)
    {
      fprintf(fpOut, "%c %s %s %s %d %d\n", Getline(aux), GetName(aux), GetTeam1(aux), GetTeam2(aux), Getscore1(aux), Getscore2(aux));
    }
    else
    {
      fprintf(fpOut, "%d Jogo inexistente.\n", NL);
    }

  }

  free(aux);
}

void Funcaocaso_r(char *nome, Game *headG, FILE *fpOut, int NL)
{
  Game *aux = 0;
  if (headG == 0)
  {
    exit(0);
  }
  else
  {
    {
      for (aux = headG; GetNext_game(aux) != 0; aux = GetNext_game(aux))
      {
        if (strcmp(GetName(aux), nome) == 0)
        {
          DeleteGameNode(aux, headG);
        }
        else
        {
          {
            fprintf(fpOut, "%d Jogo Inexistente", NL);
            break;
          }
        }

      }

    }
  }

  free(aux);
}

void Funcaocaso_s(Team *headT, char *nome, int score1, int score2, Game *headG, FILE *fpOut, int NL)
{
  Game *aux = 0;
  for (aux = headG; GetNext_game(aux) != 0; aux = GetNext_game(aux))
  {
    if (strcmp(GetName(aux), nome) == 0)
    {
      {
        aux = muda_score(score1, score2, aux);
        Determinewins(headT, aux);
        free(aux);
        exit(0);
      }
    }
    else
    {
      
    }

  }

  fprintf(fpOut, "%d Jogo inexistente", NL);
  free(aux);
}

void Funcaocaso_A(char *nome, FILE *fpOut, Team *headT, int NL)
{
  Team *aux = 0;
  Team *new = 0;
  if (headT == 0)
  {
    {
      headT = SetTeamNode(new, headT, nome);
      if (headT == 0)
      {
        exit(0);
      }
      else
      {
        
      }

    }
  }
  else
  {
    {
      for (aux = headT; GetNext_team(aux) != 0; aux = GetNext_team(aux))
      {
        if (strcmp(Getteam_name(aux), nome) == 0)
        {
          {
            fprintf(fpOut, "%d Equipa existente.\n", NL);
            exit(0);
          }
        }
        else
        {
          
        }

      }

      new = InitTeamNode();
      if (new == 0)
      {
        exit(0);
      }
      else
      {
        
      }

      headT = SetTeamNode(new, headT, nome);
    }
  }

  free(aux);
}

void Funcaocaso_P(char *nome, Team *headT, FILE *fpOut, int NL)
{
  Team *aux = 0;
  for (aux = headT; GetNext_team(aux) != 0; aux = GetNext_team(aux))
  {
    if (strcmp(Getteam_name(aux), nome) == 0)
    {
      {
        fprintf(fpOut, "%d %s %d\n", NL, nome, GetWin(aux));
        free(aux);
        exit(0);
      }
    }
    else
    {
      
    }

  }

  fprintf(fpOut, "%d Equipa inexistente.\n", NL);
}

void Funcaocaso_g(Team *headT, FILE *fpOut, int NL)
{
  Team *aux = 0;
  if (headT == 0)
  {
    exit(0);
  }
  else
  {
    
  }

  fprintf(fpOut, "%d Melhores %d\n", NL, GetWin(headT));
  for (aux = headT; GetWin(aux) == GetWin(GetNext_team(aux)); aux = GetNext_team(aux))
  {
    fprintf(fpOut, "%d * %s\n", NL, Getteam_name(aux));
  }

  free(aux);
}

