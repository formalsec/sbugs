/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EQUIPAS.h"


int E_hash(char *v, int M)
{
  int h = 0;
  int a = 919;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % M;

  return h;
}

Elink *E_Init()
{
  int i;
  Elink *Eheads;
  Eheads = (Elink *) malloc(1637 * (sizeof(Elink)));
  for (i = 0; i < 1637; i++)
    Eheads[i] = 0;

  return Eheads;
}

pEquipa E_STSearch(Elink *Eheads, char *nome)
{
  int i = E_hash(nome, 1637);
  return E_Procura_Hash(Eheads[i], nome);
}

void E_STinsert(Elink *Eheads, pEquipa p)
{
  int i = E_hash(p->nome, 1637);
  Eheads[i] = E_Push(Eheads[i], p);
}

Elink E_Push(Elink head, pEquipa p)
{
  Elink next = head;
  head = malloc(sizeof(struct Enode));
  head->next = next;
  head->e = p;
  return head;
}

void Limpa_Eheads(Elink *Eheads)
{
  int i;
  for (i = 0; i < 1637; i++)
    destroy_E(Eheads[i]);

  free(Eheads);
}

Elink Epop(Elink head)
{
  Elink next;
  if (!head)
  {
    return 0;
  }
  else
  {
    
  }

  next = head->next;
  free(head->e->nome);
  free(head->e);
  free(head);
  return next;
}

Elink destroy_E(Elink head)
{
  while (head)
    head = Epop(head);

  return 0;
}

pEquipa E_Procura_Hash(Elink head, char *nome)
{
  Elink t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->e->nome, nome) == 0)
  {
    return t->e;
  }
  else
  {
    
  }


  return 0;
}

int Compara_strcmp(const void *a, const void *b)
{
  return strcmp(*((const char **) a), *((const char **) b));
}
