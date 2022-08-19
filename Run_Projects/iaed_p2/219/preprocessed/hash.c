/*File generated by PreProcessor.py*/


#include "hash.h"


static link_jogo *htj;
static link_equipa *hte;
int hash(char *nome)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*nome) != '\0'; nome++, a = (a * b) % (2003 - 1))
  {
    h = ((a * h) + (*nome)) % 2003;
  }

  return h;
}

void Initjogo()
{
  int i;
  htj = malloc(2003 * (sizeof(link_jogo)));
  for (i = 0; i < 2003; i++)
  {
    htj[i] = 0;
  }

}

jogo *searchListJogo(int hashID, char *nome)
{
  jogo *auxjogo = 0;
  link_jogo aux = htj[hashID];
  while (aux != 0)
  {
    if (strcmp(aux->j->nome, nome) == 0)
    {
      return aux->j;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return auxjogo;
}

jogo *STsearchJogo(char *nome)
{
  int i = hash(nome);
  return searchListJogo(i, nome);
}

int insertBeginListJogo(int hashID, jogo *jg)
{
  jogo *auxjogo;
  link_jogo novoNo;
  auxjogo = searchListJogo(hashID, jg->nome);
  if (auxjogo == 0)
  {
    {
      novoNo = malloc(sizeof(struct node_jogo));
      novoNo->j = jg;
      novoNo->next = htj[hashID];
      htj[hashID] = novoNo;
      return 0;
    }
  }
  else
  {
    {
      return -1;
    }
  }

}

void STinsertJogo(jogo *jg)
{
  int i;
  i = hash(jg->nome);
  insertBeginListJogo(i, jg);
}

int removeItemJogo(int hashID, char *nome)
{
  link_jogo aux = htj[hashID];
  link_jogo auxRem;
  if (strcmp(aux->j->nome, nome) == 0)
  {
    {
      htj[hashID] = aux->next;
      free_jogo(aux->j);
      free(aux);
      return 0;
    }
  }
  else
  {
    
  }

  while (aux->next != 0)
  {
    if (strcmp(aux->next->j->nome, nome) == 0)
    {
      {
        auxRem = aux->next;
        aux->next = aux->next->next;
        free_jogo(auxRem->j);
        free(auxRem);
        return 0;
      }
    }
    else
    {
      {
        auxRem = aux->next;
        auxRem = aux->next;
      }
    }

    aux = aux->next->next;
  }

  return -1;
}

void STdelete(char *nome)
{
  int i = hash(nome);
  removeItemJogo(i, nome);
}

void ApagaHashJogo()
{
  int i = 0;
  link_jogo hashtb;
  for (i = 0; i < 2003; i++)
  {
    hashtb = htj[i];
    while (hashtb != 0)
    {
      link_jogo aux_free = hashtb->next;
      free(hashtb);
      hashtb = aux_free;
    }

  }

  free(htj);
}

void Initequipa()
{
  int i;
  hte = malloc(2003 * (sizeof(link_equipa)));
  for (i = 0; i < 2003; i++)
  {
    hte[i] = 0;
  }

}

equipa *searchListEquipa(int hashID, char *nome)
{
  equipa *auxequipa = 0;
  link_equipa aux = hte[hashID];
  while (aux != 0)
  {
    if (strcmp(aux->e->nome, nome) == 0)
    {
      return aux->e;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return auxequipa;
}

equipa *STsearchEquipa(char *nome)
{
  int i = hash(nome);
  return searchListEquipa(i, nome);
}

int insertBeginListEquipa(int hashID, equipa *eq)
{
  equipa *auxequipa;
  link_equipa novoNo;
  auxequipa = searchListEquipa(hashID, eq->nome);
  if (auxequipa == 0)
  {
    {
      novoNo = malloc(sizeof(struct node_equipa));
      novoNo->e = eq;
      novoNo->next = hte[hashID];
      hte[hashID] = novoNo;
      return 0;
    }
  }
  else
  {
    {
      return -1;
    }
  }

}

void STinsertEquipa(equipa *eq)
{
  int i;
  i = hash(eq->nome);
  insertBeginListEquipa(i, eq);
}

void ApagaHashEquipa()
{
  int i = 0;
  link_equipa hashtb;
  for (i = 0; i < 2003; i++)
  {
    hashtb = hte[i];
    while (hashtb != 0)
    {
      link_equipa aux_free = hashtb->next;
      free(hashtb);
      hashtb = aux_free;
    }

  }

  free(hte);
}
