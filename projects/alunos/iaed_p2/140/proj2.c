#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main.h"

int main() {
  /* variavel do numero de linha e de ordem de insercao */
  ulong linha = 1, ordem = 0;
  /* variavel do comando */
  char c;
  /* hash das equipas */
  link* hashEquipas = EhashInit();
  /* hash dos jogos */
  jlink* hashJogos = JhashInit();

  /* ciclo de comandos, termina com um x */
  do {
    switch (c = getchar()) {
      case 'a':
        criaJogo(hashJogos,hashEquipas, linha, &ordem);
        linha++;
        break;
      case 'A':
        criaEquipa(hashEquipas, linha);
        linha++;
        break;
      case 'l':
        listaJogos(hashJogos, linha);
        linha++;
        break;
      case 'p':
        escreveJogo(hashJogos, linha);
        linha++;
        break;
      case 'P':
        escreveEquipa(hashEquipas, linha);
        linha++;
        break;
      case 'r':
        delJogo(hashJogos, linha);
        linha++;
        break;
      case 's':
        alteraScore(hashJogos, linha);
        linha++;
        break;
      case 'g':
        listaMelhoresEquipas(hashEquipas, linha);
        linha++;
        break;
      default:
        break;
    }
  } while(c != 'x');

  /* free da memoria de ambas as hash */
  EfreeHash(hashEquipas);
  JfreeHash(hashJogos);

  return 0;
}
