#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node
{
  unsigned long id;
  struct Node *next;
};
struct AdjList
{
  struct Node *head;
};
struct Graph
{
  unsigned long size;
  struct AdjList *lists;
};
struct Node *createNode(int id)
{
  struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
  newNode->id = id;
  newNode->next = 0;
  return newNode;
}

struct Graph *createGraph(int size)
{
  struct Graph *newGraph = (struct Graph *) malloc(sizeof(struct Graph));
  newGraph->size = size;
  newGraph->lists = (struct AdjList *) malloc(size * (sizeof(struct AdjList)));
  unsigned long i;
  for (i = 0; i < size; i++)
    newGraph->lists[i].head = 0;

  return newGraph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
  struct Node *newNode = createNode(dest);
  newNode->next = graph->lists[src].head;
  graph->lists[src].head = newNode;
  newNode = createNode(src);
  newNode->next = graph->lists[dest].head;
  graph->lists[dest].head = newNode;
}

void printGraph(struct Graph *graph)
{
  unsigned long i;
  for (i = 0; i < graph->size; i++)
  {
    struct Node *j = graph->lists[i].head;
    printf("\n Adjacency list of vertex %ld\n head ", i);
    while (j)
    {
      printf("-> %ld", j->id);
      j = j->next;
    }

    printf("\n");
  }

}

void freeGraph(struct Graph *graph)
{
  int i;
  struct Node *j;
  for (i = 0; i < graph->size; i++)
  {
    struct Node *k;
    for (j = graph->lists[i].head; j != 0; j = k)
    {
      k = j->next;
      free(j);
    }

  }

  free(graph->lists);
  free(graph);
}

struct Graph *intializeGraph(unsigned long vertices, unsigned long edges)
{
  unsigned long i;
  struct Graph *graph = createGraph(vertices);
  for (i = 0; i < edges; i++)
  {
    unsigned long src;
    unsigned long dst;
    if (2 != 2)
    {
      printf("Error: scanf failed\n");
    }
    else
    {
      src = new_sym_var(sizeof(unsigned long) * 8);
      dst = new_sym_var(sizeof(unsigned long) * 8);
      
    }

    if ((src <= vertices) && (dst <= vertices))
    {
      addEdge(graph, src - 1, dst - 1);
    }
    else
    {
      printf("Error: Router number out of range\n");
    }

  }

  return graph;
}

void DFS_Aux(unsigned long current, unsigned long *color, struct Graph *graph, unsigned long *breakers, unsigned long *count)
{
  struct Node *i;
  (*count)++;
  color[current] = 1;
  for (i = graph->lists[current].head; i != 0; i = i->next)
    if ((breakers[i->id] != 1) && (color[i->id] == 0))
  {
    DFS_Aux(i->id, color, graph, breakers, count);
  }
  else
  {
    
  }


  color[current] = 2;
}

unsigned long DFS(struct Graph *graph, unsigned long *breakers)
{
  unsigned long max = 0;
  unsigned long i;
  unsigned long *color = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  memset(color, 0, graph->size * (sizeof(unsigned long)));
  for (i = 0; i < graph->size; i++)
  {
    unsigned long count = 0;
    if ((breakers[i] != 1) && (color[i] == 0))
    {
      DFS_Aux(i, color, graph, breakers, &count);
    }
    else
    {
      
    }

    if (count > max)
    {
      max = count;
    }
    else
    {
      
    }

  }

  free(color);
  return max;
}

void tarjan_visit(unsigned long current, struct Graph *graph, unsigned long *dtime, unsigned long *low, unsigned long *parent, unsigned long *time, unsigned long *breakers, unsigned long *id)
{
  unsigned long children = 0;
  struct Node *i;
  dtime[current] = (low[current] = ++(*time));
  if ((*id) < current)
  {
    *id = current;
  }
  else
  {
    
  }

  for (i = graph->lists[current].head; i != 0; i = i->next)
    if (dtime[i->id] == 0)
  {
    children++;
    parent[i->id] = current;
    tarjan_visit(i->id, graph, dtime, low, parent, time, breakers, id);
    if (low[current] > low[i->id])
    {
      low[current] = low[i->id];
    }
    else
    {
      
    }

    if (((parent[current] == current) && (children > 1)) || ((parent[current] != current) && (low[i->id] >= dtime[current])))
    {
      breakers[current] = 1;
    }
    else
    {
      
    }

  }
  else
  {
    if (i->id != parent[current])
    {
      if (low[current] > dtime[i->id])
      {
        low[current] = dtime[i->id];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }


}

unsigned long *tarjan(struct Graph *graph)
{
  unsigned long time;
  unsigned long subcount;
  unsigned long i;
  time = (subcount = 0);
  unsigned long *ids = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  unsigned long *breakers = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  unsigned long *dtime = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  unsigned long *low = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  unsigned long *parent = (unsigned long *) malloc(graph->size * (sizeof(unsigned long)));
  memset(ids, 0, graph->size * (sizeof(unsigned long)));
  memset(breakers, 0, graph->size * (sizeof(unsigned long)));
  memset(dtime, 0, graph->size * (sizeof(unsigned long)));
  memset(low, 0, graph->size * (sizeof(unsigned long)));
  memset(parent, 0, graph->size * (sizeof(unsigned long)));
  for (i = 0; i < graph->size; i++)
    if (dtime[i] == 0)
  {
    unsigned long id = 0;
    parent[i] = i;
    tarjan_visit(i, graph, dtime, low, parent, &time, breakers, &id);
    ids[id] = 1;
    subcount++;
  }
  else
  {
    
  }


  unsigned long nBreakers = 0;
  for (i = 0; i < graph->size; i++)
    if (breakers[i] == 1)
  {
    nBreakers++;
  }
  else
  {
    
  }


  unsigned long *res = (unsigned long *) malloc((graph->size + 3) * (sizeof(unsigned long)));
  res[0] = subcount;
  res[1] = nBreakers;
  res[2] = DFS(graph, breakers);
  memcpy(res + 3, ids, graph->size * (sizeof(unsigned long)));
  free(ids);
  free(breakers);
  free(dtime);
  free(low);
  free(parent);
  return res;
}

int main()
{
  unsigned long nRouters;
  unsigned long nConnections;
  unsigned long i;
  if (2 != 2)
  {
    printf("Error: scanf failed\n");
  }
  else
  {
    nRouters = new_sym_var(sizeof(unsigned long) * 8);
    nConnections = new_sym_var(sizeof(unsigned long) * 8);
    
  }

  struct Graph *network = intializeGraph(nRouters, nConnections);
  unsigned long *res = tarjan(network);
  printf("%ld\n", res[0]);
  for (i = 3; i < (nRouters + 3); i++)
  {
    if (res[i] == 1)
    {
      printf("%ld", i - 2);
      if (i != (nRouters + 2))
      {
        printf(" ");
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  printf("\n%ld\n%ld\n", res[1], res[2]);
  free(res);
  freeGraph(network);
  return 0;
}

