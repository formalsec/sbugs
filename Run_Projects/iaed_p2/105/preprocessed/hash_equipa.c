/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_equipa.h"
#include "hash_table.h"


void inserir_tabela_equipa(equipa *j, equipa *tabela_hash_equipa[1000])
{
  int index = funcao_tabela(j->nome);
  j->next = tabela_hash_equipa[index];
  tabela_hash_equipa[index] = j;
}

equipa *procura_tabela_equipa(char *nome, equipa *tabela_hash_equipa[1000])
{
  int index = funcao_tabela(nome);
  equipa *aux = tabela_hash_equipa[index];
  while ((aux != 0) && (strncmp(aux->nome, nome, 1024) != 0))
  {
    aux = aux->next;
  }

  return aux;
}

void apaga_mem_equipa(equipa *tabela_hash_equipa[1000])
{
  int i;
  for (i = 0; i < 1000; i++)
  {
    equipa *el = tabela_hash_equipa[i];
    while (el != 0)
    {
      equipa *apaga = el;
      free(el->nome);
      el = el->next;
      free(apaga);
    }

  }

}

