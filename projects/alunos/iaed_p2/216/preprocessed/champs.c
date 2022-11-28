#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "champs.h"


void swap(char *s1, char *s2)
{
  char aux[1024];
  strcpy(aux, s1);
  strcpy(s1, s2);
  strcpy(s2, aux);
}

void bubble(list *aux)
{
  int flag;
  node *ptr;
  do
  {
    flag = 0;
    ptr = aux->head;
    while (ptr)
    {
      if (getHashKey(ptr->name) > getHashKey(ptr->next->name))
      {
        swap(ptr->name, ptr->next->name);
        flag = 1;
      }
      else
      {
        
      }

      ptr = ptr->next;
    }

  }
  while (flag);
}

void findChamps(list *tms)
{
  int m_wins = 0;
  list *aux = startList();
  node *ptr = tms->head;
  if (tms == 0)
  {
    free(aux);
    return;
  }
  else
  {
    while (ptr)
    {
      if (m_wins < ptr->won)
      {
        m_wins = ptr->won;
      }
      else
      {
        
      }

      ptr = ptr->next;
    }

    ptr = tms->head;
    while (ptr)
    {
      if (m_wins == ptr->won)
      {
        if (aux->head == 0)
        {
          aux->head = ptr;
        }
        else
        {
          ptr->previous = aux->end;
          aux->end->next = ptr;
        }

        aux->end = ptr;
      }
      else
      {
        
      }

      printf("%s\n", ptr->name);
      ptr = ptr->next;
    }

    bubble(aux);
    if (aux != 0)
    {
      printf("%d Melhores %d\n", counter, m_wins);
      ptr = aux->head;
      while (ptr)
      {
        printf("%d * %s\n", counter, ptr->name);
        ptr = ptr->next;
      }

    }
    else
    {
      
    }

  }

  deleteList(aux, 1);
  free(aux);
}
