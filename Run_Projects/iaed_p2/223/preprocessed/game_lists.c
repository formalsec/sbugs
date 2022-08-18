/*File generated by PreProcessor.py*/


#include "game_lists.h"


glink GNEW(Jogo jogo)
{
  glink x = malloc(sizeof(struct gnode));
  x->jogo = jogo;
  x->next = 0;
  return x;
}

glink GinsertBegin(glink head, Jogo jogo)
{
  glink x = GNEW(jogo);
  x->next = head;
  return x;
}

glink GinsertEnd(glink head, Jogo jogo)
{
  glink x;
  if (head == 0)
  {
    {
      return GNEW(jogo);
    }
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = GNEW(jogo);
  return head;
}

glink Glookup(glink head, char *v)
{
  glink t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->jogo->nome, v) == 0)
    {
      {
        return t;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

glink GremoveItem(glink head, Jogo jogo, int n)
{
  glink t;
  glink prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->jogo->nome, jogo->nome) == 0)
    {
      {
        if (t == head)
        {
          {
            head = t->next;
          }
        }
        else
        {
          {
            prev->next = t->next;
          }
        }

        if (n == 1)
        {
          {
            libertaJogo(jogo);
          }
        }
        else
        {
          
        }

        free(t);
        break;
      }
    }
    else
    {
      
    }

  }

  return head;
}

