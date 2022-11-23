#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "COMANDOS.h"
#define M 997
int main()
{
  int comando;
  int nl = 1; /* contador para as linhas de input */
  int contadorequipas = 0; /* contador para o numero de equipas presentes */
  linkJ headsJ[M];
  linkE headsE[M];
  lista *lst;

  /* inicializar as estruturas de dados */

  lst = cria_lista();
  iniciaJ(headsJ);
  iniciaE(headsE);



  while ((comando = getchar()) != 'x')
  { 
    switch (comando) 
    {
      case 'a':
        novo_jogo(nl, headsJ, headsE, lst);
        nl++;
        break;
      case 'l':
        lista_jogos(nl, lst);
        nl++;
        break;
      case 'p':
        procura_jogo(nl, headsJ);
        nl++;
        break;
      case 'r':
        apagar_jogo(nl, headsJ, lst, headsE);
        nl++;
        break;
      case 's':
        altera_score(nl, headsJ, headsE);
        nl++;
        break;
      case 'A':
        nova_equipa(nl, &contadorequipas, headsE);
        nl++;
        break;
      case 'P':
        procurar_equipa(nl, headsE);
        nl++;
        break;
      case 'g':
        lista_equipas(nl, &contadorequipas, headsE);
        nl++;
        break;
      default:
      	break;
    }
  }
  sair(headsE, headsJ, lst);
  return 0;
}