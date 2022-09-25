/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "estruturas.h"


int hash(char *nome_jogo, int *M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*nome_jogo) != '\0'; nome_jogo++, a = (a * b) % ((*M) - 1))
  {
    h = ((a * h) + (*nome_jogo)) % (*M);
  }

  if (h < 0)
  {
    h = h * (-1);
  }
  else
  {
    
  }

  return h;
}

void Stinit(int *M, pjogo *st)
{
  int i;
  for (i = 0; i < (*M); i++)
  {
    st[i] = 0;
  }

}

void Stinsert(char *nome_jogo, char *equipa1, char *equipa2, int score1, int score2, int *M, pjogo *st, link *head)
{
  int i = hash(nome_jogo, M);
  while (st[i] != 0)
  {
    i = (i + 1) % (*M);
  }

  st[i] = (pjogo) malloc(sizeof(struct jogo));
  st[i]->score1 = score1;
  st[i]->score2 = score2;
  st[i]->nome_jogo = (char *) malloc((sizeof(char)) * (strlen(nome_jogo) + 1));
  strcpy(st[i]->nome_jogo, nome_jogo);
  st[i]->equipa1 = (char *) malloc((sizeof(char)) * (strlen(equipa1) + 1));
  strcpy(st[i]->equipa1, equipa1);
  st[i]->equipa2 = (char *) malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(st[i]->equipa2, equipa2);
  *head = insertEnd(head, st[i]);
}

void reinsere_el(pjogo el, pjogo *st, int *M, char *nome_jogo)
{
  int i = hash(nome_jogo, M);
  while (st[i] != 0)
  {
    i = (i + 1) % (*M);
  }

  st[i] = el;
}

link STdelete(char *nome_jogo, int *M, pjogo *st, link *head)
{
  int i = hash(nome_jogo, M);
  int j;
  link t;
  link prev;
  while (st[i] != 0)
  {
    if (strcmp(st[i]->nome_jogo, nome_jogo) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % (*M);
    }

  }

  for (t = *head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->jogo->nome_jogo, nome_jogo) == 0)
    {
      if (t == (*head))
      {
        *head = t->next;
        free(t->jogo->nome_jogo);
        free(t->jogo->equipa1);
        free(t->jogo->equipa2);
        free(t->jogo);
        free(t);
        st[i] = 0;
        break;
      }
      else
      {
        prev->next = t->next;
        t->next = 0;
        free(t->jogo->nome_jogo);
        free(t->jogo->equipa1);
        free(t->jogo->equipa2);
        free(t->jogo);
        free(t);
        st[i] = 0;
        break;
      }

    }
    else
    {
      
    }

  }

  for (j = (i + 1) % (*M); st[j] != 0; j = (j + 1) % (*M))
  {
    reinsere_el(st[j], st, M, st[j]->nome_jogo);
    st[j] = 0;
  }

  return *head;
}

pjogo search(char *nome_jogo, int *M, pjogo *st)
{
  int i = hash(nome_jogo, M);
  while (st[i] != 0)
  {
    if (strcmp(st[i]->nome_jogo, nome_jogo) == 0)
    {
      return st[i];
    }
    else
    {
      i = (i + 1) % (*M);
    }

  }

  return 0;
}

void Htinit(int *L, pequipa *ht)
{
  int i;
  for (i = 0; i < (*L); i++)
  {
    ht[i] = 0;
  }

}

void Htinsert(char *equipa, int vitorias, int *L, pequipa *ht, link *head_2)
{
  int i = hash(equipa, L);
  while (ht[i] != 0)
  {
    i = (i + 1) % (*L);
  }

  ht[i] = (pequipa) malloc(sizeof(struct equipas));
  ht[i]->vitorias = vitorias;
  ht[i]->equipa = (char *) malloc((sizeof(char)) * (strlen(equipa) + 1));
  strcpy(ht[i]->equipa, equipa);
  *head_2 = insertEnd_equipas(head_2, ht[i]);
}

pequipa search_equipa(char *equipa, int *L, pequipa *ht)
{
  int i = hash(equipa, L);
  while (ht[i] != 0)
  {
    if (strcmp(ht[i]->equipa, equipa) == 0)
    {
      return ht[i];
    }
    else
    {
      i = (i + 1) % (*L);
    }

  }

  return 0;
}

