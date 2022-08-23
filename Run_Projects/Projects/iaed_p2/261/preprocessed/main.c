/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGO.h"  /* Ficheiro que contem as funcoes que gerem os jogos */


int main()
{
  char buffer[1024];
  char funcao;
  int running = 1;
  int n = 1;
  list *lista;
  equipaHash **equipaTable;
  lista = mk_list();
  equipaTable = criaEquipaHash();
  while (running == 1)
  {
    funcao = getchar();
    switch (funcao)
    {
      case 'a':
        getchar();
        fgets(buffer, 1024, stdin);
        lista = adicionaJogo(lista, equipaTable, buffer, n);
        n += 1;
        break;

      case 'A':
        getchar();
        fgets(buffer, 1024, stdin);
        adicionaEquipa(equipaTable, buffer, n);
        n += 1;
        break;

      case 'l':
        listaJogos(lista, n);
        n += 1;
        break;

      case 'p':
        getchar();
        fgets(buffer, 1024, stdin);
        procuraJogo(lista, buffer, n);
        n += 1;
        break;

      case 'P':
        getchar();
        fgets(buffer, 1024, stdin);
        procuraEquipa(equipaTable, buffer, n);
        n += 1;
        break;

      case 'r':
        getchar();
        fgets(buffer, 1024, stdin);
        lista = apagarJogo(lista, equipaTable, buffer, n);
        n += 1;
        break;

      case 's':
        getchar();
        fgets(buffer, 1024, stdin);
        lista = alteraResultado(lista, equipaTable, buffer, n);
        n += 1;
        break;

      case 'g':
        melhoresEquipas(equipaTable, n);
        n += 1;
        break;

      case 'x':
        running = 0;
        freeLista(lista);
        freeEquipaHash(equipaTable);
        break;

    }

  }

  return 0;
}

