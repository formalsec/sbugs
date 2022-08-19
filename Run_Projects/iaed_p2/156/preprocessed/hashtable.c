/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "Projeto2.h"


unsigned int hash(char *nome, int tamanho)
{
  int indice;
  int a = 31415;
  int b = 27183;
  for (indice = 0; (*nome) != '\0'; nome++, a = (a * b) % (tamanho - 1))
  {
    indice = ((a * indice) + (*nome)) % tamanho;
  }

  return indice;
}

equipa_pont *inic_hash_equipa()
{
  equipa_pont *tabela_hash;
  int i;
  tabela_hash = (equipa_pont *) malloc(2131 * (sizeof(equipa_pont)));
  for (i = 0; i < 2131; i++)
  {
    tabela_hash[i] = 0;
  }

  return tabela_hash;
}

jogo_pont *inic_hash_jogo()
{
  jogo_pont *tabela_hash;
  int i;
  tabela_hash = (jogo_pont *) malloc(5501 * (sizeof(jogo_pont)));
  for (i = 0; i < 5501; i++)
  {
    tabela_hash[i] = 0;
  }

  return tabela_hash;
}

void limpa(equipa_pont *tabela_hash_equipas, jogo_pont *tabela_hash_jogos)
{
  int indice;
  equipa_pont e;
  equipa_pont aux1;
  jogo_pont i;
  jogo_pont aux2;
  for (indice = 0; indice < 2131; indice++)
  {
    for (e = tabela_hash_equipas[indice]; e != 0; e = aux1)
    {
      aux1 = e->prox_equipa;
      free(e->nome_equipa);
      free(e->vitorias);
      free(e);
    }

  }

  free(tabela_hash_equipas);
  for (indice = 0; indice < 5501; indice++)
  {
    for (i = tabela_hash_jogos[indice]; i != 0; i = aux2)
    {
      aux2 = i->prox_jogo;
      free(i->nome_jogo);
      free(i->golos1);
      free(i->golos2);
      free(i);
    }

  }

  free(tabela_hash_jogos);
}
