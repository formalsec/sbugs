/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
  struct node *next;
  int value;
} node;
typedef struct linkedList
{
  node *head;
} LinkedList;
void initList(LinkedList *list)
{
  list->head = 0;
}

int pop(LinkedList *list)
{
  node *removedElement;
  int value;
  if (list->head == 0)
  {
    return -1;
  }
  else
  {
    
  }

  removedElement = list->head;
  value = removedElement->value;
  list->head = list->head->next;
  free(removedElement);
  return value;
}

void push(LinkedList *list, int value)
{
  node *newNode;
  newNode = (node *) malloc(sizeof(node));
  newNode->value = value;
  newNode->next = list->head;
  list->head = newNode;
}

void destroyList(LinkedList *list)
{
  node *node_;
  node *nextNode;
  node_ = list->head;
  while (node_ != 0)
  {
    nextNode = node_->next;
    free(node_);
    node_ = nextNode;
  }

}

int isEmpty(LinkedList list)
{
  if (list.head == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

typedef struct graph
{
  int vertices;
  int edges;
  LinkedList *outGoingEdges;
} Graph;
void initGraph(Graph *graph, int vertices, int edges)
{
  int i;
  graph->vertices = vertices;
  graph->edges = edges;
  graph->outGoingEdges = (LinkedList *) malloc((sizeof(LinkedList)) * vertices);
  for (i = 0; i < vertices; i++)
  {
    initList(&graph->outGoingEdges[i]);
  }

}

LinkedList getAdj(Graph graph, int vertice)
{
  return graph.outGoingEdges[vertice];
}

int *getSources(Graph graph, int *numSources)
{
  int i;
  int *numIncomingEdges = (int *) malloc((sizeof(int)) * graph.vertices);
  *numSources = graph.vertices;
  LinkedList adjencies;
  node *adjVertice;
  for (i = 0; i < graph.vertices; i++)
  {
    adjencies = getAdj(graph, i);
    adjVertice = adjencies.head;
    for (; adjVertice != 0; adjVertice = adjVertice->next)
    {
      if (numIncomingEdges[adjVertice->value] == 0)
      {
        (*numSources)--;
      }
      else
      {
        
      }

      numIncomingEdges[adjVertice->value]++;
    }

  }

  int sourceIndex = 0;
  int *sources = (int *) malloc((sizeof(int)) * (*numSources));
  for (i = 0; sourceIndex < (*numSources); i++)
  {
    if (numIncomingEdges[i] == 0)
    {
      sources[sourceIndex] = i;
      sourceIndex++;
    }
    else
    {
      
    }

  }

  free(numIncomingEdges);
  return sources;
}

void destroyGraph(Graph *graph)
{
  int i;
  for (i = 0; i < graph->vertices; i++)
  {
    destroyList(&graph->outGoingEdges[i]);
  }

  free(graph->outGoingEdges);
}

void processInput(Graph *graph)
{
  int vertices;
  int edges;
  int i;
  vertices = new_sym_var(sizeof(int) * 8);
  edges = new_sym_var(sizeof(int) * 8);
  initGraph(graph, vertices, edges);
  for (i = 0; i < edges; i++)
  {
    int u;
    int v;
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    push(&graph->outGoingEdges[u - 1], v - 1);
  }

}

int calculateLargestPath(Graph graph, int *sources, int sourcesSize)
{
  int i;
  char *color = (char *) malloc((sizeof(char)) * graph.vertices);
  int *longestPath = (int *) malloc((sizeof(int)) * graph.vertices);
  int visitingVertice;
  LinkedList adj;
  node *adjVertice;
  int longestAdjPath;
  LinkedList stack;
  initList(&stack);
  for (i = 0; i < graph.vertices; i++)
  {
    color[i] = 0;
    longestPath[i] = -1;
  }

  for (i = 0; i < sourcesSize; i++)
  {
    push(&stack, sources[i]);
    while (isEmpty(stack) != 1)
    {
      visitingVertice = stack.head->value;
      if (color[visitingVertice] == 0)
      {
        color[visitingVertice] = 1;
        adj = getAdj(graph, visitingVertice);
        for (adjVertice = adj.head; adjVertice != 0; adjVertice = adjVertice->next)
        {
          if (color[adjVertice->value] == 0)
          {
            push(&stack, adjVertice->value);
          }
          else
          {
            
          }

        }

      }
      else
      {
        visitingVertice = pop(&stack);
        if (color[visitingVertice] == 1)
        {
          color[visitingVertice] = 2;
          adj = getAdj(graph, visitingVertice);
          if (isEmpty(adj))
          {
            longestPath[visitingVertice] = 1;
          }
          else
          {
            
          }

          longestAdjPath = -1;
          for (adjVertice = adj.head; adjVertice != 0; adjVertice = adjVertice->next)
          {
            if (longestPath[adjVertice->value] > longestAdjPath)
            {
              longestAdjPath = longestPath[adjVertice->value];
            }
            else
            {
              
            }

          }

          longestPath[visitingVertice] = longestAdjPath + 1;
        }
        else
        {
          
        }

      }

    }

  }

  int overallLongestPath = -1;
  for (i = 0; i < sourcesSize; i++)
  {
    if (overallLongestPath < longestPath[sources[i]])
    {
      overallLongestPath = longestPath[sources[i]];
    }
    else
    {
      
    }

  }

  free(color);
  free(longestPath);
  return overallLongestPath + 1;
}

int main()
{
  int k;
  int l;
  Graph graph;
  int *sources;
  processInput(&graph);
  sources = getSources(graph, &k);
  l = calculateLargestPath(graph, sources, k);
  printf("%d %d\n", k, l);
  destroyGraph(&graph);
  free(sources);
  return 0;
}

