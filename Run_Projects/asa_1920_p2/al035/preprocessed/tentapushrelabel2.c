/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Vertex
{
  struct Vertex *parent;
  char id;
  int primary;
  int e_flow;
  int height;
  struct Adjacent *head;
} Vertex;
typedef struct Edge
{
  Vertex *u;
  Vertex *v;
  int flow;
  int cap;
} Edge;
typedef struct Node
{
  Vertex *inNode;
  struct Node *next;
} Node;
typedef struct Queue
{
  Node *head;
} Queue;
typedef struct PrimaryVertex
{
  char id;
  Vertex in;
  Vertex out;
} PrimaryVertex;
typedef struct Adjacent
{
  Edge *edge;
  struct Adjacent *next;
} Adjacent;
typedef struct AdjList
{
  Adjacent *head;
} AdjList;
PrimaryVertex *graph;
Node *front;
Node *rear;
Node *head;
Vertex sink;
Vertex source;
Queue queue;
int cidadaos;
int supermercados;
int ruas;
int avenidas;
int nVertexes;
int nPrimaryVertexes;
int currentHeight;
int giveMatrixIndex(int rua, int avenida)
{
  return ((rua * avenidas) - (avenidas - avenida)) - 1;
}

int giveIndexV(int rua, int avenida, int dir)
{
  if (dir == 1)
  {
    return giveMatrixIndex(rua, avenida + 1);
  }
  else
  {
    return giveMatrixIndex(rua + 1, avenida);
  }

}

struct Vertex newVertex(int pri, char type)
{
  struct Vertex new;
  new.primary = pri;
  new.id = type;
  new.height = 0;
  new.e_flow = 0;
  new.parent = 0;
  new.head = 0;
  return new;
}

PrimaryVertex *initGraph()
{
  int i;
  PrimaryVertex *grafo = malloc(nPrimaryVertexes * (sizeof(*grafo)));
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    grafo[i].id = '-';
    grafo[i].in = newVertex(i + 1, 'i');
    grafo[i].out = newVertex(i + 1, 'o');
  }

  source = newVertex(0, 's');
  sink = newVertex(-5, 't');
  return grafo;
}

void freegraph()
{
  free(graph);
}

void printGraph()
{
  int i;
  int j;
  int n;
  n = 0;
  for (i = 0; i < ruas; i++)
  {
    for (j = 0; j < avenidas; j++)
    {
      printf("%c(E:%d,H:%d)\t", graph[n].id, graph[n].in.e_flow, graph[n].in.height);
      n++;
    }

    printf("\n");
  }

  printf("\n");
  printf("%c(E:%d,H:%d)\t %c(E:%d,H:%d)\n", source.id, source.e_flow, source.height, sink.id, sink.e_flow, sink.height);
}

void printAllVertexes()
{
  int i;
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    printf("Vertice-%d \tin:%c out:%c\n", i + 1, graph[i].in.id, graph[i].out.id);
  }

}

Vertex *getParent(Vertex son)
{
  return son.parent;
}

void resetParents()
{
  int i;
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    graph[i].in.parent = 0;
    graph[i].out.parent = 0;
  }

}

void printVertex(Vertex *in)
{
  printf("Vertex:%d\t%c (E:%d,H:%d)\n", in->primary, in->id, in->e_flow, in->height);
}

void initQueue()
{
  queue.head = 0;
  front = 0;
  rear = 0;
  head = 0;
}

void enQueue(Vertex *in)
{
  Node *new = malloc(sizeof(Node));
  new->inNode = in;
  if ((front == 0) && (rear == 0))
  {
    front = new;
    rear = new;
    new->next = 0;
  }
  else
  {
    rear->next = new;
    new->next = 0;
    rear = new;
  }

}

int isEmpty()
{
  if (front == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

Vertex *deQueue()
{
  Node *temp = front;
  Vertex *q = temp->inNode;
  if (isEmpty())
  {
    return 0;
  }
  else
  {
    
  }

  if (front == rear)
  {
    free(temp);
    front = 0;
    rear = 0;
  }
  else
  {
    front = front->next;
    free(temp);
  }

  return q;
}

Vertex *getWhatsInQueue()
{
  Node *temp = front;
  Vertex *q = temp->inNode;
  if (isEmpty())
  {
    return 0;
  }
  else
  {
    
  }

  return q;
}

void displayQueue()
{
  int i;
  Node *ptr = front;
  i = 1;
  printf("THA QUEUE:\n");
  while (ptr != 0)
  {
    printf("Node %d : Vertex:%d \t%c\n", i, ptr->inNode->primary, ptr->inNode->id);
    ptr = ptr->next;
    i++;
  }

  printf("\n");
}

void cleanQueue()
{
  Node *temp;
  while (front != 0)
  {
    temp = front;
    front = front->next;
    free(temp);
  }

  front = 0;
  rear = 0;
}

Adjacent *newAdjacent()
{
  Adjacent *new = malloc(sizeof(*new));
  new->edge = 0;
  new->next = 0;
  return new;
}

void addEdgeToVList(Vertex *Uvertex, Edge *edge)
{
  Adjacent *new = newAdjacent();
  new->next = Uvertex->head;
  new->edge = edge;
  Uvertex->head = new;
}

void removeSpecificEdgeFromVList(Vertex *Uvertex, Edge *edge)
{
  Adjacent *temp = Uvertex->head;
  Adjacent *prev;
  if (temp->edge == edge)
  {
    Uvertex->head = Uvertex->head->next;
    free(temp);
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    if (temp->edge == edge)
    {
      prev->next = temp->next;
      free(temp);
      return;
    }
    else
    {
      
    }

    prev = temp;
    temp = temp->next;
  }

}

void printEdgesList(Vertex *vertex)
{
  int n = 1;
  Adjacent *temp;
  temp = vertex->head;
  printf("PVERTEX:%d %c\n", vertex->primary, vertex->id);
  while (temp != 0)
  {
    printf("Edge:%d \t U:%d %c\tV:%d %c\n", n, temp->edge->u->primary, temp->edge->u->id, temp->edge->v->primary, temp->edge->v->id);
    temp = temp->next;
  }

}

void printAllEdgesList()
{
  int i;
  printf("ALL EDGES:\n");
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    printEdgesList(&graph[i].in);
    printEdgesList(&graph[i].out);
  }

  printEdgesList(&source);
  printEdgesList(&sink);
}

void freeEdgesFromSpecificVertexList(Vertex *u)
{
  Adjacent *temp = u->head;
  while (u->head != 0)
  {
    u->head = u->head->next;
    free(temp->edge);
    free(temp);
    temp = u->head;
  }

}

void freeAllEdgesLists()
{
  int i;
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    freeEdgesFromSpecificVertexList(&graph[i].in);
    freeEdgesFromSpecificVertexList(&graph[i].out);
  }

  freeEdgesFromSpecificVertexList(&sink);
  freeEdgesFromSpecificVertexList(&source);
}

void reverseEdge(Edge *edge)
{
  Vertex *temp = edge->u;
  edge->u = edge->v;
  edge->v = temp;
}

void switchEdgesInLists(Vertex *u, Edge *edge)
{
  Vertex *temp = edge->v;
  removeSpecificEdgeFromVList(u, edge);
  reverseEdge(edge);
  addEdgeToVList(temp, edge);
}

Edge *newEdge(Vertex *u, Vertex *v)
{
  Edge *new = malloc(sizeof(Edge));
  new->cap = 1;
  new->flow = 0;
  new->u = u;
  new->v = v;
  return new;
}

void addEdgesSupCid(PrimaryVertex *Pvertex, char id)
{
  if (id == 's')
  {
    addEdgeToVList(&source, newEdge(&source, &Pvertex->in));
  }
  else
  {
    addEdgeToVList(&Pvertex->out, newEdge(&Pvertex->out, &sink));
  }

}

void addInternalEdge(PrimaryVertex *Pvertex)
{
  addEdgeToVList(&Pvertex->in, newEdge(&Pvertex->in, &Pvertex->out));
}

void addALLInternalEdges()
{
  int i;
  for (i = 0; i < nPrimaryVertexes; i++)
  {
    addInternalEdge(&graph[i]);
  }

}

void addEdge(int rua, int avenida, int dir)
{
  int a;
  int b;
  a = giveMatrixIndex(rua, avenida);
  b = giveIndexV(rua, avenida, dir);
  addEdgeToVList(&graph[a].out, newEdge(&graph[a].out, &graph[b].in));
  addEdgeToVList(&graph[b].out, newEdge(&graph[b].out, &graph[a].in));
}

void processEdges(int rua, int avenida)
{
  if ((avenidas == 1) && (ruas == 1))
  {
    return;
  }
  else
  {
    
  }

  if ((rua < ruas) && (avenida < avenidas))
  {
    addEdge(rua, avenida, 1);
    addEdge(rua, avenida, 2);
    return;
  }
  else
  {
    if ((rua < ruas) && (avenida == avenidas))
    {
      addEdge(rua, avenida, 2);
      return;
    }
    else
    {
      if ((rua == ruas) && (avenida < avenidas))
      {
        addEdge(rua, avenida, 1);
        return;
      }
      else
      {
      }

    }

  }

}

void initEdges()
{
  int i;
  int j;
  addALLInternalEdges();
  for (i = 0; i < ruas; i++)
  {
    for (j = 0; j < avenidas; j++)
    {
      processEdges(i + 1, j + 1);
    }

  }

}

void initializeADSs()
{
  nPrimaryVertexes = ruas * avenidas;
  nVertexes = (2 * nPrimaryVertexes) + 2;
  initQueue();
  graph = initGraph();
  initEdges();
}

void freeADSs()
{
  freeAllEdgesLists();
  freegraph();
}

void processInput()
{
  char input[100];
  int i = 0;
  int j = 0;
  char nAvenidas[20];
  char nRuas[20];
  char nSupermercados[20];
  char nCidadaos[20];
  if (fgets(input, 100, stdin) == 0)
  {
  }
  else
  {
    
  }

  for (; input[i] != ' '; i++)
  {
    nAvenidas[i] = input[i];
  }

  nAvenidas[i] = 0;
  for (; input[i] != 0; i++)
  {
    nRuas[j] = input[i];
    j++;
  }

  nRuas[j] = 0;
  if (fgets(input, 100, stdin) == 0)
  {
  }
  else
  {
    
  }

  for (i = 0; input[i] != ' '; i++)
  {
    nSupermercados[i] = input[i];
  }

  nSupermercados[i] = 0;
  for (j = 0; input[i] != 0; i++, j++)
  {
    nCidadaos[j] = input[i];
  }

  nCidadaos[j] = 0;
  avenidas = atoi(nAvenidas);
  ruas = atoi(nRuas);
  supermercados = atoi(nSupermercados);
  cidadaos = atoi(nCidadaos);
}

void processCandSAux(PrimaryVertex *vertex, char type)
{
  if (vertex->id == 'B')
  {
    return;
  }
  else
  {
    
  }

  if ((vertex->id == 'C') && (type == 'C'))
  {
    return;
  }
  else
  {
    
  }

  if ((vertex->id == 'S') && (type == 'S'))
  {
    return;
  }
  else
  {
    
  }

  if ((vertex->id == 'C') && (type == 'S'))
  {
    vertex->id = 'B';
    addEdgesSupCid(vertex, 't');
    return;
  }
  else
  {
    
  }

  if ((vertex->id == 'S') && (type == 'C'))
  {
    vertex->id = 'B';
    addEdgesSupCid(vertex, 's');
    return;
  }
  else
  {
    vertex->id = type;
    if (type == 'S')
    {
      addEdgesSupCid(vertex, 't');
    }
    else
    {
      addEdgesSupCid(vertex, 's');
    }

  }

}

void processSupermercadosCidadaos()
{
  int i;
  int j;
  int k;
  int nRua;
  int nAvenida;
  char input[100];
  char rua[20];
  char avenida[20];
  for (k = 0; k < supermercados; k++)
  {
    if (fgets(input, 100, stdin) == 0)
    {
    }
    else
    {
      
    }

    i = 0;
    j = 0;
    for (; input[i] != ' '; i++)
    {
      avenida[i] = input[i];
    }

    avenida[i] = 0;
    for (; input[i] != 0; i++)
    {
      rua[j] = input[i];
      j++;
    }

    rua[j] = 0;
    nRua = atoi(rua);
    nAvenida = atoi(avenida);
    if (nRua > ruas)
    {
      fputs("Rua Invalida\n", stderr);
    }
    else
    {
      
    }

    if (nAvenida > avenidas)
    {
      fputs("Avenida Invalida\n", stderr);
    }
    else
    {
      
    }

    processCandSAux(&graph[giveMatrixIndex(nRua, nAvenida)], 'S');
  }

  for (k = 0; k < cidadaos; k++)
  {
    if (fgets(input, 100, stdin) == 0)
    {
    }
    else
    {
      
    }

    i = 0;
    j = 0;
    for (; input[i] != ' '; i++)
    {
      avenida[i] = input[i];
    }

    avenida[i] = 0;
    for (; input[i] != 0; i++)
    {
      rua[j] = input[i];
      j++;
    }

    rua[j] = 0;
    nRua = atoi(rua);
    nAvenida = atoi(avenida);
    if (nRua > ruas)
    {
      fputs("Rua Invalida\n", stderr);
    }
    else
    {
      
    }

    if (nAvenida > avenidas)
    {
      fputs("Avenida Invalida\n", stderr);
    }
    else
    {
      
    }

    processCandSAux(&graph[giveMatrixIndex(nRua, nAvenida)], 'C');
  }

}

void preFlow()
{
  Adjacent *temp = source.head;
  while (temp != 0)
  {
    temp->edge->v->e_flow = 1;
    enQueue(temp->edge->v);
    addEdgeToVList(temp->edge->v, newEdge(temp->edge->v, temp->edge->u));
    temp = temp->next;
  }

  source.height = nVertexes;
  sink.height = -1;
}

int push(Vertex *u)
{
  int flow;
  Adjacent *temp = u->head;
  while (temp != 0)
  {
    if (temp->edge->flow == temp->edge->cap)
    {
      temp = temp->next;
      continue;
    }
    else
    {
      
    }

    if (temp->edge->u->height > temp->edge->v->height)
    {
      flow = 1;
      temp->edge->u->e_flow -= flow;
      temp->edge->v->e_flow += flow;
      deQueue();
      if ((temp->edge->v != (&sink)) && (temp->edge->v != (&source)))
      {
        enQueue(temp->edge->v);
      }
      else
      {
        
      }

      if ((temp->edge->v != (&source)) && (temp->edge->v != (&sink)))
      {
        switchEdgesInLists(temp->edge->u, temp->edge);
      }
      else
      {
        
      }

      return 1;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return 0;
}

void relabel(Vertex *u)
{
  int minHeight = 10000000;
  Adjacent *temp = u->head;
  while (temp != 0)
  {
    if (temp->edge->flow == temp->edge->cap)
    {
      temp = temp->next;
      continue;
    }
    else
    {
      
    }

    if (temp->edge->v->height < minHeight)
    {
      minHeight = temp->edge->v->height;
      temp->edge->u->height = minHeight + 1;
      currentHeight = minHeight + 1;
    }
    else
    {
      
    }

    temp = temp->next;
  }

}

int getMaxFlow()
{
  Vertex *vert;
  while (!isEmpty())
  {
    vert = getWhatsInQueue();
    if (!push(vert))
    {
      relabel(vert);
    }
    else
    {
      
    }

    if (currentHeight > nVertexes)
    {
      break;
    }
    else
    {
      
    }

  }

  return sink.e_flow;
}

int main()
{
  processInput();
  initializeADSs();
  processSupermercadosCidadaos();
  preFlow();
  printf("%d\n", getMaxFlow());
  freeADSs();
  return 0;
}

