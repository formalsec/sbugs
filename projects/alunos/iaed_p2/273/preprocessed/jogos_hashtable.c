#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <string.h>
#include <stdlib.h>
#include "equipas.h"
#include "equipas_hashtable.h" /* contem a funcao hash */
#include "jogos.h"
#include "jogos_hashtable.h"


jogo **inicia_hashtable_jogos(int *max, int *num_elem)
{
  jogo **nova_hastable;
  int i;
  int M = 2 * (*max);
  *num_elem = 0;
  nova_hastable = malloc(M * (sizeof(jogo *)));
  for (i = 0; i < M; i++)
  {
    nova_hastable[i] = 0;
  }

  return nova_hastable;
}

jogo *insere_jogo(jogo *novo_jogo, int *pt_max_ht_jogos, jogo **hashtable_jogos, int *pt_num_elem, lista_jogos *lst_jogos)
{
  int i = hash(novo_jogo->nome, *pt_max_ht_jogos);
  while (hashtable_jogos[i] != 0)
  {
    if (strcmp(hashtable_jogos[i]->nome, novo_jogo->nome) == 0)
    {
      return 0;
    }
    else
    {
      
    }

    i = (i + 1) % (*pt_max_ht_jogos);
  }

  hashtable_jogos[i] = novo_jogo;
  novo_jogo->anterior = lst_jogos->jogo_final;
  novo_jogo->seguinte = 0;
  if (lst_jogos->jogo_final != 0)
  {
    lst_jogos->jogo_final->seguinte = novo_jogo;
  }
  else
  {
    lst_jogos->jogo_inicial = novo_jogo;
  }

  lst_jogos->jogo_final = novo_jogo;
  if (((*pt_num_elem)++) > ((*pt_max_ht_jogos) / 2))
  {
    hashtable_jogos = expande_hashtable_jogos(hashtable_jogos, pt_max_ht_jogos, pt_num_elem, lst_jogos);
  }
  else
  {
    
  }

  return hashtable_jogos[i];
}

void liberta_hashtable_jogos(jogo **ht_jogos, int max_ht_jogos)
{
  int i;
  for (i = 0; i < max_ht_jogos; i++)
  {
    if (ht_jogos[i] != 0)
    {
      liberta_jogo(ht_jogos[i]);
    }
    else
    {
      
    }

  }

  free(ht_jogos);
}

jogo **expande_hashtable_jogos(jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem, lista_jogos *lst_jogos)
{
  int i;
  jogo **hastable_antiga = ht_jogos;
  *pt_max_ht_jogos = 2 * (*pt_max_ht_jogos);
  ht_jogos = inicia_hashtable_jogos(pt_max_ht_jogos, pt_num_elem);
  for (i = 0; i < ((*pt_max_ht_jogos) / 2); i++)
  {
    if (hastable_antiga[i] != 0)
    {
      insere_jogo(hastable_antiga[i], pt_max_ht_jogos, ht_jogos, pt_num_elem, lst_jogos);
    }
    else
    {
      
    }

  }

  free(hastable_antiga);
  return ht_jogos;
}

jogo *procura_jogo_ht(jogo **ht_jogos, char nome_jogo_procurar[], int max_ht_jogos)
{
  int i = hash(nome_jogo_procurar, max_ht_jogos);
  while (ht_jogos[i] != 0)
  {
    if (strcmp(ht_jogos[i]->nome, nome_jogo_procurar) == 0)
    {
      return ht_jogos[i];
    }
    else
    {
      i = (i + 1) % max_ht_jogos;
    }

  }

  return 0;
}

int remove_jogo_ht(char nome_jogo_eliminar[], jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem_ht_jogos, lista_jogos *lst_jogos)
{
  int j;
  int i = hash(nome_jogo_eliminar, *pt_max_ht_jogos);
  while (ht_jogos[i] != 0)
  {
    if (strcmp(ht_jogos[i]->nome, nome_jogo_eliminar) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % (*pt_max_ht_jogos);
    }

  }

  if (ht_jogos[i] == 0)
  {
    return -1;
  }
  else
  {
    
  }

  altera_resultados_jogo(ht_jogos[i], 0, 0);
  if (ht_jogos[i]->anterior == 0)
  {
    lst_jogos->jogo_inicial = ht_jogos[i]->seguinte;
  }
  else
  {
    ht_jogos[i]->anterior->seguinte = ht_jogos[i]->seguinte;
  }

  if (ht_jogos[i]->seguinte == 0)
  {
    lst_jogos->jogo_final = ht_jogos[i]->anterior;
  }
  else
  {
    ht_jogos[i]->seguinte->anterior = ht_jogos[i]->anterior;
  }

  liberta_jogo(ht_jogos[i]);
  ht_jogos[i] = 0;
  (*pt_num_elem_ht_jogos)--;
  for (j = (i + 1) % (*pt_max_ht_jogos); ht_jogos[j] != 0; j = (j + 1) % (*pt_max_ht_jogos), (*pt_num_elem_ht_jogos)--)
  {
    jogo *aux_remove_jogo = ht_jogos[j];
    ht_jogos[j] = 0;
    insere_jogo(aux_remove_jogo, pt_max_ht_jogos, ht_jogos, pt_num_elem_ht_jogos, lst_jogos);
  }

  return 0;
}
