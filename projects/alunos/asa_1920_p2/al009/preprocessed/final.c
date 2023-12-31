#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct 
{
  int pessoa;
  int market;
  int *edges;
  int *flow;
  int n_edge;
  bool onQueue;
  int parent;
} Crossing;
int avenues;
int streets;
int markets;
int person;
int n_vertex;
int *queue;
int front = -1;
int rear = -1;
Crossing *corners;
int max_flow = 0;
void inicialize_corners();
void addEdge(int a, int b);
void build_matrix();
void edmonds_karp();
int BFS();
void augment(int end);
int find_edge(int a, int b);
int min(int a, int b);
bool isEmpty();
void push(int n);
int pop();
void reset();
int main()
{
  int i;
  int l;
  int c;
  int node;
  avenues = new_sym_var(sizeof(int) * 8);
  streets = new_sym_var(sizeof(int) * 8);
  markets = new_sym_var(sizeof(int) * 8);
  person = new_sym_var(sizeof(int) * 8);
  n_vertex = avenues * streets;
  inicialize_corners();
  queue = malloc((sizeof(int)) * ((n_vertex * 2) + 2));
  for (i = 0; i < markets; i++)
  {
    l = new_sym_var(sizeof(int) * 8);
    c = new_sym_var(sizeof(int) * 8);
    node = 2 * (((c - 1) * avenues) + l);
    corners[node - 1].market = 1;
    addEdge(node, (n_vertex * 2) + 1);
  }

  for (i = 0; i < person; i++)
  {
    l = new_sym_var(sizeof(int) * 8);
    c = new_sym_var(sizeof(int) * 8);
    node = 2 * (((c - 1) * avenues) + l);
    if (corners[node - 1].pessoa != 1)
    {
      corners[node - 1].pessoa = 1;
      addEdge(0, node - 1);
    }
    else
    {
      
    }

  }

  build_matrix();
  edmonds_karp();
  printf("%d\n", max_flow);
  for (i = 0; i < ((n_vertex * 2) + 2); i++)
  {
    free(corners[i].flow);
    free(corners[i].edges);
  }

  free(corners);
  return 0;
}

void inicialize_corners()
{
  int i;
  corners = (Crossing *) malloc((sizeof(Crossing)) * ((n_vertex * 2) + 2));
  for (i = 0; i < ((n_vertex * 2) + 2); i++)
  {
    corners[i].pessoa = 0;
    corners[i].market = 0;
    corners[i].n_edge = 0;
    corners[i].edges = 0;
    corners[i].flow = 0;
    corners[i].parent = -1;
    corners[i].onQueue = false;
  }

}

void addEdge(int a, int b)
{
  int i;
  int *new_edges;
  int *new_flow;
  if (corners[a].n_edge == 0)
  {
    corners[a].edges = malloc(sizeof(int));
    corners[a].edges[0] = b;
    corners[a].flow = malloc(sizeof(int));
    corners[a].flow[0] = 1;
    corners[a].n_edge++;
  }
  else
  {
    corners[a].n_edge++;
    new_edges = malloc((sizeof(int)) * corners[a].n_edge);
    new_flow = malloc((sizeof(int)) * corners[a].n_edge);
    for (i = 0; i < (corners[a].n_edge - 1); i++)
    {
      new_edges[i] = corners[a].edges[i];
      new_flow[i] = corners[a].flow[i];
    }

    new_edges[i] = b;
    new_flow[i] = 1;
    corners[a].edges = new_edges;
    corners[a].flow = new_flow;
  }

}

void build_matrix()
{
  int i;
  for (i = 1; i < (n_vertex * 2); i += 2)
  {
    addEdge(i, i + 1);
  }

  for (i = 2; i < ((n_vertex * 2) + 1); i += 2)
  {
    if ((i + (2 * avenues)) < ((n_vertex * 2) + 1))
    {
      addEdge(i, (i + (2 * avenues)) - 1);
      addEdge(i + (2 * avenues), i - 1);
    }
    else
    {
      
    }

    if ((i % (2 * avenues)) != 0)
    {
      addEdge(i, i + 1);
      addEdge(i + 2, i - 1);
    }
    else
    {
      
    }

  }

}

bool isEmpty()
{
  return (front == (-1)) || (rear == (-1));
}

int pop()
{
  int i;
  if (isEmpty())
  {
    return -1;
  }
  else
  {
    
  }

  if (front == rear)
  {
    i = rear;
    rear = -1;
    front = -1;
    return queue[i];
  }
  else
  {
    return queue[front++];
  }

}

void push(int n)
{
  if (isEmpty())
  {
    front = 0;
    rear = 0;
    queue[rear] = n;
  }
  else
  {
    rear++;
    queue[rear] = n;
  }

}

int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

void edmonds_karp()
{
  int end;
  push(0);
  end = BFS();
  if (end > 0)
  {
    augment(end);
    max_flow++;
  }
  else
  {
    
  }

  while ((end != (-1)) && (!(max_flow == min(person, markets))))
  {
    reset();
    push(0);
    end = BFS();
    if (end > 0)
    {
      augment(end);
      max_flow++;
    }
    else
    {
      
    }

  }

}

int BFS()
{
  int i;
  int node;
  int destino;
  while (!isEmpty())
  {
    node = pop();
    for (i = 0; i < corners[node].n_edge; i++)
    {
      destino = corners[node].edges[i];
      if (corners[destino].onQueue || (corners[node].flow[i] == 0))
      {
        continue;
      }
      else
      {
        if (destino == ((n_vertex * 2) + 1))
        {
          corners[node].flow[i] = 0;
          return node;
        }
        else
        {
          if ((corners[destino].pessoa == 1) && (node != 0))
          {
            continue;
          }
          else
          {
            push(destino);
            corners[destino].parent = node;
            corners[destino].onQueue = true;
          }

        }

      }

    }

  }

  return -1;
}

void reset()
{
  int i;
  for (i = 0; i < ((n_vertex * 2) + 2); i++)
  {
    corners[i].onQueue = false;
    corners[i].parent = -1;
    front = -1;
    rear = -1;
  }

}

void augment(int end)
{
  int n;
  int prev;
  int aux;
  prev = corners[end].parent;
  n = find_edge(prev, end);
  corners[prev].flow[n] = 0;
  addEdge(end, prev);
  while (prev != 0)
  {
    aux = corners[prev].parent;
    n = find_edge(aux, prev);
    corners[aux].flow[n] = 0;
    addEdge(prev, aux);
    prev = corners[prev].parent;
  }

}

int find_edge(int a, int b)
{
  int i;
  for (i = 0; i < corners[a].n_edge; i++)
  {
    if (corners[a].edges[i] == b)
    {
      return i;
    }
    else
    {
      
    }

  }

  return -1;
}

