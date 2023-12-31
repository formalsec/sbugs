#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "main.h"


int main()
{
  char comando;
  int linha = 1;
  linkeq *hash_equipas = HashEquipas_inic();
  item_hash_jg *hash_jogos = HashJogos_inic();
  lista lista_jogos = cria_lista_jogos();
  while ((comando = getchar()) != 'x')
  {
    switch (comando)
    {
      case 'a':
        adiciona_jogo(hash_jogos, hash_equipas, lista_jogos, linha);
        linha++;
        break;

      case 'A':
        adiciona_equipa(hash_equipas, linha);
        linha++;
        break;

      case 'l':
        lista_todos_jogos(lista_jogos, linha);
        linha++;
        break;

      case 'p':
        procura_jogo(hash_jogos, linha);
        linha++;
        break;

      case 'P':
        procura_equipa(hash_equipas, linha);
        linha++;
        break;

      case 'r':
        apaga_jogo(hash_jogos, hash_equipas, lista_jogos, linha);
        linha++;
        break;

      case 's':
        altera_score(hash_jogos, hash_equipas, linha);
        linha++;
        break;

      case 'g':
        lista_melhores_equipas(hash_equipas, linha);
        linha++;
        break;

      default:
        break;

    }

  }

  free_hashequipas(hash_equipas);
  free_listajogos(lista_jogos);
  free_hash_jogos(hash_jogos);
  return 0;
}

