/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node
{
  int value;
  int done;
  int num_conections;
  int size;
  int *conections;
} node;
node **graph;
int *graph_val;
int stack_size;
int previous_size;
int min_val;
int current_index = 0;
void initinalizeGraph(int *N)
{
  graph = calloc(*N, sizeof(node));
}

node *createNode(int *val, int *N)
{
  node *dummy = malloc(sizeof(struct node));
  dummy->value = *val;
  dummy->done = 1;
  dummy->num_conections = 0;
  if ((*N) < 50)
  {
    dummy->conections = malloc((sizeof(int)) * (*N));
    dummy->size = *N;
  }
  else
  {
    dummy->conections = malloc((sizeof(int)) * 50);
    dummy->size = 50;
  }

  return dummy;
}

int parseArgs(int *N, int *M)
{
  int i;
  int *val;
  int *father_node;
  int *son_node;
  int pos = 0;
  int key = 0;
  int conects;
  val = malloc(sizeof(int));
  father_node = malloc(sizeof(int));
  son_node = malloc(sizeof(int));
  for (int N_index = 0; N_index < 10; N_index++)
  {
    N[N_index] = new_sym_var(sizeof(int) * 8);
  }

  for (int M_index = 0; M_index < 10; M_index++)
  {
    M[M_index] = new_sym_var(sizeof(int) * 8);
  }

  stack_size = *N;
  initinalizeGraph(N);
  graph_val = calloc(21, sizeof(int));
  for (i = 0; i < (*N); i++)
  {
    for (int val_index = 0; val_index < 10; val_index++)
    {
      val[val_index] = new_sym_var(sizeof(int) * 8);
    }

    graph_val[*val] = 1;
    if ((*val) > key)
    {
      key = *val;
      pos = i;
    }
    else
    {
      
    }

    if ((*val) < min_val)
    {
      min_val = *val;
    }
    else
    {
      
    }

    graph[i] = createNode(val, N);
  }

  for (i = 0; i < (*M); i++)
  {
    for (int son_node_index = 0; son_node_index < 10; son_node_index++)
    {
      son_node[son_node_index] = new_sym_var(sizeof(int) * 8);
    }

    for (int father_node_index = 0; father_node_index < 10; father_node_index++)
    {
      father_node[father_node_index] = new_sym_var(sizeof(int) * 8);
    }

    conects = graph[(*father_node) - 1]->num_conections;
    if (conects == (graph[(*father_node) - 1]->size - 1))
    {
      graph[(*father_node) - 1]->conections = realloc(graph[(*father_node) - 1]->conections, (sizeof(int)) * (conects + 50));
      graph[(*father_node) - 1]->size += 50;
    }
    else
    {
      
    }

    graph[(*father_node) - 1]->conections[conects] = (*son_node) - 1;
    graph[(*father_node) - 1]->num_conections++;
  }

  free(val);
  free(father_node);
  free(son_node);
  return pos;
}

int min(int a, int b)
{
  return (a > b) ? (b) : (a);
}

void propagate(int u)
{
  int v;
  int i;
  int max_connections;
  max_connections = graph[u]->num_conections;
  graph[u]->done = 0;
  for (i = 0; i < max_connections; i++)
  {
    v = graph[u]->conections[i];
    if (graph[v]->done == 1)
    {
      if (graph[u]->value > graph[v]->value)
      {
        graph[v]->value = graph[u]->value;
      }
      else
      {
        
      }

      propagate(v);
    }
    else
    {
      
    }

  }

  stack_size--;
}

void free_all(int *N)
{
  int i;
  for (i = 0; i < (*N); i++)
  {
    free(graph[i]->conections);
    free(graph[i]);
  }

  free(graph);
  free(graph_val);
}

int main(int argc, const char *argv[])
{
  int i;
  int big_node;
  int max_val;
  int e;
  int *N;
  int *M;
  N = malloc(sizeof(int));
  M = malloc(sizeof(int));
  big_node = parseArgs(N, M);
  max_val = graph[big_node]->value;
  propagate(big_node);
  for (i = max_val; i >= min_val; i--)
  {
    if (graph_val[i] == 1)
    {
      for (e = 0; e < (*N); e++)
      {
        if ((graph[e]->value == i) && (graph[e]->done == 1))
        {
          propagate(e);
        }
        else
        {
          
        }

        if (stack_size == 0)
        {
          break;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

    if (stack_size == 0)
    {
      break;
    }
    else
    {
      
    }

  }

  for (i = 0; i < (*N); i++)
  {
    printf("%d\n", graph[i]->value);
  }

  free(M);
  free_all(N);
  free(N);
  return 0;
}

