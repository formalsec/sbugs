#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void displayUsage(const char *appName)
{
  printf("Usage: %s\n", appName);
  exit(1);
}

static int *parseArgs(long argc, char *argv[])
{
  static int args[2];
  argv[1][strlen(argv[1]) - 1] = '\0';
  args[0] = atoi(argv[1]);
  args[1] = atoi(argv[2]);
  if (argc != (2 + 1))
  {
    fprintf(stderr, "Invalid number of arguments: ");
    displayUsage(argv[0]);
  }
  else
  {
    
  }

  if ((args[0] < 2) || (args[1] < 1))
  {
    fprintf(stderr, "NOTE: Arg1 > 2 and Arg2 > 1: ");
    displayUsage(argv[0]);
  }
  else
  {
    
  }

  return args;
}

int DFS_visit(int n, int *notas, int *estado, int matriz_adj[n][n], int vertice)
{
  int i;
  estado[vertice] = 1;
  for (i = 0; i < n; i++)
  {
    if ((matriz_adj[vertice][i] == 1) && (estado[i] == 0))
    {
      DFS_visit(n, notas, estado, matriz_adj, i);
      if (notas[vertice] < notas[i])
      {
        notas[vertice] = notas[i];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  estado[1] = 2;
  return notas[vertice];
}

int main(int argc, char *argv[])
{
  int *args = parseArgs(argc, argv);
  int notas[args[0]];
  int estado[args[0]];
  int matriz_adj[args[0]][args[0]];
  int aluno;
  int amigo;
  int i;
  int j;
  for (i = 0; i < args[0]; i++)
  {
    notas[i] = new_sym_var(sizeof(int) * 8);
    estado[i] = 0;
    for (j = 0; j < args[0]; j++)
      matriz_adj[i][j] = 0;

  }

  for (i = 0; i < args[1]; i++)
  {
    aluno = new_sym_var(sizeof(int) * 8);
    amigo = new_sym_var(sizeof(int) * 8);
    matriz_adj[aluno - 1][amigo - 1] = 1;
  }

  for (i = 0; i < args[0]; i++)
  {
    if (estado[i] == 0)
    {
      DFS_visit(args[0], notas, estado, matriz_adj, i);
    }
    else
    {
      
    }

  }

  for (i = 0; i < args[0]; i++)
  {
    printf("%d\n", notas[i]);
  }

  return 0;
}
