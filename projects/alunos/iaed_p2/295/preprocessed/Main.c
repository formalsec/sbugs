#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Comandos.h"
#include "Estruturas.h"


int main()
{
  lista_equipas *conj_equipas;
  lista_equipas_aux *conj_equipas_aux;
  lista_jogos *conj_jogos;
  lista_jogos_aux *conj_jogos_aux;
  int a = 0;
  int nl = 1;
  char c;
  conj_equipas = malloc(sizeof(lista_equipas));
  inicia_lista_equipas(conj_equipas);
  conj_equipas_aux = malloc(sizeof(lista_equipas_aux));
  inicia_lista_equipas_aux(conj_equipas_aux);
  conj_jogos = malloc(sizeof(lista_jogos));
  inicia_lista_jogos(conj_jogos);
  conj_jogos_aux = malloc(sizeof(lista_jogos_aux));
  inicia_lista_jogos_aux(conj_jogos_aux);
  c = getchar();
  while (1)
  {
    if (c == 'x')
    {
      free_geral(conj_equipas, conj_equipas_aux, conj_jogos, conj_jogos_aux);
      break;
    }
    else
    {
      
    }

    direciona(c, nl, conj_equipas, conj_equipas_aux, conj_jogos, conj_jogos_aux);
    a++;
    if ((a % 2) == 0)
    {
      nl++;
    }
    else
    {
      
    }

    c = getchar();
  }

  return 0;
}

