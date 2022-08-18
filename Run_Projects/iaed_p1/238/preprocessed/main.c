/*File generated by PreProcessor.py*/


#include "functions.h"


int main()
{
  char command;
  char line[5][100];
  struct Product prodList[10000];
  struct Encomenda encomendas[500];
  int idp = 0;
  int ide = -1;
  while (1)
  {
    command = new_sym_var(sizeof(char) * 8);
    switch (command)
    {
      case 'a':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        idp = a(prodList, line, idp);
        break;

      case 'q':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        q(prodList, line, idp);
        break;

      case 'N':
        printf("Nova encomenda %i.\n", ++ide);
        encomendas[ide].prodTotal = 0;
        break;

      case 'A':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        A(prodList, line, idp, ide, encomendas);
        break;

      case 'r':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        r(prodList, line, idp);
        break;

      case 'R':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        R(line, idp, ide, encomendas, prodList);
        break;

      case 'C':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        C(ide, encomendas, line, prodList);
        break;

      case 'p':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        p(prodList, line, idp);
        break;

      case 'E':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        E(ide, encomendas, line, prodList, idp);
        break;

      case 'm':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        m(ide, encomendas, line, idp);
        break;

      case 'l':
        l(prodList, idp);
        break;

      case 'L':
        for (int line_index = 0; line_index < 10; line_index++)
      {
        line[0][line_index] = new_sym_var(sizeof(char) * 8);
      }

        line[0][10 - 1] = '\0';
        L(ide, encomendas, line, prodList);
        break;

      case 'x':
        return 0;

    }

  }

}

