/*File generated by PreProcessor.py*/


#include "team_lists.h"


tlink TNEW(Equipa equipa)
{
  tlink x = malloc(sizeof(struct tnode));
  x->equipa = equipa;
  x->next = 0;
  return x;
}

tlink TinsertBegin(tlink head, Equipa equipa)
{
  tlink x = TNEW(equipa);
  x->next = head;
  return x;
}

tlink TinsertEnd(tlink head, Equipa equipa)
{
  tlink x;
  if (head == 0)
  {
    {
      return TNEW(equipa);
    }
  }
  else
  {
    
  }

  for (x = head; x->next != 0; x = x->next)
    ;

  x->next = TNEW(equipa);
  return head;
}

tlink Tlookup(tlink head, char *v)
{
  tlink t;
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->equipa->nome, v) == 0)
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

tlink TremoveItem(tlink head, Equipa equipa, int n)
{
  tlink t;
  tlink prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->equipa->nome, equipa->nome) == 0)
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
            libertaEquipa(equipa);
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

