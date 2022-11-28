#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "projeto.h"


int hash(char *c, int size)
{
  int indice;
  int a = 31415;
  int b = 27183;
  for (indice = 0; strcmp(c, "\0") != 0; c++, a = (a * b) % (size - 1))
  {
    indice = ((a * indice) + (*c)) % size;
  }

  return indice;
}

jogo *inicia_hash_jogos(jogo *table_jogos)
{
  int i;
  table_jogos = (jogo *) malloc(997 * (sizeof(struct str_jogo)));
  for (i = 0; i < 997; i++)
  {
    table_jogos[i] = 0;
  }

  return table_jogos;
}

equipa *inicia_hash_equipas(equipa *table_equipas)
{
  int i;
  table_equipas = (equipa *) malloc(593 * (sizeof(struct str_equipa)));
  for (i = 0; i < 593; i++)
  {
    table_equipas[i] = 0;
  }

  return table_equipas;
}

void free_final(equipa *table_equipas, jogo *table_jogos)
{
  int i;
  jogo aux_jogo;
  equipa aux_equipa;
  for (i = 0; i < 997; i++)
  {
    for (; table_jogos[i] != 0; table_jogos[i] = aux_jogo)
    {
      aux_jogo = table_jogos[i]->next;
      free(table_jogos[i]->nome);
      free(table_jogos[i]->score1);
      free(table_jogos[i]->score2);
      free(table_jogos[i]);
    }

  }

  free(table_jogos);
  for (i = 0; i < 593; i++)
  {
    for (; table_equipas[i] != 0; table_equipas[i] = aux_equipa)
    {
      aux_equipa = table_equipas[i]->next;
      free(table_equipas[i]->nome);
      free(table_equipas[i]->jogos_ganhos);
      free(table_equipas[i]);
    }

  }

  free(table_equipas);
}
