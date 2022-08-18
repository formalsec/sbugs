/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JOGOS.h"


int J_hash(char *v, int M)
{
  int h = 0;
  int a = 919;
  for (; (*v) != '\0'; v++)
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

Q QUEUEinit()
{
  Q q = (Q) malloc(sizeof(struct queue));
  q->head = 0;
  q->tail = 0;
  return q;
}

Jlink *J_Init()
{
  int i;
  Jlink *Jheads;
  Jheads = (Jlink *) malloc(1637 * (sizeof(Jlink)));
  for (i = 0; i < 1637; i++)
    Jheads[i] = 0;

  return Jheads;
}

pJogo J_STSearch(Jlink *Jheads, char *nome)
{
  int i = J_hash(nome, 1637);
  return J_Procura_Hash(Jheads[i], nome);
}

void J_STinsert(Q Todos_Jogos, Jlink *Jheads, pJogo p)
{
  int i = J_hash(p->nome, 1637);
  Jheads[i] = J_Push(Todos_Jogos, Jheads[i], p);
}

Jlink J_Push(Q Todos_Jogos, Jlink head, pJogo p)
{
  Jlink next = head;
  head = (Jlink) malloc(sizeof(struct Jnode));
  head->next = next;
  head->j = p;
  head->pass = QUEUEput(Todos_Jogos, p);
  return head;
}

void J_STdelete(Jlink *Jheads, Q Todos_Jogos, pJogo p)
{
  int i = J_hash(p->nome, 1637);
  Jheads[i] = Apaga_Jogo_Hash(Jheads[i], Todos_Jogos, p);
}

Jlink Apaga_Jogo_Hash(Jlink head, Q q, pJogo p)
{
  Jlink t;
  Jlink pre;
  for (pre = 0, t = head; t != 0; pre = t, t = t->next)
  {
    if (strcmp(t->j->nome, p->nome) == 0)
    {
      {
        if (!t->pass->prev)
        {
          QUEUE_Pop(q);
        }
        else
        {
          if (!t->pass->next)
          {
            {
              q->tail = q->tail->prev;
              q->tail->next = 0;
              free(t->pass);
            }
          }
          else
          {
            {
              Qlink ant = t->pass->prev;
              Qlink prox = t->pass->next;
              ant->next = prox;
              prox->prev = ant;
              free(t->pass);
            }
          }

        }

        if (t == head)
        {
          head = t->next;
        }
        else
        {
          pre->next = t->next;
        }

        FREE_Jnode(t);
        break;
      }
    }
    else
    {
      
    }

  }

  return head;
}

void Limpa_Jheads(Jlink *Jheads)
{
  int i;
  for (i = 0; i < 1637; i++)
    destroy_J(Jheads[i]);

  free(Jheads);
}

Jlink Jpop(Jlink head)
{
  Jlink next;
  if (!head)
  {
    return 0;
  }
  else
  {
    
  }

  next = head->next;
  FREE_Jnode(head);
  return next;
}

Jlink destroy_J(Jlink head)
{
  while (head)
    head = Jpop(head);

  return 0;
}

pJogo J_Procura_Hash(Jlink head, char *nome)
{
  Jlink t;
  for (t = head; t != 0; t = t->next)
    if (strcmp(t->j->nome, nome) == 0)
  {
    return t->j;
  }
  else
  {
    
  }


  return 0;
}

Qlink QUEUEput(Q q, pJogo p)
{
  if (q->head == 0)
  {
    {
      q->head = (q->tail = NEWnode(p, q->head));
      q->head->prev = 0;
      return q->head;
    }
  }
  else
  {
    
  }

  q->tail->next = NEWnode(p, q->tail->next);
  q->tail->next->prev = q->tail;
  q->tail = q->tail->next;
  return q->tail;
}

Qlink NEWnode(pJogo p, Qlink next)
{
  Qlink x = (Qlink) malloc(sizeof(struct QUEUEjogos));
  x->j = p;
  x->next = next;
  return x;
}

void Limpa_QUEUE(Q Todos_Jogos)
{
  while (Todos_Jogos->head != 0)
    Todos_Jogos = QUEUE_Pop(Todos_Jogos);

  free(Todos_Jogos);
}

Q QUEUE_Pop(Q q)
{
  Qlink t = q->head->next;
  free(q->head);
  q->head = t;
  if (q->head)
  {
    q->head->prev = 0;
  }
  else
  {
    
  }

  return q;
}

void FREE_Jnode(Jlink head)
{
  free(head->j->nome);
  free(head->j->equipa1);
  free(head->j->equipa2);
  free(head->j);
  free(head);
}

