#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "sort.h"


void swap(tlink i, tlink j)
{
  Equipa aux;
  aux = i->equipa;
  i->equipa = j->equipa;
  j->equipa = aux;
}

void sortlist(tlink head)
{
  tlink i;
  tlink j;
  for (i = head; i != 0; i = i->next)
  {
    for (j = i->next; j != 0; j = j->next)
    {
      if (strcmp(i->equipa->nome, j->equipa->nome) > 0)
      {
        swap(i, j);
      }
      else
      {
        
      }

    }

  }

}

