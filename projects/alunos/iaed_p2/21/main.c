#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FUNCTIONS.h"


int main(){
  int counter = 0;
  int c;
  /*Inicializacao das estruturas que guardam as diferentes informacoes do sistema*/
  TlistInit();
  MlistInit();
  teamInit();
  matchInit();
  /*obtencao do input introduzido pelo utilizador e comparacao com os diferentes
  comandos*/
  while((c=getchar()) != EOF){
    counter++;
    switch(c){
      case 'a': fa(counter); break;
      case 'A': fA(counter); break;
      case 'l': fl(counter); break;
      case 'p': fp(counter); break;
      case 'P': fP(counter); break;
      case 'r': fr(counter); break;
      case 's': fs(counter); break;
      case 'g': fg(counter); break;
      case 'x': fx(); break;
    }
    if (c == 'x'){
      /*caso o comando seja x, sair do ciclo while*/
      break;
    }
  }
  return 0;
}
