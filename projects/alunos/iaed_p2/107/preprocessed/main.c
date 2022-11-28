#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "interacao.h"


void inicializa(no_jogo_tabela *tabela_jogos[], no_equipa *tabela_equipas[], lista_jogos **fila_jogos)
{
  int i;
  for (i = 0; i < 1049; i++)
  {
    tabela_jogos[i] = 0;
    tabela_equipas[i] = 0;
  }

  *fila_jogos = (lista_jogos *) malloc(sizeof(lista_jogos));
  (*fila_jogos)->inicio = 0;
  (*fila_jogos)->fim = 0;
}

void liberta_memoria(no_equipa *tabela_equipas[], lista_jogos **fila_jogos)
{
  no_equipa *i;
  no_equipa *aux_equipa;
  no_jogos *k;
  no_jogos *aux_jogo;
  int j;
  for (j = 0; j < 1049; j++)
  {
    if (!tabela_equipas[j])
    {
      continue;
    }
    else
    {
      
    }

    for (i = tabela_equipas[j]; i; i = aux_equipa)
    {
      aux_equipa = i->proximo;
      free(i->equipa_do_no.nome);
      free(i);
    }

  }

  for (k = (*fila_jogos)->inicio; k; k = aux_jogo)
  {
    aux_jogo = k->proximo;
    free(k->jogo_n->jogo1.nome);
    free(k->jogo_n->jogo1.equipa1);
    free(k->jogo_n->jogo1.equipa2);
    free(k->jogo_n);
    free(k);
  }

  free(*fila_jogos);
}

int main()
{
  int c;
  int numero_equipas = 0;
  int linha = 1;
  lista_jogos *fila_jogos;
  no_jogo_tabela *tabela_jogos[1049];
  no_equipa *tabela_equipas[1049];
  inicializa(tabela_jogos, tabela_equipas, &fila_jogos);
  while ((c = getchar()) != 'x')
  {
    switch (c)
    {
      case 'a':
      {
        novo_jogo(tabela_equipas, &fila_jogos, tabela_jogos, linha);
        linha++;
        break;
      }

      case 'l':
      {
        lista_todos_jogos(fila_jogos, linha);
        linha++;
        break;
      }

      case 'p':
      {
        procura_jogo(tabela_jogos, linha);
        linha++;
        break;
      }

      case 'r':
      {
        apaga_jogo_alvo(tabela_equipas, tabela_jogos, &fila_jogos, linha);
        linha++;
        break;
      }

      case 's':
      {
        altera_score_jogo(tabela_jogos, tabela_equipas, linha);
        linha++;
        break;
      }

      case 'A':
      {
        adiciona_equipa_alvo(tabela_equipas, linha, &numero_equipas);
        linha++;
        break;
      }

      case 'P':
      {
        procura_equipa(tabela_equipas, linha);
        linha++;
        break;
      }

      case 'g':
      {
        lista_mais_vitorias(tabela_equipas, linha, numero_equipas);
        linha++;
        break;
      }

    }

  }

  liberta_memoria(tabela_equipas, &fila_jogos);
  return 0;
}
