/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tables.h"


static int Nequipas;
static int Mequipas;
static int Njogos;
static int Mjogos;
static int sizeArrayE;
static int sizeArrayJ;
static equipa *tableEquipas;
static element *tableJogos;
static equipa *listaEquipas;
static jogo *listaJogos;
void tableEInit(int max)
{
  int i;
  Nequipas = 0;
  Mequipas = findPrime(2 * max);
  tableEquipas = malloc(Mequipas * (sizeof(equipa)));
  for (i = 0; i < Mequipas; i++)
  {
    tableEquipas[i] = 0;
  }

}

void tableJInit(int max)
{
  int i;
  Njogos = 0;
  Mjogos = findPrime(2 * max);
  tableJogos = malloc(Mjogos * (sizeof(element)));
  for (i = 0; i < Mjogos; i++)
  {
    tableJogos[i] = malloc(sizeof(struct element));
    tableJogos[i]->game = 0;
    tableJogos[i]->ocupado = 0;
  }

}

void initArrayE(int max)
{
  int i;
  sizeArrayE = 2 * max;
  listaEquipas = malloc(sizeArrayE * (sizeof(equipa)));
  for (i = 0; i < sizeArrayE; i++)
  {
    listaEquipas[i] = 0;
  }

}

void initArrayJ(int max)
{
  int i;
  sizeArrayJ = 2 * max;
  listaJogos = malloc(sizeArrayJ * (sizeof(jogo)));
  for (i = 0; i < sizeArrayJ; i++)
  {
    listaJogos[i] = 0;
  }

}

int hash1(char *v, int M)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

int hash2(char *v, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*v)) % M;
  }

  return h;
}

void insertArrayE(equipa e)
{
  listaEquipas[Nequipas] = e;
  if ((Nequipas + 1) > (sizeArrayE / 2))
  {
    expandArrayE();
  }
  else
  {
    
  }

}

int insertArrayJ(jogo e)
{
  listaJogos[Njogos] = e;
  if ((Njogos + 1) > (sizeArrayJ / 2))
  {
    expandArrayJ();
  }
  else
  {
    
  }

  return Njogos;
}

void tableEInsert(equipa a)
{
  char *name = a->name;
  int i = hash1(name, Mequipas);
  int k = hash2(name, Mequipas);
  while (tableEquipas[i] != 0)
  {
    if (i == ((i + k) % Mequipas))
    {
      expandTableE();
      i = hash1(name, Mequipas);
      k = hash2(name, Mequipas);
    }
    else
    {
      i = (i + k) % Mequipas;
    }

  }

  tableEquipas[i] = a;
  if ((Nequipas++) > (Mequipas / 2))
  {
    expandTableE();
  }
  else
  {
    
  }

}

void tableJInsert(jogo a, int pos)
{
  char *name = a->name;
  int i = hash1(name, Mjogos);
  int k = hash2(name, Mjogos);
  while (tableJogos[i]->game != 0)
  {
    if (i == ((i + k) % Mjogos))
    {
      expandTableJ();
      i = hash1(name, Mjogos);
      k = hash2(name, Mjogos);
    }
    else
    {
      i = (i + k) % Mjogos;
    }

  }

  tableJogos[i]->game = a;
  tableJogos[i]->ocupado = 1;
  tableJogos[i]->game->idNumber = pos;
  if ((Njogos++) > (Mjogos / 2))
  {
    expandTableJ();
  }
  else
  {
    
  }

}

equipa tableESearch(char *name)
{
  int i = hash1(name, Mequipas);
  int k = hash2(name, Mequipas);
  int aux = i;
  while (tableEquipas[i] != 0)
  {
    if (strcmp(name, tableEquipas[i]->name) == 0)
    {
      return tableEquipas[i];
    }
    else
    {
      
    }

    i = (i + k) % Mequipas;
    if (i == aux)
    {
      break;
    }
    else
    {
      
    }

  }

  return 0;
}

element tableJSearch(char *name)
{
  int i = hash1(name, Mjogos);
  int k = hash2(name, Mjogos);
  int aux = i;
  while (tableJogos[i]->ocupado != 0)
  {
    if ((tableJogos[i]->game != 0) && (strcmp(name, tableJogos[i]->game->name) == 0))
    {
      return tableJogos[i];
    }
    else
    {
      
    }

    i = (i + k) % Mjogos;
    if (i == aux)
    {
      break;
    }
    else
    {
      
    }

  }

  return 0;
}

void removeArrayJ(int pos)
{
  int i;
  if ((pos + 1) == Njogos)
  {
    listaJogos[pos] = 0;
  }
  else
  {
    for (i = pos; i < (Njogos - 1); i++)
    {
      listaJogos[i] = listaJogos[i + 1];
      listaJogos[i]->idNumber--;
    }

  }

}

void tableJDelete(jogo j)
{
  removeArrayJ(j->idNumber);
  if (j->r1 > j->r2)
  {
    removeVictory(j->equipa1);
  }
  else
  {
    
  }

  if (j->r2 > j->r1)
  {
    removeVictory(j->equipa2);
  }
  else
  {
    
  }

  Njogos--;
}

void printJogos(int linha)
{
  int i;
  for (i = 0; i < Njogos; i++)
  {
    printf("%d ", linha);
    printJogo(listaJogos[i]);
  }

}

void printEquipas(int linha, int n)
{
  int i;
  printf("%d Melhores %u\n", linha, listaEquipas[0]->victorys);
  for (i = 0; i < n; i++)
  {
    printf("%d * %s\n", linha, listaEquipas[i]->name);
  }

}

void freeArrayE()
{
  int i;
  for (i = 0; i < Nequipas; i++)
  {
    freeEquipa(listaEquipas[i]);
  }

  free(listaEquipas);
}

void freeArrayJ()
{
  int i;
  for (i = 0; i < Njogos; i++)
  {
    freeJogo(listaJogos[i]);
  }

  free(listaJogos);
}

void freeTableE()
{
  free(tableEquipas);
}

void freeTableJ()
{
  int i;
  for (i = 0; i < Mjogos; i++)
  {
    free(tableJogos[i]);
  }

  free(tableJogos);
}

int findPrime(int n)
{
  int i;
  int j;
  int flag = 0;
  for (i = n; i > 1; i--)
  {
    for (j = i / 2; j >= 1; j--)
    {
      if (((i % j) == 0) && (j != 1))
      {
        flag = 0;
        break;
      }
      else
      {
        flag = 1;
      }

    }

    if (flag == 1)
    {
      break;
    }
    else
    {
      
    }

  }

  return i;
}

void expandTableE()
{
  int i;
  int auxM = Mequipas;
  equipa *aux = tableEquipas;
  tableEInit(Mequipas + Mequipas);
  for (i = 0; i < auxM; i++)
  {
    if (aux[i] != 0)
    {
      tableEInsert(aux[i]);
    }
    else
    {
      
    }

  }

  free(aux);
}

void expandTableJ()
{
  int i;
  int auxM = Mjogos;
  element *aux = tableJogos;
  tableJInit(Mjogos + Mjogos);
  for (i = 0; i < auxM; i++)
  {
    if (aux[i]->game != 0)
    {
      tableJInsert(aux[i]->game, aux[i]->game->idNumber);
    }
    else
    {
      
    }

    free(aux[i]);
  }

  free(aux);
}

void expandArrayE()
{
  int i;
  int auxS = sizeArrayE;
  equipa *aux = listaEquipas;
  initArrayE(sizeArrayE + sizeArrayE);
  for (i = 0; i < auxS; i++)
  {
    if (aux[i] != 0)
    {
      listaEquipas[i] = aux[i];
    }
    else
    {
      
    }

  }

  free(aux);
}

void expandArrayJ()
{
  int i;
  int auxS = sizeArrayJ;
  jogo *aux = listaJogos;
  initArrayJ(sizeArrayJ + sizeArrayJ);
  for (i = 0; i < auxS; i++)
  {
    if (aux[i] != 0)
    {
      listaJogos[i] = aux[i];
    }
    else
    {
      
    }

  }

  free(aux);
}

int putBiggerOnTop()
{
  int i;
  int j = 1;
  equipa aux;
  unsigned int vit = listaEquipas[0]->victorys;
  for (i = 1; i < Nequipas; i++)
  {
    if (listaEquipas[i]->victorys > vit)
    {
      aux = listaEquipas[0];
      listaEquipas[0] = listaEquipas[i];
      listaEquipas[i] = aux;
      vit = listaEquipas[0]->victorys;
      j = 1;
    }
    else
    {
      
    }

    if ((listaEquipas[i]->victorys == vit) && (j != i))
    {
      aux = listaEquipas[j];
      listaEquipas[j] = listaEquipas[i];
      listaEquipas[i] = aux;
      j++;
    }
    else
    {
      
    }

    if ((listaEquipas[i]->victorys == vit) && (j == i))
    {
      j++;
    }
    else
    {
      
    }

  }

  return j;
}

void heapify(int n, int i)
{
  int largest = i;
  int left = (2 * i) + 1;
  int right = (2 * i) + 2;
  equipa aux;
  if ((left < n) && (strcmp(listaEquipas[left]->name, listaEquipas[largest]->name) > 0))
  {
    largest = left;
  }
  else
  {
    
  }

  if ((right < n) && (strcmp(listaEquipas[right]->name, listaEquipas[largest]->name) > 0))
  {
    largest = right;
  }
  else
  {
    
  }

  if (largest != i)
  {
    aux = listaEquipas[i];
    listaEquipas[i] = listaEquipas[largest];
    listaEquipas[largest] = aux;
    heapify(n, largest);
  }
  else
  {
    
  }

}

void heapsort(int n)
{
  int i;
  equipa aux;
  for (i = (n / 2) - 1; i >= 0; i--)
  {
    heapify(n, i);
  }

  for (i = n - 1; i >= 0; i--)
  {
    aux = listaEquipas[0];
    listaEquipas[0] = listaEquipas[i];
    listaEquipas[i] = aux;
    heapify(i, 0);
  }

}

int getNequipas()
{
  return Nequipas;
}

