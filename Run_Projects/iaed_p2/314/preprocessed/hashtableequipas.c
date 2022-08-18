/*File generated by PreProcessor.py*/


#include "hashtableequipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hashe(char *v, int m)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % m;

  return h;
}

linke *STiniciae(int M)
{
  int i;
  linke *heads = malloc(M * (sizeof(linke)));
  for (i = 0; i < M; i++)
  {
    heads[i] = 0;
  }

  return heads;
}

linke insereListe(linke head, equipa *eq)
{
  linke e = malloc(sizeof(struct nodee));
  e->equipa = eq;
  if (head == 0)
  {
    {
      e->next = 0;
      head = e;
    }
  }
  else
  {
    {
      e->next = head;
      head = e;
    }
  }

  return head;
}

void STinsertee(equipa *eq, int M, linke *heads)
{
  int i = hashe(eq->nomeeq, M);
  heads[i] = insereListe(heads[i], eq);
}

equipa *procuraListe(linke head, char *nome)
{
  linke tmp = head;
  if (tmp == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  while ((tmp != 0) && (strcmp(tmp->equipa->nomeeq, nome) != 0))
  {
    tmp = tmp->next;
  }

  if ((tmp != 0) && (strcmp(tmp->equipa->nomeeq, nome) == 0))
  {
    {
      return tmp->equipa;
    }
  }
  else
  {
    
  }

  return 0;
}

equipa *STprocurae(char *nomeeq, int M, linke *heads)
{
  int i = hashe(nomeeq, M);
  return procuraListe(heads[i], nomeeq);
}

void STfree_listhte(linke head)
{
  linke tmp;
  while (head)
  {
    tmp = head->next;
    free(head->equipa->nomeeq);
    free(head->equipa);
    free(head);
    head = tmp;
  }

}

void STfree_hte(int M, linke *heads)
{
  int i;
  for (i = 0; i < M; i++)
  {
    STfree_listhte(heads[i]);
  }

  free(heads);
}

