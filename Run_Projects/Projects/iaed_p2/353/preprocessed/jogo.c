/*File generated by PreProcessor.py*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"


ht_jogo *ht_init(void)
{
  int i = 0;
  ht_jogo *hashtable = malloc(sizeof(ht_jogo));
  hashtable->links = malloc((sizeof(link_jogo *)) * 1553);
  for (; i < 1553; ++i)
  {
    hashtable->links[i] = 0;
  }

  return hashtable;
}

link_jogo *ht_pair(ht_jogo *hashtable, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2)
{
  unsigned int slot = hash(nome);
  link_jogo *x = malloc(sizeof(link_jogo));
  x->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  x->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  x->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(x->nome, nome);
  strcpy(x->equipa1, equipa1);
  strcpy(x->equipa2, equipa2);
  x->score1 = score1;
  x->score2 = score2;
  x->next = hashtable->links[slot];
  hashtable->links[slot] = x;
  return x;
}

void ht_set(ht_jogo *hashtable, ll_jogos **ll_head, ht_equipas *hashtable_equipas, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2, int NL)
{
  link_equipa *estado_equipa1 = st_search(hashtable_equipas, equipa1);
  link_equipa *estado_equipa2 = st_search(hashtable_equipas, equipa2);
  link_jogo *jogo = st_search_jogo(hashtable, nome);
  link_jogo *new;
  if (jogo != 0)
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  else
  {
    
  }

  if ((estado_equipa1 == 0) || (estado_equipa2 == 0))
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (score1 > score2)
  {
    estado_equipa1->nr_vitorias++;
  }
  else
  {
    
  }

  if (score1 < score2)
  {
    estado_equipa2->nr_vitorias++;
  }
  else
  {
    
  }

  new = ht_pair(hashtable, nome, equipa1, equipa2, score1, score2);
  insertEndJogos(ll_head, new);
}

link_jogo *st_search_jogo(ht_jogo *hashtable, const char *nome)
{
  unsigned int slot = hash(nome);
  link_jogo *x = hashtable->links[slot];
  while (x != 0)
  {
    if (strcmp(x->nome, nome) == 0)
    {
      return x;
    }
    else
    {
      
    }

    x = x->next;
  }

  return 0;
}

void ht_search(ht_jogo *hashtable, const char *nome, int NL)
{
  link_jogo *x = st_search_jogo(hashtable, nome);
  if (x == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1, x->equipa2, x->score1, x->score2);
}

void ht_del(ht_jogo *hashtable, const char *nome, int NL)
{
  unsigned int slot = hash(nome);
  int indice = 0;
  link_jogo *x = hashtable->links[slot];
  link_jogo *anterior;
  if (x == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  while (x != 0)
  {
    if (strcmp(x->nome, nome) == 0)
    {
      if ((x->next == 0) && (indice == 0))
      {
        hashtable->links[slot] = 0;
      }
      else
      {
        
      }

      if ((x->next != 0) && (indice == 0))
      {
        hashtable->links[slot] = x->next;
      }
      else
      {
        
      }

      if ((x->next == 0) && (indice != 0))
      {
        anterior->next = 0;
      }
      else
      {
        
      }

      if ((x->next != 0) && (indice != 0))
      {
        anterior->next = x->next;
      }
      else
      {
        
      }

      free(x->nome);
      free(x->equipa1);
      free(x->equipa2);
      free(x);
      return;
    }
    else
    {
      
    }

    anterior = x;
    x = anterior->next;
    ++indice;
  }

  printf("%d Jogo inexistente.\n", NL);
}

void ht_change(ht_jogo *hashtable, ht_equipas *hashtable_equipas, const char *nome, int score1, int score2, int NL)
{
  link_jogo *x = st_search_jogo(hashtable, nome);
  link_equipa *equipa1;
  link_equipa *equipa2;
  if (x == 0)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  equipa1 = st_search(hashtable_equipas, x->equipa1);
  equipa2 = st_search(hashtable_equipas, x->equipa2);
  if (score1 > score2)
  {
    if (x->score1 < x->score2)
    {
      equipa1->nr_vitorias++;
      equipa2->nr_vitorias--;
    }
    else
    {
      
    }

    if (x->score1 == x->score2)
    {
      equipa1->nr_vitorias++;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  if (score1 < score2)
  {
    if (x->score1 > x->score2)
    {
      equipa1->nr_vitorias--;
      equipa2->nr_vitorias++;
    }
    else
    {
      
    }

    if (x->score1 == x->score2)
    {
      equipa2->nr_vitorias++;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  if (score1 == score2)
  {
    if (x->score1 > x->score2)
    {
      equipa1->nr_vitorias--;
    }
    else
    {
      
    }

    if (x->score1 < x->score2)
    {
      equipa2->nr_vitorias--;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

  x->score1 = score1;
  x->score2 = score2;
}

void insertEndJogos(ll_jogos **head_ref, link_jogo *jogo)
{
  ll_jogos *last = *head_ref;
  ll_jogos *novo_node = malloc(sizeof(ll_jogos));
  novo_node->jogo = jogo;
  novo_node->next = 0;
  if ((*head_ref) == 0)
  {
    *head_ref = novo_node;
    return;
  }
  else
  {
    
  }

  while (last->next != 0)
    last = last->next;

  last->next = novo_node;
  return;
}

void deleteNode(ll_jogos **head_ref, link_jogo *jogo)
{
  ll_jogos *temp = *head_ref;
  ll_jogos *anterior;
  if ((temp != 0) && (temp->jogo == jogo))
  {
    *head_ref = temp->next;
    free(temp);
    return;
  }
  else
  {
    
  }

  while ((temp != 0) && (temp->jogo != jogo))
  {
    anterior = temp;
    temp = temp->next;
  }

  if (temp == 0)
  {
    return;
  }
  else
  {
    
  }

  anterior->next = temp->next;
  free(temp);
}

void deleteList(ll_jogos **head)
{
  ll_jogos *atual = *head;
  ll_jogos *antigo;
  while (atual != 0)
  {
    antigo = atual;
    atual = atual->next;
    free(antigo);
  }

  *head = 0;
}

