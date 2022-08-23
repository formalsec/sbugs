/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


struct QNode
{
  int key;
  struct QNode *next;
};
struct Queue
{
  struct QNode *front;
  struct QNode *rear;
};
typedef struct AdjListNode
{
  int dest;
  int capacidade;
  struct AdjListNode *next;
} AdjListNode;
typedef struct AdjList
{
  AdjListNode *head;
} AdjList;
typedef struct Graph
{
  int V;
  int *pi;
  int *visited;
  AdjList *array;
} Graph;
AdjListNode *addAdjListNode(int dest, int cap);
Graph *createGraph(int V);
void addEdge(Graph *graph, int orig, int dest, int cap);
void freeGraph(Graph *graph);
int EdmondsKarp(Graph *graph, int s, int t);
int BFS(Graph *graph, int s, int t);
struct QNode *newNode(int k);
struct Queue *createQueue();
void enqueue(struct Queue *q, int k);
int dequeue(struct Queue *q);
int is_Q_empty(struct Queue *q);
int min(int u, int v);
int **matrix;
int main()
{
  int i;
  int j;
  int n;
  int v_in;
  int numAvenidas;
  int numRuas;
  int numClientes;
  int numSupermercados;
  n = 2;
  numAvenidas = new_sym_var(sizeof(int) * 8);
  numRuas = new_sym_var(sizeof(int) * 8);
  if (n < 0)
  {
    perror("Error:scanf");
  }
  else
  {
    
  }

  n = 2;
  numSupermercados = new_sym_var(sizeof(int) * 8);
  numClientes = new_sym_var(sizeof(int) * 8);
  if (n < 0)
  {
    perror("Error:scanf");
  }
  else
  {
    
  }

  int V = (2 * numAvenidas) * numRuas;
  Graph *graph = createGraph(V + 2);
  for (v_in = 1; v_in < V; v_in = v_in + 2)
  {
    addEdge(graph, v_in, v_in + 1, 1);
    addEdge(graph, v_in + 1, v_in, 0);
  }

  matrix = (int **) malloc(numAvenidas * (sizeof(int *)));
  for (i = 0; i < numAvenidas; i++)
  {
    matrix[i] = (int *) malloc(numRuas * (sizeof(int)));
  }

  int k = 1;
  for (i = 0; i < numAvenidas; i++)
  {
    for (j = numRuas - 1; j >= 0; j--)
    {
      matrix[i][j] = k;
      k += 2;
    }

  }

  int sumermercado[V];
  for (i = 1; i < V; i += 2)
  {
    sumermercado[i] = 0;
  }

  int cliente[V];
  for (i = 1; i < V; i += 2)
  {
    cliente[i] = 0;
  }

  j = 0;
  int T = V + 1;
  for (k = 0; k < numSupermercados; k++)
  {
    n = 2;
    i = new_sym_var(sizeof(int) * 8);
    j = new_sym_var(sizeof(int) * 8);
    if (n < 0)
    {
      perror("Error:scanf");
    }
    else
    {
      
    }

    if (sumermercado[matrix[i - 1][j - 1]] == 0)
    {
      addEdge(graph, matrix[i - 1][j - 1] + 1, T, 1);
      addEdge(graph, T, matrix[i - 1][j - 1] + 1, 0);
      sumermercado[matrix[i - 1][j - 1]] = 1;
    }
    else
    {
      
    }

  }

  for (k = 0; k < numClientes; k++)
  {
    n = 2;
    i = new_sym_var(sizeof(int) * 8);
    j = new_sym_var(sizeof(int) * 8);
    if (n < 0)
    {
      perror("Error:scanf");
    }
    else
    {
      
    }

    if (cliente[matrix[i - 1][j - 1]] == 0)
    {
      addEdge(graph, 0, matrix[i - 1][j - 1], 1);
      addEdge(graph, matrix[i - 1][j - 1], 0, 0);
      cliente[matrix[i - 1][j - 1]] = 1;
    }
    else
    {
      
    }

  }

  for (i = 0; i < numAvenidas; i++)
  {
    for (j = numRuas - 1; j >= 0; j--)
    {
      if ((i == 0) && (j == (numRuas - 1)))
      {
        addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
        addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
        addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
        addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
        continue;
      }
      else
      {
        if ((i == 0) && (j == 0))
        {
          addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
          addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
          addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
          addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
          continue;
        }
        else
        {
          if ((j == (numRuas - 1)) && (i == (numAvenidas - 1)))
          {
            addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
            addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
            addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
            addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
            continue;
          }
          else
          {
            if ((i == (numAvenidas - 1)) && (j == 0))
            {
              addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
              addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
              addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
              addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
              continue;
            }
            else
            {
              if (i == 0)
              {
                addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
                addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
                addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
                addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
                addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
                addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
                continue;
              }
              else
              {
                if (i == (numAvenidas - 1))
                {
                  addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
                  addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
                  addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
                  addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
                  addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
                  addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
                  continue;
                }
                else
                {
                  if (j == (numRuas - 1))
                  {
                    addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
                    addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
                    addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
                    addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
                    addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
                    addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
                    continue;
                  }
                  else
                  {
                    if (j == 0)
                    {
                      addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
                      addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
                      addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
                      addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
                      addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
                      addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
                      continue;
                    }
                    else
                    {
                      addEdge(graph, matrix[i][j] + 1, matrix[i - 1][j], 1);
                      addEdge(graph, matrix[i][j] + 1, matrix[i + 1][j], 1);
                      addEdge(graph, matrix[i][j] + 1, matrix[i][j + 1], 1);
                      addEdge(graph, matrix[i][j] + 1, matrix[i][j - 1], 1);
                      addEdge(graph, matrix[i - 1][j], matrix[i][j] + 1, 0);
                      addEdge(graph, matrix[i + 1][j], matrix[i][j] + 1, 0);
                      addEdge(graph, matrix[i][j + 1], matrix[i][j] + 1, 0);
                      addEdge(graph, matrix[i][j - 1], matrix[i][j] + 1, 0);
                    }

                  }

                }

              }

            }

          }

        }

      }

    }

  }

  for (i = 0; i < numAvenidas; i++)
  {
    free(matrix[i]);
  }

  int max_flow = EdmondsKarp(graph, 0, V + 1);
  printf("%d\n", max_flow);
  for (i = 0; i < (V + 2); i++)
  {
    AdjListNode *tmp;
    while (graph->array[i].head != 0)
    {
      tmp = graph->array[i].head;
      graph->array[i].head = graph->array[i].head->next;
      free(tmp);
    }

  }

  freeGraph(graph);
  return 0;
}

int EdmondsKarp(Graph *graph, int s, int t)
{
  int v;
  int u;
  int cap_r = 32767;
  int max_flow = 0;
  while (BFS(graph, s, t) == 1)
  {
    int path_flow = 32767;
    for (v = t; v != s; v = graph->pi[v])
    {
      u = graph->pi[v];
      AdjListNode *adjNode;
      for (adjNode = graph->array[u].head; adjNode != 0; adjNode = adjNode->next)
      {
        if (adjNode->dest == v)
        {
          cap_r = adjNode->capacidade;
          break;
        }
        else
        {
          
        }

      }

      path_flow = min(path_flow, cap_r);
    }

    for (v = t; v != s; v = graph->pi[v])
    {
      u = graph->pi[v];
      AdjListNode *adjNode;
      for (adjNode = graph->array[u].head; adjNode != 0; adjNode = adjNode->next)
      {
        if (adjNode->dest == v)
        {
          adjNode->capacidade -= path_flow;
          break;
        }
        else
        {
          
        }

      }

      for (adjNode = graph->array[v].head; adjNode != 0; adjNode = adjNode->next)
      {
        if (adjNode->dest == u)
        {
          adjNode->capacidade += path_flow;
          break;
        }
        else
        {
          
        }

      }

    }

    max_flow += path_flow;
  }

  return max_flow;
}

int BFS(Graph *graph, int s, int t)
{
  int w;
  int i;
  int v;
  for (i = 0; i < graph->V; i++)
  {
    graph->visited[i] = 0;
  }

  struct Queue *q = createQueue();
  enqueue(q, s);
  graph->visited[s] = 1;
  graph->pi[s] = -1;
  while (!is_Q_empty(q))
  {
    v = dequeue(q);
    if (v == t)
    {
      graph->visited[v] = 1;
      return 1;
    }
    else
    {
      
    }

    AdjListNode *adjNode;
    for (adjNode = graph->array[v].head; adjNode != 0; adjNode = adjNode->next)
    {
      w = adjNode->dest;
      if ((graph->visited[w] == 0) && (adjNode->capacidade > 0))
      {
        graph->visited[w] = 1;
        graph->pi[w] = v;
        enqueue(q, w);
      }
      else
      {
        
      }

    }

  }

  return 0;
}

Graph *createGraph(int V)
{
  Graph *graph = (Graph *) malloc(sizeof(Graph));
  graph->V = V;
  graph->array = (AdjList *) malloc(V * (sizeof(AdjList)));
  graph->pi = (int *) malloc(V * (sizeof(int)));
  graph->visited = (int *) malloc(V * (sizeof(int)));
  int i;
  for (i = 0; i < V; i++)
  {
    graph->array[i].head = 0;
  }

  return graph;
}

void freeGraph(Graph *graph)
{
  free(graph->array);
  free(graph->pi);
  free(graph->visited);
}

AdjListNode *addAdjListNode(int dest, int cap)
{
  AdjListNode *newNode = (AdjListNode *) malloc(sizeof(AdjListNode));
  newNode->dest = dest;
  newNode->capacidade = cap;
  newNode->next = 0;
  return newNode;
}

void addEdge(Graph *graph, int orig, int dest, int cap)
{
  AdjListNode *newNode = addAdjListNode(dest, cap);
  newNode->next = graph->array[orig].head;
  graph->array[orig].head = newNode;
}

struct QNode *newNode(int k)
{
  struct QNode *temp = (struct QNode *) malloc(sizeof(struct QNode));
  temp->key = k;
  temp->next = 0;
  return temp;
}

struct Queue *createQueue()
{
  struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));
  q->front = (q->rear = 0);
  return q;
}

void enqueue(struct Queue *q, int k)
{
  struct QNode *temp = newNode(k);
  if (q->rear == 0)
  {
    q->front = (q->rear = temp);
    return;
  }
  else
  {
    
  }

  q->rear->next = temp;
  q->rear = temp;
}

int dequeue(struct Queue *q)
{
  int x;
  if (q->front == 0)
  {
    return -1;
  }
  else
  {
    
  }

  struct QNode *temp = q->front;
  q->front = q->front->next;
  if (q->front == 0)
  {
    q->rear = 0;
  }
  else
  {
    
  }

  x = temp->key;
  free(temp);
  return x;
}

int is_Q_empty(struct Queue *q)
{
  return q->front == 0;
}

int min(int u, int v)
{
  if (u < v)
  {
    return u;
  }
  else
  {
    return v;
  }

}

