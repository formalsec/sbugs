#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hash.h"


unsigned int hash(int M, const char *nome)
{
  unsigned int i;
  unsigned int index = 0;
  for (i = 0; i < strlen(nome); i++)
  {
    index += nome[i];
    index = (index * nome[i]) % M;
  }

  return index;
}

pLink insertBeginList(pLink head, pJogo j)
{
  pLink old_head = head;
  head = malloc(sizeof(struct link));
  head->next = old_head;
  head->j = j;
  return head;
}

pLink_e insertBeginList_e(pLink_e head, pEquipa e)
{
  pLink_e old_head = head;
  head = malloc(sizeof(struct link_e));
  head->next = old_head;
  head->e = e;
  return head;
}

pJogo searchList(pLink head, char *nome)
{
  pLink temp = head;
  while (temp)
  {
    if (strcmp(temp->j->nome, nome) == 0)
    {
      return temp->j;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return 0;
}

pEquipa searchList_e(pLink_e head, char *nome)
{
  pLink_e temp = head;
  while (temp)
  {
    if (strcmp(temp->e->nome_e, nome) == 0)
    {
      return temp->e;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return 0;
}

pLink removeList(pLink head, char *nome)
{
  pLink temp = head;
  pLink prev = 0;
  if (!head)
  {
    return 0;
  }
  else
  {
    
  }

  while (temp)
  {
    if (strcmp(temp->j->nome, nome) == 0)
    {
      if (temp == head)
      {
        head = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }

      free_link(temp);
      break;
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

  return head;
}

pHash ht_init(int m)
{
  int i;
  pHash h = malloc(sizeof(struct ht));
  h->M = m;
  h->heads = (pLink *) malloc(h->M * (sizeof(struct link)));
  for (i = 0; i < m; i++)
  {
    h->heads[i] = 0;
  }

  return h;
}

pHash_e ht_init_e(int m)
{
  int i;
  pHash_e h_e = malloc(sizeof(struct ht_e));
  h_e->M = m;
  h_e->heads_e = (pLink_e *) malloc(h_e->M * (sizeof(struct link_e)));
  for (i = 0; i < m; i++)
  {
    h_e->heads_e[i] = 0;
  }

  return h_e;
}

void ht_destroy(pHash h)
{
  int i;
  pLink t1;
  for (i = 0; i < h->M; i++)
  {
    t1 = h->heads[i];
    while (h->heads[i])
    {
      t1 = h->heads[i];
      h->heads[i] = h->heads[i]->next;
      free_link(t1);
    }

  }

  free(h->heads);
  free(h);
}

void ht_e_destroy(pHash_e h_e)
{
  int i;
  pLink_e t1;
  for (i = 0; i < h_e->M; i++)
  {
    t1 = h_e->heads_e[i];
    while (h_e->heads_e[i])
    {
      t1 = h_e->heads_e[i];
      h_e->heads_e[i] = h_e->heads_e[i]->next;
      free_link_e(t1);
    }

  }

  free(h_e->heads_e);
  free(h_e);
}

pJogo ht_search(pHash h, char *nome)
{
  int i = hash(h->M, nome);
  if (h->heads[i] != 0)
  {
    return searchList(h->heads[i], nome);
  }
  else
  {
    pJogo j = 0;
    return j;
  }

}

pEquipa ht_search_e(pHash_e h_e, char *nome_e)
{
  int i = hash(h_e->M, nome_e);
  if (h_e->heads_e[i] != 0)
  {
    return searchList_e(h_e->heads_e[i], nome_e);
  }
  else
  {
    pEquipa e = 0;
    return e;
  }

}

void ht_insert(pHash h, pJogo j)
{
  int i = hash(h->M, j->nome);
  h->heads[i] = insertBeginList(h->heads[i], j);
}

void ht_insert_e(pHash_e h_e, pEquipa e)
{
  int i = hash(h_e->M, e->nome_e);
  h_e->heads_e[i] = insertBeginList_e(h_e->heads_e[i], e);
}

void ht_delete(pHash h, char *nome)
{
  int i = hash(h->M, nome);
  h->heads[i] = removeList(h->heads[i], nome);
}

