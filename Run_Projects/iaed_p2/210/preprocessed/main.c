/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"


int main()
{
  char c;
  char string1[1023];
  char string2[1023];
  char string3[1023];
  unsigned int score1;
  unsigned int score2;
  int NL = 1;
  init();
  while (1)
  {
    switch (c = getchar())
    {
      case 'a':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        for (int string2_index = 0; string2_index < 10; string2_index++)
      {
        string2[string2_index] = new_sym_var(sizeof(char) * 8);
      }

        string2[10 - 1] = '\0';
        for (int string3_index = 0; string3_index < 10; string3_index++)
      {
        string3[string3_index] = new_sym_var(sizeof(char) * 8);
      }

        string3[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(unsigned int) * 8);
        score2 = new_sym_var(sizeof(unsigned int) * 8);
        add_game(string1, NL, string2, string3, score1, score2);
        NL++;
        break;

      case 'A':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        add_team(string1, NL);
        NL++;
        break;

      case 'l':
        print_games(NL);
        NL++;
        break;

      case 'p':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        printf("%d ", NL);
        search_game(string1);
        NL++;
        break;

      case 'P':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        printf("%d ", NL);
        search_team(string1);
        NL++;
        break;

      case 'r':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        delete_game(string1, NL);
        NL++;
        break;

      case 's':
        for (int string1_index = 0; string1_index < 10; string1_index++)
      {
        string1[string1_index] = new_sym_var(sizeof(char) * 8);
      }

        string1[10 - 1] = '\0';
        score1 = new_sym_var(sizeof(unsigned int) * 8);
        score2 = new_sym_var(sizeof(unsigned int) * 8);
        change_score(string1, score1, score2, NL);
        NL++;
        break;

      case 'g':
        print_teams(NL);
        NL++;
        break;

      case 'x':
        free_all();
        return 0;

      default:
        printf("Erro: Comando desconhecido\n");

    }

    getchar();
  }

  return 1;
}

