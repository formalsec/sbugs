#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj2_aux.h"
#include "proj2_comandos.h"


int main()
{
  char entrada[4000];
  char *comando;
  char *atr1;
  char *atr2;
  char *atr3;
  char *atr4;
  char *atr5;
  int NL = 0;
  Lista_jogos_equipas *lje;
  lje = cria_lista();
  while (1)
  {
    NL += 1;
    fgets(entrada, 4000, stdin);
    comando = strtok(entrada, " ");
    switch (*comando)
    {
      case 'a':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, ":");
        atr3 = strtok(0, ":");
        atr4 = strtok(0, ":");
        atr5 = strtok(0, "\n");
        a(NL, atr1, atr2, atr3, atr4, atr5, lje);
        break;

      case 'A':
        atr1 = strtok(0, "\n");
        A(NL, atr1, lje);
        break;

      case 'l':
        l(NL, lje);
        break;

      case 'p':
        atr1 = strtok(0, "\n");
        p(NL, atr1, lje);
        break;

      case 'P':
        atr1 = strtok(0, "\n");
        P(NL, atr1, lje);
        break;

      case 'r':
        atr1 = strtok(0, "\n");
        r(NL, atr1, lje);
        break;

      case 's':
        atr1 = strtok(0, ":");
        atr2 = strtok(0, ":");
        atr3 = strtok(0, "\n");
        s(NL, atr1, atr2, atr3, lje);
        break;

      case 'g':
        g(NL, lje);
        break;

      case 'x':
        free_lista(lje);
        exit(0);

    }

  }

  return 0;
}

