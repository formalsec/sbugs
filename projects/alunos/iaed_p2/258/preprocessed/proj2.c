#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "jogo.h"


int main()
{
  int c;
  int n;
  int num_comandos = 1;
  struct TodosJogos jogos;
  struct TodasEquipas equipas;
  for (n = 0; n < 1000; n++)
  {
    jogos.elementos[n] = 0;
  }

  for (n = 0; n < 1000; n++)
  {
    equipas.elementos[n] = 0;
  }

  equipas.num_equipas = 0;
  equipas.vetor = 0;
  jogos.num_jogos = 0;
  jogos.vetor = 0;
  while (1)
  {
    c = getchar();
    if (c == EOF)
    {
      return 0;
    }
    else
    {
      
    }

    if ((c == '\n') || (c == ' '))
    {
      continue;
    }
    else
    {
      
    }

    switch (c)
    {
      case 'a':
        adicionajogo(&jogos, &equipas, num_comandos);
        break;

      case 'A':
        adicionaequipa(&equipas, num_comandos);
        break;

      case 'l':
        listajogo(&jogos, num_comandos);
        break;

      case 'p':
        procurajogo(&jogos, num_comandos);
        break;

      case 'P':
        procuraequipa(&equipas, num_comandos);
        break;

      case 'r':
        apagajogo(&jogos, num_comandos);
        break;

      case 's':
        alterascore(&jogos, num_comandos);
        break;

      case 'g':
        encontravitoriosos(&equipas, num_comandos);
        break;

      case 'x':
        return 0;

    }

    num_comandos += 1;
  }

  for (n = 0; n < jogos.num_jogos; n++)
  {
    if (jogos.vetor[n] == 0)
    {
      continue;
    }
    else
    {
      
    }

    free(jogos.vetor[n]->nome);
    free(jogos.vetor[n]);
  }

  free(jogos.vetor);
  for (n = 0; n < equipas.num_equipas; n++)
  {
    if (equipas.vetor[n] == 0)
    {
      continue;
    }
    else
    {
      
    }

    free(equipas.vetor[n]->nome);
    free(equipas.vetor[n]);
  }

  free(equipas.vetor);
  return 0;
}

