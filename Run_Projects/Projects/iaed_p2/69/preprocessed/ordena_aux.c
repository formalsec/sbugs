/*File generated by PreProcessor.py*/


#include "ordena_aux.h"


void lista_melhores_aux(lista_equipas *heads_eq, int mais_vitorias, int tamanho, int count)
{
  char **Equipas_mais_vit;
  int i;
  int k = 0;
  int size;
  lista_equipas aux;
  Equipas_mais_vit = (char **) malloc(tamanho * (sizeof(char *)));
  for (i = 0; i < 997; i++)
  {
    aux = heads_eq[i];
    while (aux != 0)
    {
      if (aux->equipa->vitorias == mais_vitorias)
      {
        size = strlen(aux->equipa->nome) + 1;
        Equipas_mais_vit[k] = malloc(size);
        strcpy(Equipas_mais_vit[k], aux->equipa->nome);
        k++;
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  ordena(Equipas_mais_vit, k);
  printf("%d Melhores %d\n", count, mais_vitorias);
  for (i = 0; i < k; i++)
  {
    printf("%d * %s\n", count, Equipas_mais_vit[i]);
  }

  while ((--i) >= 0)
  {
    free(Equipas_mais_vit[i]);
  }

  free(Equipas_mais_vit);
}

int comparador(const void *a, const void *b)
{
  return strcmp(*((char **) a), *((char **) b));
}

void ordena(char **arr, int n)
{
  qsort(arr, n, sizeof(const char *), comparador);
}

