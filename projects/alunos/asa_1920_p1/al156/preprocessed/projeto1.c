#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int *CriaVectorNotas(int tamanho)
{
  int *v;
  int i;
  int num;
  v = (int *) malloc(tamanho * (sizeof(int)));
  for (i = 0; i < tamanho; i++)
  {
    num = new_sym_var(sizeof(int) * 8);
    v[i] = num;
  }

  return v;
}

void freeRelaALun(int **v, int tamanho)
{
  int i = 0;
  for (i = 0; i < tamanho; i++)
  {
    free(v[i]);
  }

  free(v);
}

void printvector1(int *v, int tamanho)
{
  int i;
  for (i = 0; i < tamanho; i++)
  {
    printf("%d\n", v[i]);
  }

}

void percorreRela(int **r, int *a, int tamanho, int valor)
{
  int j;
  for (j = 0; j < tamanho; j++)
  {
    if ((r[j][valor] == 1) && (a[j] < a[valor]))
    {
      a[j] = a[valor];
      percorreRela(r, a, tamanho, j);
    }
    else
    {
      
    }

  }

}

void estudoNota(int **r, int *a, int numALunos)
{
  int i;
  int j;
  for (i = 0; i < numALunos; i++)
  {
    for (j = 0; j < numALunos; j++)
    {
      if ((r[i][j] == 1) && (a[i] < a[j]))
      {
        a[i] = a[j];
        percorreRela(r, a, numALunos, i);
      }
      else
      {
        
      }

    }

  }

  printvector1(a, numALunos);
}

int main()
{
  int num1;
  int num2;
  int i;
  int *notas;
  int **adj_matrix;
  int r;
  int c;
  int nodes;
  int numrel;
  nodes = new_sym_var(sizeof(int) * 8);
  numrel = new_sym_var(sizeof(int) * 8);
  adj_matrix = (int **) malloc((sizeof(int **)) * nodes);
  for (r = 0; r < nodes; r++)
  {
    adj_matrix[r] = (int *) malloc((sizeof(int)) * nodes);
  }

  for (r = 0; r < nodes; r++)
  {
    for (c = 0; c < nodes; c++)
    {
      adj_matrix[r][c] = 0;
    }

  }

  notas = CriaVectorNotas(nodes);
  for (i = 0; i < numrel; i++)
  {
    num1 = new_sym_var(sizeof(int) * 8);
    num2 = new_sym_var(sizeof(int) * 8);
    adj_matrix[num1 - 1][num2 - 1] = 1;
  }

  estudoNota(adj_matrix, notas, nodes);
  freeRelaALun(adj_matrix, nodes);
  free(notas);
  return 0;
}
