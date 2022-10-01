/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


int main()
{
  char caracter;
  int NL = 0;
  jogos *lista_jogos = mk_list_jg();
  node **table = get_hashtables();
  e_node **equipas = get_hashtable_equipa();
  while ((caracter = getchar()) != 'x')
  {
    NL++;
    switch (caracter)
    {
      case 'a':
        a_comando(lista_jogos, table, equipas, NL);
        break;

      case 'l':
        l_comando(lista_jogos, NL);
        getchar();
        break;

      case 'p':
        p_comando(table, NL);
        break;

      case 'r':
        r_comando(lista_jogos, table, equipas, NL);
        break;

      case 's':
        s_comando(table, equipas, NL);
        break;

      case 'A':
        A_comando(equipas, NL);
        break;

      case 'P':
        P_comando(equipas, NL);
        break;

      case 'g':
        g_comando(equipas, NL);
        getchar();
        break;

    }

  }

  free_all(lista_jogos, table, equipas);
  return 0;
}
