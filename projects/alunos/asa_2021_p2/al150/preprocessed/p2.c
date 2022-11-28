#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int n_v;
typedef struct Queue
{
  int front;
  int back;
  int size;
  int max_size;
  int *array;
} *Queue;
struct Queue *createQueue(int max_size)
{
  Queue queue = malloc(sizeof(struct Queue));
  queue->max_size = max_size;
  queue->front = (queue->size = 0);
  queue->back = max_size - 1;
  queue->array = (int *) malloc(queue->max_size * (sizeof(int)));
  return queue;
}

int isFull(struct Queue *queue)
{
  return queue->size == queue->max_size;
}

int isEmpty(struct Queue *queue)
{
  return queue->size == 0;
}

void addQueue(struct Queue *queue, int item)
{
  if (isFull(queue))
  {
    fprintf(stderr, "cant add, queue full\n");
    exit(1);
  }
  else
  {
    
  }

  queue->back = (queue->back + 1) % queue->max_size;
  queue->array[queue->back] = item;
  queue->size = queue->size + 1;
}

int removeQueue(struct Queue *queue)
{
  if (isEmpty(queue))
  {
    fprintf(stderr, "cant remove, queue empty\n");
    exit(1);
  }
  else
  {
    
  }

  int item = queue->array[queue->front];
  queue->front = (queue->front + 1) % queue->max_size;
  queue->size = queue->size - 1;
  return item;
}

int **newGraph(int num_v)
{
  int i;
  int **graph = malloc((sizeof(int *)) * num_v);
  for (i = 0; i < num_v; i++)
  {
    graph[i] = (int *) calloc(num_v, sizeof(int));
  }

  return graph;
}

void addEdge(int **graph, int v2, int v1, int capacity)
{
  graph[v2][v1] = capacity;
  graph[v1][v2] = capacity;
}

int min(int a, int b)
{
  if (a > b)
  {
    return b;
  }
  else
  {
    return a;
  }

}

int **processInput()
{
  int num_proc;
  int num_coms;
  int c_X;
  int c_Y;
  int v1;
  int v2;
  int cap;
  int num_args = 2;
  num_proc = new_sym_var(sizeof(int) * 8);
  num_coms = new_sym_var(sizeof(int) * 8);
  if (((num_args != 2) || (num_proc < 2)) || (num_coms < 0))
  {
    printf("bad args 1\n");
    exit(1);
  }
  else
  {
    
  }

  n_v = num_proc + 2;
  int **graph = newGraph(n_v);
  int i;
  for (i = 0; i < num_proc; i++)
  {
    int num_args = 2;
    c_X = new_sym_var(sizeof(int) * 8);
    c_Y = new_sym_var(sizeof(int) * 8);
    if (num_args != 2)
    {
      printf("bad args 2\n");
      exit(1);
    }
    else
    {
      
    }

    addEdge(graph, 0, i + 1, c_X);
    addEdge(graph, n_v - 1, i + 1, c_Y);
  }

  for (i = 0; i < num_coms; i++)
  {
    int num_args = 3;
    v1 = new_sym_var(sizeof(int) * 8);
    v2 = new_sym_var(sizeof(int) * 8);
    cap = new_sym_var(sizeof(int) * 8);
    if (num_args != 3)
    {
      printf("bad args 3\n");
      exit(1);
    }
    else
    {
      
    }

    addEdge(graph, v1, v2, cap);
  }

  return graph;
}

int bfs(int **res_graph, int s, int t, int *p_list)
{
  int *visited_list = (int *) calloc(n_v, sizeof(int));
  Queue queue = createQueue(n_v);
  addQueue(queue, s);
  visited_list[s] = 1;
  p_list[s] = -1;
  while (!isEmpty(queue))
  {
    int u = removeQueue(queue);
    int v;
    for (v = 0; v < n_v; v++)
    {
      if ((visited_list[v] == 0) && (res_graph[u][v] > 0))
      {
        if (v == t)
        {
          p_list[v] = u;
          return 1;
        }
        else
        {
          
        }

        addQueue(queue, v);
        p_list[v] = u;
        visited_list[v] = 1;
      }
      else
      {
        
      }

    }

  }

  return 0;
}

void fordFulkerson(int **graph, int s, int t)
{
  int u;
  int v;
  int **res_graph = newGraph(n_v);
  for (u = 0; u < n_v; u++)
    for (v = 0; v < n_v; v++)
  {
    res_graph[u][v] = graph[u][v];
    res_graph[v][u] = graph[u][v];
  }


  int *p_list = (int *) calloc(n_v, sizeof(int));
  int max_flux = 0;
  while (bfs(res_graph, s, t, p_list))
  {
    int path_flux = 1000000;
    for (v = t; v != s; v = p_list[v])
    {
      u = p_list[v];
      path_flux = min(path_flux, res_graph[u][v]);
    }

    for (v = t; v != s; v = p_list[v])
    {
      u = p_list[v];
      res_graph[u][v] -= path_flux;
      res_graph[v][u] += path_flux;
    }

    max_flux += path_flux;
  }

  printf("%d\n", max_flux);
}

int main(int agrc, char *argv[])
{
  int **grafo = processInput();
  fordFulkerson(grafo, 0, n_v - 1);
  return 0;
}
