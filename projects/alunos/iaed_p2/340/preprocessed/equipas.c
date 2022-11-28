#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "equipas.h"


Equipa *cria_equipa(char *nome)
{
  Equipa *x = malloc(sizeof(Equipa));
  x->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(x->nome, nome);
  x->ganhos = 0;
  x->next = 0;
  return x;
}

void altera_ganhos(Equipa *head, int S)
{
  if (S)
  {
    head->ganhos += 1;
  }
  else
  {
    if ((!S) && (head->ganhos > 0))
    {
      head->ganhos -= 1;
    }
    else
    {
      
    }

  }

}

void free_equipa(Equipa *head)
{
  free(head->nome);
  free(head);
}
