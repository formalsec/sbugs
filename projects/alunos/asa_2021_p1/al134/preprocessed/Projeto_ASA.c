#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


int n_vertex;
int n_edges;
int dominoes_to_move = 0;
int longest_chain = 1;
typedef struct l link;
struct l
{
  int number;
  int longest_path;
  link *next;
};
link *vertexArray;
int *sourcesToFind;
int *sourcesToUse;
void addLink(int vertexNumber, link *vertex)
{
  link *inicial_vertex = &vertexArray[vertexNumber];
  int i;
  for (i = 0;; i++)
  {
    if (inicial_vertex->next == 0)
    {
      inicial_vertex->next = vertex;
      break;
    }
    else
    {
      inicial_vertex = inicial_vertex->next;
    }

  }

}

void readInput()
{
  if (2 == 2)
  {
    n_vertex = new_sym_var(sizeof(int) * 8);
    n_edges = new_sym_var(sizeof(int) * 8);
    vertexArray = malloc((sizeof(link)) * n_vertex);
    sourcesToFind = malloc((sizeof(int)) * n_vertex);
    if ((vertexArray == 0) || (sourcesToFind == 0))
    {
      exit(1);
    }
    else
    {
      
    }

  }
  else
  {
    printf("Failed to read integers.\n");
  }

  int i;
  for (i = 0; i < n_vertex; i++)
  {
    vertexArray[i].number = i + 1;
    vertexArray[i].next = 0;
    vertexArray[i].longest_path = 0;
    sourcesToFind[i] = 0;
  }

  for (i = 1; i <= n_edges; i++)
  {
    int vertex1;
    int vertex2;
    if (2 == 2)
    {
      vertex1 = new_sym_var(sizeof(int) * 8);
      vertex2 = new_sym_var(sizeof(int) * 8);
      link *vertex = malloc(sizeof(link));
      vertex->number = vertex2;
      vertex->next = 0;
      vertex->longest_path = 0;
      addLink(vertex1 - 1, vertex);
      sourcesToFind[vertex2 - 1]++;
    }
    else
    {
      printf("Failed to read integers.\n");
    }

  }

}

void findSources()
{
  int i;
  for (i = 0; i < n_vertex; i++)
  {
    if (sourcesToFind[i] == 0)
    {
      dominoes_to_move++;
      sourcesToUse = realloc(sourcesToUse, (sizeof(int)) * dominoes_to_move);
      sourcesToUse[dominoes_to_move - 1] = i + 1;
    }
    else
    {
      
    }

  }

}

void findLongestPath()
{
  int sourceToUse = dominoes_to_move;
  link *visited = malloc(sizeof(link));
  link vertex = vertexArray[sourcesToUse[sourceToUse - 1] - 1];
  int path;
  for (path = 0;;)
  {
    if ((path <= 0) && (vertex.next == 0))
    {
      if ((sourceToUse - 1) == 0)
      {
        break;
      }
      else
      {
        path = 0;
        sourceToUse--;
        vertex = vertexArray[sourcesToUse[sourceToUse - 1] - 1];
      }

    }
    else
    {
      if ((vertex.next == 0) || (path < vertex.longest_path))
      {
        if (longest_chain < (path + 1))
        {
          longest_chain = path + 1;
        }
        else
        {
          
        }

        vertex = visited[path - 1];
        visited = realloc(visited, (sizeof(link)) * path);
        path--;
      }
      else
      {
        vertex = *vertex.next;
        path++;
        visited = realloc(visited, (sizeof(link)) * path);
        visited[path - 1] = vertex;
        vertex = vertexArray[vertex.number - 1];
        vertexArray[vertex.number - 1].longest_path = path;
      }

    }

  }

}

int main()
{
  readInput();
  findSources();
  findLongestPath();
  printf("%d %d\n", dominoes_to_move, longest_chain);
  return 0;
}

