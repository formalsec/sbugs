/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"
#include "equipa.h"


int main()
{
  int maxE = 19913;
  int maxJ = 19913;
  int nComandos = 1;
  int nEquipas = 0;
  int nJogos = 0;
  pEquipa *tabE = 0;
  pJogo *tabJ = 0;
  DLinkedList listJ = 0;
  char comando;
  tabE = EQUIPAinit(maxE, tabE);
  tabJ = JOGOinit(maxJ, tabJ);
  listJ = JOGOlist_init();
  do
  {
    comando = getchar();
    switch (comando)
    {
      case 'a':
        adicionaNovoJogo(tabJ, tabE, maxJ, maxE, nComandos, listJ);
        nJogos++;
        if (nJogos > (maxJ / 2))
      {
        maxJ = maxJ * 2;
        tabJ = JOGOexpand(tabJ, maxJ);
      }
      else
      {
        
      }

        nComandos++;
        break;

      case 'A':
        adicionaNovaEquipa(tabE, maxE, nComandos);
        nEquipas++;
        if (nEquipas > (maxE / 2))
      {
        maxE = maxE * 2;
        tabE = EQUIPAexpand(tabE, maxE);
      }
      else
      {
        
      }

        nComandos++;
        break;

      case 'l':
        listaJogosPelaOrdemIntroduzidos(listJ, nComandos);
        nComandos++;
        break;

      case 'p':
        procuraUmJogo(tabJ, maxJ, nComandos);
        nComandos++;
        break;

      case 'P':
        procuraUmaEquipa(tabE, maxE, nComandos);
        nComandos++;
        break;

      case 'r':
        apagaUmJogo(tabJ, tabE, maxJ, maxE, listJ, nComandos);
        nJogos--;
        nComandos++;
        break;

      case 's':
        alteraScoreDeUmJogo(tabJ, tabE, maxJ, maxE, nComandos);
        nComandos++;
        break;

      case 'g':
        encontraAsEquipasVencedores(tabE, maxE, nComandos);
        nComandos++;
        break;

    }

  }
  while (comando != 'x');
  sair(tabE, tabJ, listJ, maxE, maxJ);
  return 0;
}
