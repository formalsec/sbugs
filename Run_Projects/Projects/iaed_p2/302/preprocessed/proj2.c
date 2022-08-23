/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main()
{
  char comando;
  int cont = 1;
  int run = 1;
  hash_table_jogo *syst_jogos = mk_hash_table_jg(1237);
  hash_table_equipa *syst_eq = mk_hash_table_eq(1237);
  node_jogo *head_lista_jogos = 0;
  while (run)
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        head_lista_jogos = func_a(cont, syst_jogos, syst_eq, head_lista_jogos);
        break;

      case 'l':
        func_l(cont, head_lista_jogos);
        break;

      case 'p':
        func_p(cont, syst_jogos);
        break;

      case 'r':
        head_lista_jogos = func_r(cont, syst_jogos, syst_eq, head_lista_jogos);
        break;

      case 's':
        func_s(cont, syst_jogos, syst_eq);
        break;

      case 'A':
        func_A(cont, syst_eq);
        break;

      case 'P':
        func_P(cont, syst_eq);
        break;

      case 'g':
        func_g(cont, syst_eq);
        break;

      case 'x':
        run = 0;
        break;

      default:
        cont++;
        continue;

    }

  }

  free_hashtable_eq(syst_eq);
  free_hashtable_jg(syst_jogos);
  return 0;
}

