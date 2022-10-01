/*File generated by PreProcessor.py*/


#include "funcoes.h"
#include <stdio.h>


int main()
{
  char op;
  unsigned int NL = 1;
  Jogos jogos;
  Equipas equipas;
  jogos = init_jogos();
  equipas = init_equipas();
  while ((op = getchar()) != 'x')
  {
    switch (op)
    {
      case 'a':
        getchar();
        NL = a(NL, jogos, equipas);
        break;

      case 'A':
        getchar();
        NL = A(NL, equipas);
        break;

      case 'l':
        getchar();
        NL = l(NL, jogos);
        break;

      case 'p':
        getchar();
        NL = p(NL, jogos);
        break;

      case 'P':
        getchar();
        NL = P(NL, equipas);
        break;

      case 'r':
        getchar();
        NL = r(NL, jogos);
        break;

      case 's':
        getchar();
        NL = s(NL, jogos);
        break;

      case 'g':
        getchar();
        NL = g(NL, equipas);
        break;

    }

  }

  destroi_jogos(jogos);
  destroi_equipas(equipas);
  return 0;
}
