/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
  int **Fluxo;
  int **Com;
  int *visitado;
  int *path;
} MatrixProcessos;
MatrixProcessos matriz;
int processos;
int comunicacoes;
int raiz_matriz;
int cauda;
int cabeca;
int solucao;
int *Fila;
int min(int x, int y)
{
  return (x < y) ? (x) : (y);
}

void inicializa(int i, int val1, int val2, int val3, int flag)
{
  if (flag == 0)
  {
    matriz.Com[processos + 1][i + 1] = val2;
    matriz.Com[i + 1][processos + 1] = val2;
    matriz.Com[0][i + 1] = val1;
    matriz.Com[i + 1][0] = val1;
  }
  else
  {
    matriz.Com[val2][val1] = val3;
    matriz.Com[val1][val2] = val3;
  }

}

void freememoria()
{
  int i = 0;
  for (i = 0; i < raiz_matriz; i++)
  {
    free(matriz.Fluxo[i]);
    free(matriz.Com[i]);
  }

  free(matriz.Fluxo);
  free(matriz.Com);
  free(matriz.visitado);
  free(matriz.path);
  free(Fila);
}

int bfs_algorithm(int a, int b)
{
  int i;
  int j;
  for (i = 0; i < raiz_matriz; i++)
    matriz.visitado[i] = 0;

  cauda = 0;
  cabeca = cauda;
  Fila[cauda] = a;
  matriz.visitado[a] = 1;
  cauda++;
  matriz.path[a] = -1;
  while (cabeca != cauda)
  {
    i = Fila[cabeca];
    matriz.visitado[i] = 2;
    cabeca++;
    for (j = 0; j < raiz_matriz; j++)
    {
      if ((matriz.visitado[j] == 0) && ((matriz.Com[i][j] - matriz.Fluxo[i][j]) > 0))
      {
        Fila[cauda] = j;
        matriz.visitado[j] = 1;
        cauda++;
        matriz.path[j] = i;
      }
      else
      {
        
      }

    }

  }

  return matriz.visitado[b] == 2;
}

int ff_algorithm(int source, int sink)
{
  int i;
  int j;
  int p;
  int fluxomax = 0;
  for (i = 0; i < raiz_matriz; i++)
  {
    for (j = 0; j < raiz_matriz; j++)
      matriz.Fluxo[i][j] = 0;

  }

  while (bfs_algorithm(source, sink))
  {
    int incr = 1000000000;
    for (p = processos + 1; matriz.path[p] >= 0; p = matriz.path[p])
      incr = min(incr, matriz.Com[matriz.path[p]][p] - matriz.Fluxo[matriz.path[p]][p]);

    for (p = processos + 1; matriz.path[p] >= 0; p = matriz.path[p])
    {
      matriz.Fluxo[matriz.path[p]][p] += incr;
      matriz.Fluxo[p][matriz.path[p]] -= incr;
    }

    fluxomax += incr;
  }

  return fluxomax;
}

int main()
{
  int val_X;
  int val_Y;
  int i = 0;
  int j = 0;
  int l = 0;
  int m = 0;
  int o = 0;
  int val1;
  int val2;
  int val3;
  if (2 == 2)
  {
    processos = new_sym_var(sizeof(int) * 8);
    comunicacoes = new_sym_var(sizeof(int) * 8);
    if ((processos == 0) && (comunicacoes == 0))
    {
      printf("0\n");
      return 0;
    }
    else
    {
      if ((processos == 1) && (comunicacoes == 0))
      {
        if (2 == 2)
        {
          val_X = new_sym_var(sizeof(int) * 8);
          val_Y = new_sym_var(sizeof(int) * 8);
          if (val_X < val_Y)
          {
            printf("%d\n", val_X);
            return 0;
          }
          else
          {
            printf("%d\n", val_Y);
            return 0;
          }

        }
        else
        {
          return 1;
        }

      }
      else
      {
        if ((processos < 2) || (comunicacoes < 0))
        {
          return 1;
        }
        else
        {
          
        }

      }

    }

    raiz_matriz = processos + 2;
    Fila = malloc((sizeof(int)) * raiz_matriz);
    matriz.Com = malloc((sizeof(int *)) * raiz_matriz);
    matriz.Fluxo = malloc((sizeof(int *)) * raiz_matriz);
    for (i = 0; i < raiz_matriz; i++)
    {
      matriz.Fluxo[i] = malloc((sizeof(int)) * raiz_matriz);
      matriz.Com[i] = malloc((sizeof(int)) * raiz_matriz);
    }

    for (j = 0; j < raiz_matriz; j++)
    {
      for (l = 0; l < raiz_matriz; l++)
        matriz.Com[j][l] = 0;

    }

    for (m = 0; m < processos; m++)
    {
      if (2 == 2)
      {
        val1 = new_sym_var(sizeof(int) * 8);
        val2 = new_sym_var(sizeof(int) * 8);
        inicializa(m, val1, val2, 0, 0);
      }
      else
      {
        
      }

    }

    for (o = 0; o < comunicacoes; o++)
    {
      if (3 == 3)
      {
        val1 = new_sym_var(sizeof(int) * 8);
        val2 = new_sym_var(sizeof(int) * 8);
        val3 = new_sym_var(sizeof(int) * 8);
        inicializa(o, val1, val2, val3, 1);
      }
      else
      {
        
      }

    }

    matriz.visitado = malloc((sizeof(int)) * raiz_matriz);
    matriz.path = malloc((sizeof(int)) * raiz_matriz);
    solucao = ff_algorithm(0, processos + 1);
    freememoria();
    printf("%d\n", solucao);
    return 0;
  }
  else
  {
    return 1;
  }

}

