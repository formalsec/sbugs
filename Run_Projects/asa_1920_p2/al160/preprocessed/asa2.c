/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int result = 0;
typedef struct 
{
  int *node;
  int in;
  int out;
} queue;
int bfs(int **graph, int *cits, int *sups, queue *q, int *parent, int num_sup, int num_cit, int n, int num_st, int num_av);
void edmondsKarp(int **graph, int *cits, int *sups, int num_sup, int num_cit, int n, int num_st, int num_av);
void enqueue(queue *q, int node);
int dequeue(queue *q);
int empty(queue *q);
int ind(int av, int st, int num_st);
int relativeInd(int node, int adj, int num_st, int num_av);
int graphInd(int node, int adj, int num_st, int num_av);
int **initializeGraph(int num_av, int num_st);
int *initializeCitLocations(int n, int num_st);
int *initializeSupLocations(int n, int num_st);
void freeGraph(int **g, int n);
int main()
{
  int num_av;
  int num_st;
  int num_sup;
  int num_cit;
  int **graph;
  int *cits;
  int *sups;
  num_av = new_sym_var(sizeof(int) * 8);
  num_st = new_sym_var(sizeof(int) * 8);
  num_sup = new_sym_var(sizeof(int) * 8);
  num_cit = new_sym_var(sizeof(int) * 8);
  sups = initializeSupLocations(num_sup, num_st);
  cits = initializeCitLocations(num_cit, num_st);
  graph = initializeGraph(num_av, num_st);
  edmondsKarp(graph, cits, sups, num_sup, num_cit, (num_av * num_st) * 2, num_st, num_av);
  free(sups);
  free(cits);
  freeGraph(graph, (2 * num_av) * num_st);
  printf("%d\n", result);
  return 0;
}

int bfs(int **graph, int *cits, int *sups, queue *q, int *parent, int num_sup, int num_cit, int n, int num_st, int num_av)
{
  int i;
  int t;
  int currentNode;
  int next = -1;
  q->in = -1;
  q->out = -1;
  for (i = 0; i < n; i++)
    parent[i] = -1;

  for (i = 0; i < num_cit; i++)
  {
    parent[cits[i]] = -2;
    if (graph[cits[i]][4] == 1)
    {
      enqueue(q, cits[i]);
    }
    else
    {
      
    }

  }

  while (!empty(q))
  {
    currentNode = dequeue(q);
    for (i = 0; i < 5; i++)
    {
      next = graphInd(currentNode, i, num_st, num_av);
      if (((next != (-1)) && (parent[next] == (-1))) && (graph[currentNode][i] == 1))
      {
        parent[next] = currentNode;
        for (t = 0; t < num_sup; t++)
        {
          if (next == sups[t])
          {
            return next;
          }
          else
          {
            
          }

        }

        enqueue(q, next);
      }
      else
      {
        
      }

    }

  }

  return -3;
}

void edmondsKarp(int **matrix, int *cits, int *sups, int num_sup, int num_cit, int n, int num_st, int num_av)
{
  int currentNode;
  int previousNode = 0;
  int *parent = malloc((sizeof(int)) * n);
  queue *q = malloc(sizeof(queue));
  q->node = malloc((sizeof(int)) * n);
  currentNode = bfs(matrix, cits, sups, q, parent, num_sup, num_cit, n, num_st, num_av);
  while (currentNode != (-3))
  {
    while (currentNode != (-2))
    {
      previousNode = parent[currentNode];
      if (previousNode != (-2))
      {
        matrix[previousNode][relativeInd(previousNode, currentNode, num_st, num_av)] = 0;
        matrix[currentNode][relativeInd(currentNode, previousNode, num_st, num_av)] = 1;
      }
      else
      {
        
      }

      currentNode = previousNode;
    }

    result++;
    currentNode = bfs(matrix, cits, sups, q, parent, num_sup, num_cit, n, num_st, num_av);
  }

  free(q->node);
  free(q);
  free(parent);
}

void enqueue(queue *q, int node)
{
  if (q->in == (-1))
  {
    q->in = 0;
  }
  else
  {
    
  }

  q->out++;
  q->node[q->out] = node;
}

int dequeue(queue *q)
{
  int ret;
  if (q->in == (-1))
  {
    return -1;
  }
  else
  {
    
  }

  ret = q->node[q->in];
  q->in++;
  if (q->in > q->out)
  {
    q->in = (q->out = -1);
  }
  else
  {
    
  }

  return ret;
}

int empty(queue *q)
{
  return (q->in == (-1)) && (q->out == (-1));
}

int ind(int av, int st, int num_st)
{
  return 2 * ((((av - 1) * num_st) + st) - 1);
}

int relativeInd(int node, int adj, int num_st, int num_av)
{
  int av;
  int st;
  st = ((node / 2) + 1) % num_st;
  if (st == 0)
  {
    st = num_st;
  }
  else
  {
    
  }

  av = ((((node / 2) + 1) - st) / num_st) + 1;
  if ((node % 2) == 0)
  {
    if ((av != 1) && (((node - (2 * num_st)) + 1) == adj))
    {
      return 0;
    }
    else
    {
      
    }

    if ((av != num_av) && (((node + (2 * num_st)) + 1) == adj))
    {
      return 2;
    }
    else
    {
      
    }

    if ((node + 1) == adj)
    {
      return 4;
    }
    else
    {
      
    }

    if ((st != 1) && ((node - 1) == adj))
    {
      return 3;
    }
    else
    {
      
    }

    if ((st != num_st) && ((node + 3) == adj))
    {
      return 1;
    }
    else
    {
      
    }

  }
  else
  {
    if ((av != 1) && (((node - (2 * num_st)) - 1) == adj))
    {
      return 0;
    }
    else
    {
      
    }

    if ((av != num_av) && (((node + (2 * num_st)) - 1) == adj))
    {
      return 2;
    }
    else
    {
      
    }

    if ((node - 1) == adj)
    {
      return 4;
    }
    else
    {
      
    }

    if ((st != 1) && ((node - 3) == adj))
    {
      return 3;
    }
    else
    {
      
    }

    if ((st != num_st) && ((node + 1) == adj))
    {
      return 1;
    }
    else
    {
      
    }

  }

  return -1;
}

int graphInd(int node, int adj, int num_st, int num_av)
{
  int av;
  int st;
  st = ((node / 2) + 1) % num_st;
  if (st == 0)
  {
    st = num_st;
  }
  else
  {
    
  }

  av = ((((node / 2) + 1) - st) / num_st) + 1;
  if ((node % 2) != 0)
  {
    if (adj == 4)
    {
      return node - 1;
    }
    else
    {
      
    }

    if ((av != 1) && (adj == 0))
    {
      return (node - (2 * num_st)) - 1;
    }
    else
    {
      
    }

    if ((av != num_av) && (adj == 2))
    {
      return (node + (2 * num_st)) - 1;
    }
    else
    {
      
    }

    if ((st != 1) && (adj == 3))
    {
      return node - 3;
    }
    else
    {
      
    }

    if ((st != num_st) && (adj == 1))
    {
      return node + 1;
    }
    else
    {
      
    }

  }
  else
  {
    if (adj == 4)
    {
      return node + 1;
    }
    else
    {
      
    }

    if ((av != 1) && (adj == 0))
    {
      return (node - (2 * num_st)) + 1;
    }
    else
    {
      
    }

    if ((st != num_st) && (adj == 1))
    {
      return node + 3;
    }
    else
    {
      
    }

    if ((av != num_av) && (adj == 2))
    {
      return (node + (2 * num_st)) + 1;
    }
    else
    {
      
    }

    if ((st != 1) && (adj == 3))
    {
      return node - 1;
    }
    else
    {
      
    }

  }

  return -1;
}

int **initializeGraph(int num_av, int num_st)
{
  int i;
  int av;
  int st;
  int n = (2 * num_av) * num_st;
  int **m = malloc((sizeof(int *)) * n);
  for (i = 0; i < n; i++)
  {
    m[i] = malloc((sizeof(int)) * 5);
  }

  for (i = 0; i < n; i += 2)
  {
    st = ((i / 2) + 1) % num_st;
    if (st == 0)
    {
      st = num_st;
    }
    else
    {
      
    }

    av = ((((i / 2) + 1) - st) / num_st) + 1;
    m[i][relativeInd(i, i + 1, num_st, num_av)] = 1;
    m[i + 1][relativeInd(i + 1, i, num_st, num_av)] = 0;
    if (av == 1)
    {
      if (st == 1)
      {
        m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
        m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
        m[i + 1][relativeInd(i + 1, i + (2 * num_st), num_st, num_av)] = 1;
        m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
      }
      else
      {
        if (st == num_st)
        {
          m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
          m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 1;
          m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
        }
        else
        {
          m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
          m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
          m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + 1, i + (2 * num_st), num_st, num_av)] = 1;
          m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
        }

      }

    }
    else
    {
      if (av == num_av)
      {
        if (st == 1)
        {
          m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
          m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
          m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
        }
        else
        {
          if (st == num_st)
          {
            m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
            m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
            m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
          }
          else
          {
            m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
            m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
            m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
            m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
          }

        }

      }
      else
      {
        if (((st == 1) && (av != 1)) && (av != num_av))
        {
          m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
          m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
          m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
          m[i + 1][relativeInd(i + 1, i + (2 * num_st), num_st, num_av)] = 1;
          m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
        }
        else
        {
          if (((st == num_st) && (av != 1)) && (av != num_av))
          {
            m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
            m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
            m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i + (2 * num_st), num_st, num_av)] = 1;
            m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
          }
          else
          {
            m[i + 1][relativeInd(i + 1, i - (2 * num_st), num_st, num_av)] = 1;
            m[i - (2 * num_st)][relativeInd(i - (2 * num_st), i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i - 2, num_st, num_av)] = 1;
            m[i - 2][relativeInd(i - 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i + 2, num_st, num_av)] = 1;
            m[i + 2][relativeInd(i + 2, i + 1, num_st, num_av)] = 0;
            m[i + 1][relativeInd(i + 1, i + (2 * num_st), num_st, num_av)] = 1;
            m[i + (2 * num_st)][relativeInd(i + (2 * num_st), i + 1, num_st, num_av)] = 0;
          }

        }

      }

    }

  }

  return m;
}

int *initializeCitLocations(int n, int num_st)
{
  int i;
  int av;
  int st;
  int *list = malloc((sizeof(int)) * n);
  for (i = 0; i < n; i++)
  {
    av = new_sym_var(sizeof(int) * 8);
    st = new_sym_var(sizeof(int) * 8);
    list[i] = ind(av, st, num_st);
  }

  return list;
}

int *initializeSupLocations(int n, int num_st)
{
  int i;
  int av;
  int st;
  int *list = malloc((sizeof(int)) * n);
  for (i = 0; i < n; i++)
  {
    av = new_sym_var(sizeof(int) * 8);
    st = new_sym_var(sizeof(int) * 8);
    list[i] = ind(av, st, num_st) + 1;
  }

  return list;
}

void freeGraph(int **g, int n)
{
  int i;
  for (i = 0; i < n; i++)
    free(g[i]);

  free(g);
}

