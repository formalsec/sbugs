/*File generated by PreProcessor.py*/


#include "TABELA_HASH_E.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  char comando = ' ';
  int contador = 0;
  listE *lista_equipas = cria_listE();
  listJogos *lista_jogos = cria_listJogos();
  Tabela_hash *tabela = cria_tabela_hash();
  Tabela_hash *calendario = cria_tabela_hash();
  while ((comando != EOF) && (comando != 'x'))
  {
    comando = new_sym_var(sizeof(char) * 8);
    switch (comando)
    {
      case 'a':
        adiciona_jogo(lista_jogos, calendario, tabela, ++contador);
        break;

      case 'l':
        lista_todos_jogos(lista_jogos, ++contador);
        break;

      case 'p':
        procura_jogo(calendario, ++contador);
        break;

      case 'r':
        apaga_jogo(calendario, tabela, lista_jogos, ++contador);
        break;

      case 's':
        altera_resultado(calendario, tabela, ++contador);
        break;

      case 'A':
        adiciona_equipa(lista_equipas, tabela, ++contador);
        break;

      case 'P':
        procura_equipa(tabela, ++contador);
        break;

      case 'g':
        vencedores(lista_equipas, ++contador);
        break;

    }

  }

  free_list(lista_equipas);
  free_listJ(lista_jogos);
  free_tabela_hash(tabela);
  free_tabela_hash(calendario);
  return 0;
}
