/*File generated by PreProcessor.py*/


#include "hash_defines.h"
#include "jogos_hash.h"
#include "jogos_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


JOGO_HASH **init_hash_jogos()
{
  int i;
  JOGO_HASH **hashtable_jogos = malloc((sizeof(JOGO_HASH)) * 2001);
  for (i = 0; i < 2001; i++)
    hashtable_jogos[i] = 0;

  return hashtable_jogos;
}

void add_jogo_hash(JOGO_HASH **hashtable_jogos, JOGO *jogo)
{
  JOGO_HASH *tmp = 0;
  unsigned long indice;
  indice = hash(jogo->nome);
  if (hashtable_jogos[indice] == 0)
  {
    hashtable_jogos[indice] = calloc(1, sizeof(JOGO_HASH));
    hashtable_jogos[indice]->jogo_ptr = jogo;
  }
  else
  {
    tmp = calloc(1, sizeof(JOGO_HASH));
    tmp->next = hashtable_jogos[indice];
    tmp->jogo_ptr = jogo;
    hashtable_jogos[indice] = tmp;
  }

}

JOGO *procura_jogo(JOGO_HASH **hashtable_jogos, char *nome)
{
  unsigned long indice;
  JOGO_HASH *tmp = 0;
  indice = hash(nome);
  tmp = hashtable_jogos[indice];
  while (tmp != 0)
  {
    if (strcmp(tmp->jogo_ptr->nome, nome) == 0)
    {
      return tmp->jogo_ptr;
    }
    else
    {
      tmp = tmp->next;
    }

  }

  return 0;
}

void remove_jogo_hash(JOGO_HASH **hashtable_jogos, char *nome)
{
  unsigned long indice;
  JOGO_HASH *tmp = 0;
  JOGO_HASH *prev_tmp = 0;
  indice = hash(nome);
  tmp = hashtable_jogos[indice];
  while (tmp != 0)
  {
    if (strcmp(tmp->jogo_ptr->nome, nome) == 0)
    {
      break;
    }
    else
    {
      
    }

    prev_tmp = tmp;
    tmp = tmp->next;
  }

  if (tmp == 0)
  {
    return;
  }
  else
  {
    
  }

  if ((prev_tmp == 0) && (tmp->next == 0))
  {
    hashtable_jogos[indice] = 0;
  }
  else
  {
    if (prev_tmp == 0)
    {
      hashtable_jogos[indice] = tmp->next;
    }
    else
    {
      prev_tmp->next = tmp->next;
    }

  }

  free(tmp);
}

void altera_score(JOGO_HASH **hashtable_jogos, char *nome, int score1, int score2)
{
  JOGO *jogo_alterar = procura_jogo(hashtable_jogos, nome);
  jogo_alterar->score1 = score1;
  jogo_alterar->score2 = score2;
}

char *maior_score_jogo(JOGO_HASH **hashtable_jogos, char *nome)
{
  JOGO *jogo = procura_jogo(hashtable_jogos, nome);
  if (jogo->score1 > jogo->score2)
  {
    return jogo->equipa1;
  }
  else
  {
    
  }

  if (jogo->score1 < jogo->score2)
  {
    return jogo->equipa2;
  }
  else
  {
    return 0;
  }

}

void destroy_jogos_hash(JOGO_HASH **hashtable_jogos)
{
  JOGO_HASH *tmp = 0;
  int i;
  for (i = 0; i < 2001; i++)
  {
    while ((tmp = hashtable_jogos[i]) != 0)
    {
      hashtable_jogos[i] = hashtable_jogos[i]->next;
      free(tmp);
    }

  }

  free(hashtable_jogos);
}

