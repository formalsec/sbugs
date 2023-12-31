#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "equipas.h"
#include "common.h"


TabelaEquipas *inicia_tabela_equipas(int capacidade)
{
  int i;
  TabelaEquipas *tabela = malloc(sizeof(TabelaEquipas));
  tabela->capacidade = capacidade * 2;
  tabela->tamanho = 0;
  tabela->equipas = malloc((sizeof(Equipa *)) * tabela->capacidade);
  for (i = 0; i < tabela->capacidade; i++)
    tabela->equipas[i] = 0;

  return tabela;
}

void expandir_equipas(TabelaEquipas *tabela);
void inserir_equipa(TabelaEquipas *tabela, Equipa *equipa)
{
  int i = hash(equipa->nome, tabela->capacidade);
  while (tabela->equipas[i] != 0)
    i = (i + 1) % tabela->capacidade;

  tabela->equipas[i] = equipa;
  tabela->tamanho++;
  if (tabela->tamanho > (tabela->capacidade / 2))
  {
    expandir_equipas(tabela);
  }
  else
  {
    
  }

}

void expandir_equipas(TabelaEquipas *tabela)
{
  int i;
  TabelaEquipas *tab = inicia_tabela_equipas(tabela->capacidade * 2);
  for (i = 0; i < tabela->capacidade; i++)
  {
    if (tabela->equipas[i] != 0)
    {
      inserir_equipa(tab, tabela->equipas[i]);
    }
    else
    {
      
    }

  }

  free(tabela->equipas);
  tabela->equipas = tab->equipas;
  tabela->capacidade = tab->capacidade;
  tabela->tamanho = tab->tamanho;
  free(tab);
}

Equipa *procura_equipa(TabelaEquipas *tabela, char *nome)
{
  int i = hash(nome, tabela->capacidade);
  while (tabela->equipas[i] != 0)
  {
    if (strcmp(tabela->equipas[i]->nome, nome) == 0)
    {
      return tabela->equipas[i];
    }
    else
    {
      i = (i + 1) % tabela->capacidade;
    }

  }

  return 0;
}

void free_tabela_equipas(TabelaEquipas *tabela)
{
  int i;
  for (i = 0; i < tabela->capacidade; i++)
  {
    if (tabela->equipas[i] != 0)
    {
      free(tabela->equipas[i]->nome);
      free(tabela->equipas[i]);
    }
    else
    {
      
    }

  }

  free(tabela->equipas);
  free(tabela);
}

void swap(char **a, char **b)
{
  char *temp = *a;
  *a = *b;
  *b = temp;
}

int partition(char **equipas, int left, int right)
{
  int i = left - 1;
  int j = right;
  char *v = equipas[right];
  while (i < j)
  {
    while (strcmp(equipas[++i], v) < 0)
      ;

    while (strcmp(v, equipas[--j]) < 0)
    {
      if (j == left)
      {
        break;
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      swap(&equipas[i], &equipas[j]);
    }
    else
    {
      
    }

  }

  if (strcmp(equipas[i], equipas[right]) > 0)
  {
    swap(&equipas[i], &equipas[right]);
  }
  else
  {
    
  }

  return i;
}

void ordena_equipas(char **equipas, int left, int right)
{
  int i;
  if (right <= left)
  {
    return;
  }
  else
  {
    
  }

  i = partition(equipas, left, right);
  ordena_equipas(equipas, left, i - 1);
  ordena_equipas(equipas, i + 1, right);
}

