/*File generated by PreProcessor.py*/


#include "hashtable_equipas.h"


void HTinic_equipas(Equipa **equipas, int max)
{
  int i;
  for (i = 0; i < max; i++)
    equipas[i] = 0;

}

void HTinsere_equipa(Equipa *equipa, Equipa **equipas, int dim)
{
  int chave;
  char *nome;
  Equipa *equipa_aux;
  nome = equipa->nome;
  chave = hash(nome, dim);
  if (equipas[chave] == 0)
  {
    equipas[chave] = equipa;
  }
  else
  {
    equipa_aux = equipas[chave];
    while (equipa_aux->next != 0)
      equipa_aux = equipa_aux->next;

    equipa_aux->next = equipa;
  }

}

Equipa *HTprocura_equipa(char *nome, Equipa **equipas, int dim)
{
  Equipa *equipa_aux;
  int chave = hash(nome, dim);
  if (equipas[chave] == 0)
  {
    return 0;
  }
  else
  {
    equipa_aux = equipas[chave];
    while ((strcmp(nome, equipa_aux->nome) != 0) && (equipa_aux->next != 0))
      equipa_aux = equipa_aux->next;

    if (strcmp(nome, equipa_aux->nome) == 0)
    {
      return equipa_aux;
    }
    else
    {
      return 0;
    }

  }

}

void quicksort_equipas(Equipa **equipas, int first, int last)
{
  int i;
  int j;
  int prim;
  Equipa *temp;
  if (first < last)
  {
    prim = first;
    i = first;
    j = last;
    while (i < j)
    {
      while ((strcmp(equipas[i]->nome, equipas[prim]->nome) <= 0) && (i < last))
        i++;

      while (strcmp(equipas[j]->nome, equipas[prim]->nome) > 0)
        j--;

      if (i < j)
      {
        temp = equipas[i];
        equipas[i] = equipas[j];
        equipas[j] = temp;
      }
      else
      {
        
      }

    }

    temp = equipas[prim];
    equipas[prim] = equipas[j];
    equipas[j] = temp;
    quicksort_equipas(equipas, first, j - 1);
    quicksort_equipas(equipas, j + 1, last);
  }
  else
  {
    
  }

}

void HTencontra_mais_vitorias(Equipa **equipas, int dim, int conta_linhas)
{
  Equipa **equipas_vencedoras;
  Equipa *aux;
  int max_vitorias = 0;
  int i;
  int j = 0;
  equipas_vencedoras = (Equipa **) malloc(sizeof(Equipa));
  for (i = 0; i < dim; i++)
  {
    aux = equipas[i];
    while (aux != 0)
    {
      if (aux->numero_vitorias > max_vitorias)
      {
        max_vitorias = aux->numero_vitorias;
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  for (i = 0; i < dim; i++)
  {
    aux = equipas[i];
    while (aux != 0)
    {
      if (aux->numero_vitorias == max_vitorias)
      {
        equipas_vencedoras[j] = aux;
        j++;
        equipas_vencedoras = realloc(equipas_vencedoras, (j + 1) * (sizeof(Equipa)));
      }
      else
      {
        
      }

      aux = aux->next;
    }

  }

  if (j == 0)
  {
    free(equipas_vencedoras);
    return;
  }
  else
  {
    
  }

  quicksort_equipas(equipas_vencedoras, 0, j - 1);
  printf("%d Melhores %d\n", conta_linhas, max_vitorias);
  for (i = 0; i < j; i++)
    printNome_Equipa(equipas_vencedoras[i], conta_linhas);

  free(equipas_vencedoras);
}

void HTfree_equipas(Equipa **equipas, int dim)
{
  Equipa *equipa_aux_1;
  Equipa *equipa_aux_2;
  int i;
  for (i = 0; i < dim; i++)
  {
    equipa_aux_1 = equipas[i];
    while (equipa_aux_1 != 0)
    {
      equipa_aux_2 = equipa_aux_1;
      equipa_aux_1 = equipa_aux_1->next;
      freeEquipa(equipa_aux_2);
    }

  }

  free(equipas);
}

