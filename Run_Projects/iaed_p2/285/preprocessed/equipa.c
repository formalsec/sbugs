/*File generated by PreProcessor.py*/


#include "equipa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int procura_indice_equipas(Equipa *Hashtable, char *nome, int tamanho_Hashtable)
{
  int indice;
  indice = hash(nome, tamanho_Hashtable);
  while (Hashtable[indice] != 0)
  {
    if (strcmp(Hashtable[indice]->Nome, nome) == 0)
    {
      {
        return indice;
      }
    }
    else
    {
      {
        indice = (indice + 1) % tamanho_Hashtable;
      }
    }

  }

  return -1;
}

int equipa_nova(char *nome, Equipa *Hashtable, int tamanho_Hashtable)
{
  int Indice = hash(nome, tamanho_Hashtable);
  while (Hashtable[Indice] != 0)
  {
    if (strcmp(Hashtable[Indice]->Nome, nome) == 0)
    {
      {
        return 1;
      }
    }
    else
    {
      
    }

    Indice = (Indice + 1) % tamanho_Hashtable;
  }

  return 0;
}

Equipa nova_equipa(char *nome)
{
  Equipa nova = (Equipa) malloc(sizeof(struct equipa));
  nova->Nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(nova->Nome, nome);
  nova->Vitorias = 0;
  return nova;
}

int procura_equipa(Equipa *Hashtable, int tamanho_Hashtable, int NL)
{
  int indice;
  char nome[1024];
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  indice = procura_indice_equipas(Hashtable, nome, tamanho_Hashtable);
  if (indice != (-1))
  {
    {
      printf("%d %s %d\n", NL, Hashtable[indice]->Nome, Hashtable[indice]->Vitorias);
      return 0;
    }
  }
  else
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return 0;
    }
  }

}

int verifica_equipas(char *equipa1, char *equipa2, Equipa *Hashtable, int tamanho_Hashtable)
{
  int Indice1 = procura_indice_equipas(Hashtable, equipa1, tamanho_Hashtable);
  int Indice2 = procura_indice_equipas(Hashtable, equipa2, tamanho_Hashtable);
  if ((Indice1 != (-1)) && (Indice2 != (-1)))
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  return 1;
}

Lista_Equipas insere_lista_equipas(Lista_Equipas lista, Equipa equipa1)
{
  Lista_Equipas variavel = (Lista_Equipas) malloc(sizeof(struct lista_equipas));
  variavel->equipa = equipa1;
  variavel->next = lista;
  return variavel;
}

int print_lista_equipas(Lista_Equipas lista, int NL)
{
  int Max = 0;
  int contador = 0;
  int indice;
  Lista_Equipas variavel;
  Lista_Equipas melhores = 0;
  char **arr;
  char **arr2;
  if (lista == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  for (variavel = lista; variavel != 0; variavel = variavel->next)
  {
    if (variavel->equipa->Vitorias > Max)
    {
      {
        Max = variavel->equipa->Vitorias;
      }
    }
    else
    {
      
    }

  }

  for (variavel = lista; variavel != 0; variavel = variavel->next)
  {
    if (variavel->equipa->Vitorias == Max)
    {
      {
        melhores = insere_lista_equipas(melhores, variavel->equipa);
        contador++;
      }
    }
    else
    {
      
    }

  }

  arr = cria_array(melhores, contador);
  arr2 = cria_array(melhores, contador);
  mergesort(arr, 0, contador - 1, arr2);
  printf("%d Melhores %d\n", NL, Max);
  for (indice = 0; indice < contador; indice++)
  {
    printf("%d * %s\n", NL, arr[indice]);
  }

  while (melhores)
  {
    variavel = melhores;
    melhores = melhores->next;
    free(variavel);
  }

  free(arr);
  free(arr2);
  return 0;
}

char **cria_array(Lista_Equipas melhores, int contador)
{
  char **arr = malloc((sizeof(char *)) * contador);
  int indice;
  for (indice = 0; indice < contador; indice++)
  {
    arr[indice] = melhores->equipa->Nome;
    melhores = melhores->next;
  }

  return arr;
}

void mergesort(char **arr, int l, int r, char **arr2)
{
  int meio = (r + l) / 2;
  if (r <= l)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  mergesort(arr, l, meio, arr2);
  mergesort(arr, meio + 1, r, arr2);
  merge(arr, l, meio, r, arr2);
}

void merge(char **arr, int l, int m, int r, char **arr2)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
  {
    arr2[i - 1] = arr[i - 1];
  }

  for (j = m; j < r; j++)
  {
    arr2[(r + m) - j] = arr[j + 1];
  }

  for (k = l; k <= r; k++)
  {
    if (strcmp(arr2[j], arr2[i]) < 0)
    {
      {
        arr[k] = arr2[j--];
      }
    }
    else
    {
      {
        arr[k] = arr2[i++];
      }
    }

  }

}

int free_equipas(Lista_Equipas lista)
{
  Lista_Equipas variavel;
  if (lista == 0)
  {
    {
      free(lista);
      return 0;
    }
  }
  else
  {
    
  }

  while (lista)
  {
    variavel = lista;
    lista = lista->next;
    free(variavel->equipa->Nome);
    free(variavel->equipa);
    free(variavel);
  }

  return 0;
}

