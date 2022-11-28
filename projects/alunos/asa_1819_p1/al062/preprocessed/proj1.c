#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct Item
{
  int n;
  struct Item *prev;
  struct Item *next;
} Item;
Item criaitem(int n)
{
  Item nitem;
  nitem.n = n;
  nitem.prev = 0;
  nitem.next = 0;
  return nitem;
}

void incertitem(Item *item0, Item *insertable)
{
  Item *temporaryi = item0;
  if (item0->next == 0)
  {
    insertable->prev = item0;
    item0->next = insertable;
  }
  else
  {
    while ((temporaryi->next != 0) && (temporaryi->next->n < insertable->n))
    {
      temporaryi = temporaryi->next;
      ;
    }

    if (temporaryi->next == 0)
    {
      temporaryi->prev->next->next = insertable;
      insertable->prev = temporaryi->prev->next;
      return;
    }
    else
    {
      if (temporaryi->n == 0)
      {
        temporaryi->next->prev = insertable;
        insertable->next = item0->next;
        insertable->prev = item0;
        item0->next = insertable;
        return;
      }
      else
      {
        temporaryi->next->prev = insertable;
        insertable->next = temporaryi->prev->next->next;
        insertable->prev = temporaryi->prev->next;
        temporaryi->prev->next->next = insertable;
      }

    }

  }

}

void DFSvisiter(int **matriz, int i, int *nofwhiterouters, int *wrouters, Item *biguest)
{
  wrouters[i] = 1;
  int j;
  for (j = 1; j < matriz[i][0]; j++)
  {
    if (wrouters[matriz[i][j] - 1] == 0)
    {
      DFSvisiter(matriz, matriz[i][j] - 1, nofwhiterouters, wrouters, biguest);
    }
    else
    {
      
    }

  }

  wrouters[i] = 2;
  if (biguest->n < (i + 1))
  {
    biguest->n = i + 1;
  }
  else
  {
    
  }

  *nofwhiterouters = (*nofwhiterouters) - 1;
}

int subnetsnumber(int routers, int **matriz, Item *x)
{
  int subnetnumber = 1;
  int i;
  int *nofwhiterouters = (int *) malloc(sizeof(int));
  *nofwhiterouters = routers;
  int wrouters[routers];
  for (i = 0; i < routers; i++)
    wrouters[i] = 0;

  for (i = 0; i < routers; i++)
  {
    if (wrouters[i] == 0)
    {
      Item *correntitem = (Item *) malloc(sizeof(Item));
      *correntitem = criaitem(i + 1);
      DFSvisiter(matriz, i, nofwhiterouters, wrouters, correntitem);
      incertitem(x, correntitem);
      if ((*nofwhiterouters) != 0)
      {
        subnetnumber++;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  free(nofwhiterouters);
  return subnetnumber;
}

void DFSmissigALL(int routers, int **matriz, int i, int *listTOoff, int *nofwhiterouters, int *routerspercorridos)
{
  listTOoff[i] = 1;
  int j;
  for (j = 1; j < matriz[i][0]; j++)
  {
    if (listTOoff[matriz[i][j] - 1] == 0)
    {
      DFSmissigALL(routers, matriz, matriz[i][j] - 1, listTOoff, nofwhiterouters, routerspercorridos);
    }
    else
    {
      
    }

  }

  *routerspercorridos = (*routerspercorridos) + 1;
  listTOoff[i] = 2;
  *nofwhiterouters = (*nofwhiterouters) - 1;
}

int subnetmissingall(int routers, int **matriz, int NdeOFFrouters, int *listTOoff)
{
  int bigssubnetrouters = 0;
  int i;
  int *nofwhiterouters = (int *) malloc(sizeof(int));
  *nofwhiterouters = routers - NdeOFFrouters;
  int *routerspercorridos = (int *) malloc(sizeof(int));
  for (i = 0; i < routers; i++)
  {
    if (listTOoff[i] == 0)
    {
      *routerspercorridos = 0;
      DFSmissigALL(routers, matriz, i, listTOoff, nofwhiterouters, routerspercorridos);
      if (bigssubnetrouters < (*routerspercorridos))
      {
        bigssubnetrouters = *routerspercorridos;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  free(nofwhiterouters);
  free(routerspercorridos);
  return bigssubnetrouters;
}

void breakingvisit(int vertice, int *visited, int *div, int *l, int *pais, int *offLIST, int *time, int **matriz)
{
  int filhos = 0;
  int i;
  visited[vertice] = 1;
  *time = (*time) + 1;
  div[vertice] = *time;
  l[vertice] = *time;
  for (i = 1; i < matriz[vertice][0]; i++)
  {
    int v = matriz[vertice][i] - 1;
    if (visited[v] == 0)
    {
      filhos++;
      pais[v] = vertice;
      breakingvisit(v, visited, div, l, pais, offLIST, time, matriz);
      if (l[vertice] >= l[v])
      {
        l[vertice] = l[v];
      }
      else
      {
        
      }

      if ((pais[vertice] == (-1)) && (filhos > 1))
      {
        offLIST[vertice] = 3;
      }
      else
      {
        
      }

      if ((pais[vertice] != (-1)) && (l[v] >= div[vertice]))
      {
        offLIST[vertice] = 3;
      }
      else
      {
        
      }

    }
    else
    {
      if (v != pais[vertice])
      {
        if (l[vertice] >= div[v])
        {
          l[vertice] = div[v];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

}

void get_breaking_routers(int routers, int *offLIST, int **matriz)
{
  int i;
  int abselutetime = 0;
  int div[routers];
  int l[routers];
  int visited[routers];
  int pais[routers];
  for (i = 0; i < routers; i++)
  {
    div[i] = 0;
    l[i] = 32767;
    visited[i] = 0;
    pais[i] = -1;
  }

  for (i = 0; i < routers; i++)
  {
    if (visited[i] == 0)
    {
      breakingvisit(i, &visited[0], &div[0], &l[0], &pais[0], offLIST, &abselutetime, matriz);
    }
    else
    {
      
    }

  }

}

int main()
{
  int routers;
  int connectors;
  int i;
  int con1;
  int con2;
  int **matriz;
  int originalsub;
  int breakingrouter = 0;
  Item *x = (Item *) malloc(sizeof(Item));
  *x = criaitem(0);
  routers = new_sym_var(sizeof(int) * 8);
  connectors = new_sym_var(sizeof(int) * 8);
  matriz = (int **) malloc(routers * (sizeof(int *)));
  for (i = 0; i < routers; i++)
  {
    matriz[i] = (int *) malloc(sizeof(int));
    matriz[i][0] = 1;
  }

  for (i = 0; i < connectors; i++)
  {
    con1 = new_sym_var(sizeof(int) * 8);
    con2 = new_sym_var(sizeof(int) * 8);
    matriz[con1 - 1][0]++;
    matriz[con1 - 1] = (int *) realloc(matriz[con1 - 1], (sizeof(int)) * matriz[con1 - 1][0]);
    matriz[con1 - 1][matriz[con1 - 1][0] - 1] = con2;
    matriz[con2 - 1][0]++;
    matriz[con2 - 1] = (int *) realloc(matriz[con2 - 1], (sizeof(int)) * matriz[con2 - 1][0]);
    matriz[con2 - 1][matriz[con2 - 1][0] - 1] = con1;
  }

  originalsub = subnetsnumber(routers, matriz, x);
  printf("%d\n", originalsub);
  Item *printitem = x->next;
  while (printitem->next != 0)
  {
    printf("%d ", printitem->n);
    printitem = printitem->next;
  }

  printf("%d\n", printitem->n);
  while (printitem->prev != 0)
  {
    printitem = printitem->prev;
    free(printitem->next);
  }

  int offLIST[routers];
  for (i = 0; i < routers; i++)
    offLIST[i] = 0;

  get_breaking_routers(routers, &offLIST[0], matriz);
  int count = 0;
  for (i = 0; i < routers; i++)
  {
    if (offLIST[i] == 3)
    {
      count++;
    }
    else
    {
      
    }

  }

  breakingrouter = count;
  printf("%d\n", count);
  printf("%d\n", subnetmissingall(routers, matriz, breakingrouter, offLIST));
  free(x);
  for (i = 0; i < routers; i++)
  {
    free(matriz[i]);
  }

  free(matriz);
  return 0;
}
