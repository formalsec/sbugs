#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
  int vertex;
  struct node *next;
};
struct node *createNode(int v);
struct Graph
{
  int numVertices;
  int *visited;
  int *disc;
  int *low;
  int *parent;
  int *ap;
  struct node **adjLists;
};
typedef struct network_result
{
  struct node *network;
  struct network_result *next;
} network_result_t;
struct Graph *createGraph(int);
void addEdge(struct Graph *, int, int);
void printGraph(struct Graph *);
void DFS(struct Graph *, int, int);
struct Graph *read_input_file();
struct node *push(struct node *, int);
void printResults(network_result_t *);
network_result_t *pushNetwork(network_result_t *);
void push_n(struct node **, int);
void insertOrdered(struct node **, int);
void free_results();
void DFS_NORMAL(struct Graph *, int, int);
void removeArticulationPoints(struct Graph *, int);
void printResults2(network_result_t *);
void free_graph(struct Graph *);
network_result_t *results;
int n_vertices;
int M = 0;
int main()
{
  int i;
  int j = 0;
  struct Graph *graph;
  results = 0;
  graph = read_input_file();
  for (i = 0; i < n_vertices; ++i)
  {
    if (!graph->visited[i])
    {
      DFS(graph, i, 0);
    }
    else
    {
      
    }

  }

  printf("%d\n", M);
  printResults(results);
  for (i = 0; i < n_vertices; i++)
  {
    if (graph->ap[i] == 1)
    {
      j++;
      removeArticulationPoints(graph, i);
    }
    else
    {
      
    }

  }

  printf("%d\n", j);
  j = 0;
  for (i = 0; i < n_vertices; ++i)
  {
    graph->visited[i] = 0;
  }

  free_results();
  free(graph->parent);
  free(graph->disc);
  free(graph->low);
  free(graph->ap);
  for (i = 0; i < n_vertices; ++i)
  {
    if (!graph->visited[i])
    {
      DFS_NORMAL(graph, i, 0);
    }
    else
    {
      
    }

  }

  printResults2(results);
  free_results();
  free_graph(graph);
  return 0;
}

void free_graph(struct Graph *graph)
{
  int i;
  struct node *tmp;
  for (i = 0; i < n_vertices; ++i)
  {
    while (graph->adjLists[i] != 0)
    {
      tmp = graph->adjLists[i];
      graph->adjLists[i] = tmp->next;
      free(tmp);
    }

  }

  free(graph->adjLists);
  free(graph->visited);
  free(graph);
}

void insertOrdered(struct node **head, int val)
{
  struct node *tmp = *head;
  struct node *prev = 0;
  struct node *new_node = createNode(val);
  if (tmp == 0)
  {
    new_node->next = tmp;
    *head = new_node;
    return;
  }
  else
  {
    
  }

  while ((tmp != 0) && (tmp->vertex <= val))
  {
    prev = tmp;
    tmp = tmp->next;
  }

  if (prev == 0)
  {
    new_node->next = tmp;
    *head = new_node;
  }
  else
  {
    new_node->next = tmp;
    prev->next = new_node;
  }

}

int cmpfunc(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

void printResults(network_result_t *head)
{
  network_result_t *tmp = head;
  int *networks;
  int i = 0;
  int c = 0;
  networks = (int *) malloc((sizeof(int)) * M);
  while (tmp != 0)
  {
    struct node *tmp2 = tmp->network;
    int max = -1;
    while (tmp2 != 0)
    {
      if (tmp2->vertex > max)
      {
        max = tmp2->vertex;
      }
      else
      {
        
      }

      tmp2 = tmp2->next;
    }

    networks[c++] = max + 1;
    tmp = tmp->next;
  }

  qsort(networks, M, sizeof(int), cmpfunc);
  for (i = 0; i < (M - 1); ++i)
  {
    printf("%d ", networks[i]);
  }

  printf("%d\n", networks[i]);
  free(networks);
}

void printResults2(network_result_t *head)
{
  network_result_t *tmp = head;
  int max = -1;
  while (tmp != 0)
  {
    int c = 0;
    struct node *tmp2 = tmp->network;
    while (tmp2 != 0)
    {
      c += 1;
      tmp2 = tmp2->next;
    }

    if (c > max)
    {
      max = c;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  printf("%d\n", max);
}

void removeArticulationPoints(struct Graph *graph, int vertex)
{
  struct node *tmp = 0;
  struct node *tmp2 = 0;
  struct node *prev = 0;
  while (graph->adjLists[vertex] != 0)
  {
    tmp = graph->adjLists[vertex];
    tmp2 = graph->adjLists[tmp->vertex];
    prev = 0;
    while (tmp2)
    {
      if (tmp2->vertex == vertex)
      {
        if (prev == 0)
        {
          graph->adjLists[tmp->vertex] = tmp2->next;
          tmp2->next = 0;
          free(tmp2);
          break;
        }
        else
        {
          prev->next = tmp2->next;
          tmp2->next = 0;
          free(tmp2);
          tmp2 = 0;
          break;
        }

      }
      else
      {
        
      }

      prev = tmp2;
      tmp2 = tmp2->next;
    }

    graph->adjLists[vertex] = tmp->next;
    free(tmp);
  }

}

void DFS(struct Graph *graph, int vertex, int flag)
{
  struct node *adjList = graph->adjLists[vertex];
  struct node *temp = adjList;
  static int time = 0;
  int children = 0;
  if ((!graph->visited[vertex]) && (!flag))
  {
    results = pushNetwork(results);
    push_n(&results->network, vertex);
    M += 1;
  }
  else
  {
    
  }

  graph->visited[vertex] = 1;
  graph->disc[vertex] = (graph->low[vertex] = ++time);
  while (temp != 0)
  {
    int connectedVertex = temp->vertex;
    if (graph->visited[connectedVertex] == 0)
    {
      children++;
      graph->parent[connectedVertex] = vertex;
      push_n(&results->network, connectedVertex);
      DFS(graph, connectedVertex, 1);
      graph->low[vertex] = (graph->low[vertex] < graph->low[connectedVertex]) ? (graph->low[vertex]) : (graph->low[connectedVertex]);
      if ((graph->parent[vertex] == (-1)) && (children > 1))
      {
        graph->ap[vertex] = 1;
      }
      else
      {
        
      }

      if ((graph->parent[vertex] != (-1)) && (graph->low[connectedVertex] >= graph->disc[vertex]))
      {
        graph->ap[vertex] = 1;
      }
      else
      {
        
      }

    }
    else
    {
      if (connectedVertex != graph->parent[vertex])
      {
        graph->low[vertex] = (graph->low[vertex] < graph->disc[connectedVertex]) ? (graph->low[vertex]) : (graph->disc[connectedVertex]);
      }
      else
      {
        
      }

    }

    temp = temp->next;
  }

}

void DFS_NORMAL(struct Graph *graph, int vertex, int flag)
{
  struct node *adjList = graph->adjLists[vertex];
  struct node *temp = adjList;
  if ((!graph->visited[vertex]) && (!flag))
  {
    results = pushNetwork(results);
    results->network = 0;
    push_n(&results->network, vertex);
  }
  else
  {
    
  }

  graph->visited[vertex] = 1;
  while (temp != 0)
  {
    int connectedVertex = temp->vertex;
    if (graph->visited[connectedVertex] == 0)
    {
      push_n(&results->network, connectedVertex);
      DFS_NORMAL(graph, connectedVertex, 1);
    }
    else
    {
      
    }

    temp = temp->next;
  }

}

void free_results()
{
  network_result_t *tmp = 0;
  struct node *tmp2 = 0;
  while (results != 0)
  {
    tmp = results;
    while (tmp->network != 0)
    {
      tmp2 = tmp->network;
      tmp->network = tmp2->next;
      free(tmp2);
      tmp2 = 0;
    }

    results = tmp->next;
    free(tmp);
    tmp = 0;
  }

  results = 0;
}

void push_n(struct node **head, int val)
{
  struct node *new_node = (struct node *) malloc(sizeof(struct node));
  new_node->vertex = val;
  new_node->next = *head;
  *head = new_node;
}

network_result_t *pushNetwork(network_result_t *head)
{
  if (head == 0)
  {
    network_result_t *new_node = malloc(sizeof(network_result_t));
    head = new_node;
    head->network = 0;
    head->next = 0;
    return head;
  }
  else
  {
    network_result_t *new_node = malloc(sizeof(network_result_t));
    new_node->next = head;
    head = new_node;
    return head;
  }

}

struct node *createNode(int v)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = 0;
  return newNode;
}

struct Graph *createGraph(int vertices)
{
  int i;
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;
  graph->adjLists = calloc(vertices, sizeof(struct node *));
  graph->visited = calloc(vertices, sizeof(int));
  graph->parent = malloc(vertices * (sizeof(int)));
  graph->disc = calloc(vertices, sizeof(int));
  graph->low = calloc(vertices, sizeof(int));
  graph->ap = calloc(vertices, sizeof(int));
  for (i = 0; i < vertices; i++)
  {
    graph->adjLists[i] = 0;
    graph->visited[i] = 0;
    graph->parent[i] = -1;
  }

  return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
  struct node *newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph *graph)
{
  int v;
  for (v = 0; v < graph->numVertices; v++)
  {
    struct node *temp = graph->adjLists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp)
    {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }

    printf("\n");
  }

}

struct Graph *read_input_file()
{
  struct Graph *g;
  int a;
  int b;
  int i;
  int n;
  int e;
  if (!2)
  {
    exit(0);
  }
  else
  {
    n = new_sym_var(sizeof(int) * 8);
    e = new_sym_var(sizeof(int) * 8);
    
  }

  n_vertices = n;
  g = createGraph(n);
  for (i = 0; i < e; i++)
  {
    if (!2)
    {
      exit(0);
    }
    else
    {
      a = new_sym_var(sizeof(int) * 8);
      b = new_sym_var(sizeof(int) * 8);
      
    }

    if (((((a - 1) < 0) || ((a - 1) >= n)) || ((b - 1) < 0)) || ((b - 1) >= n))
    {
      printf("Invalid input %d %d at %d \n", a, b, 466);
      exit(0);
    }
    else
    {
      addEdge(g, a - 1, b - 1);
    }

  }

  return g;
}

