/*File generated by PreProcessor.py*/


#include "hashtableEquipa.h"
#include <stdlib.h>
#include <string.h>


int hashEquipa(char *str, int m)
{
  int key = 0;
  unsigned int i;
  for (i = 0; i < strlen(str); ++i)
  {
    key = key + str[i];
  }

  key = key % m;
  return key;
}

char *keyEquipa(ItemEquipa item)
{
  return item->nomeEquipa;
}

void initEquipa(int m)
{
  int i;
  headsEquipa = (NodeEquipa **) malloc(m * (sizeof(NodeEquipa *)));
  for (i = 0; i < m; i++)
    headsEquipa[i] = 0;

}

void insertEquipa(int tamHashEquipa, ItemEquipa item)
{
  int i = hashEquipa(keyEquipa(item), tamHashEquipa);
  NodeEquipa *newNodeE = (NodeEquipa *) malloc(sizeof(NodeEquipa));
  newNodeE->item = item;
  newNodeE->next = headsEquipa[i];
  headsEquipa[i] = newNodeE;
}

ItemEquipa searchEquipa(int tamHashEquipa, char *text)
{
  NodeEquipa *head = 0;
  NodeEquipa *t = 0;
  int i = hashEquipa(text, tamHashEquipa);
  head = headsEquipa[i];
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->item->nomeEquipa, text) == 0)
    {
      return t->item;
    }
    else
    {
      
    }

  }

  return 0;
}

void deleteTudoE(int i)
{
  NodeEquipa *head;
  NodeEquipa *prev = 0;
  NodeEquipa *aux;
  head = headsEquipa[i];
  if (head != 0)
  {
    {
      aux = head->next;
      while (aux != 0)
      {
        prev = aux;
        aux = aux->next;
        free(prev->item->nomeEquipa);
        free(prev->item);
        free(prev);
      }

      free(headsEquipa[i]->item->nomeEquipa);
      free(headsEquipa[i]->item);
      free(headsEquipa[i]);
    }
  }
  else
  {
    
  }

}

void deleteHeadsE()
{
  free(headsEquipa);
}

ItemEquipa *HashToArrayEquipa(int tamHashEquipa, int contadorEquipas)
{
  ItemEquipa *array = 0;
  int i;
  int j = 0;
  NodeEquipa *head;
  array = (ItemEquipa *) malloc((sizeof(ItemEquipa)) * contadorEquipas);
  for (i = 0; i < contadorEquipas; i++)
    array[i] = 0;

  for (i = 0; i < tamHashEquipa; ++i)
  {
    head = headsEquipa[i];
    while (head != 0)
    {
      array[j] = head->item;
      head = head->next;
      ++j;
    }

  }

  return array;
}

void chk_hashtableEquipa(int *tamHashEquipa, int contadorEquipas)
{
  int prev = *tamHashEquipa;
  ItemEquipa *array;
  NodeEquipa *headEquipa;
  NodeEquipa *aux;
  int i;
  array = HashToArrayEquipa(*tamHashEquipa, contadorEquipas);
  for (i = 0; i < prev; ++i)
  {
    headEquipa = headsEquipa[i];
    while (headEquipa != 0)
    {
      aux = headEquipa->next;
      free(headEquipa);
      headEquipa = aux;
    }

  }

  free(headsEquipa);
  *tamHashEquipa = (*tamHashEquipa) + 500;
  initEquipa(*tamHashEquipa);
  for (i = 0; i < contadorEquipas; ++i)
  {
    insertEquipa(*tamHashEquipa, array[i]);
  }

  free(array);
}

