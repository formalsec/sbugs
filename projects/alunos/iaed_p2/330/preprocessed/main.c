#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "funcoes.h"


int main()
{
  char comando = '0';
  Equipa *cabeca_equipas = 0;
  Hequipas *TabEquipas = init_hashE();
  Cabeca_cauda *extremos_lista_jogos = malloc(sizeof(Cabeca_cauda));
  Hjogos *TabJogos = init_hashJ();
  int *NL = malloc(sizeof(int));
  extremos_lista_jogos->cabeca = 0;
  extremos_lista_jogos->cauda = 0;
  *NL = 1;
  while (comando != 'x')
  {
    comando = new_sym_var(sizeof(char) * 8);
    if (comando == 'a')
    {
      a(TabEquipas, TabJogos, extremos_lista_jogos, NL);
    }
    else
    {
      
    }

    if (comando == 'A')
    {
      cabeca_equipas = A(TabEquipas, cabeca_equipas, NL);
    }
    else
    {
      
    }

    if (comando == 'l')
    {
      l(NL, extremos_lista_jogos);
    }
    else
    {
      
    }

    if (comando == 'p')
    {
      p(TabJogos, NL);
    }
    else
    {
      
    }

    if (comando == 'P')
    {
      P(TabEquipas, NL);
    }
    else
    {
      
    }

    if (comando == 'r')
    {
      r(NL, TabJogos, TabEquipas, extremos_lista_jogos);
    }
    else
    {
      
    }

    if (comando == 's')
    {
      s(TabEquipas, TabJogos, NL);
    }
    else
    {
      
    }

    if (comando == 'g')
    {
      g(NL, cabeca_equipas);
    }
    else
    {
      
    }

  }

  free_Hequipas(TabEquipas);
  free_listaE(cabeca_equipas);
  free_Hjogos(TabJogos);
  free_listaJ(extremos_lista_jogos);
  free(NL);
  return 0;
}
