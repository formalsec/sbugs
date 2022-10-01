/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct AdjListNode
{
  int dest;
  int cap;
  int flow;
  struct AdjListNode *next;
} *AdjListNode;
typedef struct AdjList
{
  AdjListNode head;
} *AdjList;
typedef struct Vertex
{
  int e_flow;
  int h;
} *Vertex;
typedef struct Graph
{
  int V;
  Vertex ver;
  AdjList array;
} *Graph;
struct node
{
  int v;
  struct node *next;
  struct node *prev;
};
int h(Graph g, int u)
{
  return g->ver[u].h;
}

int e(Graph g, int u)
{
  return g->ver[u].e_flow;
}

struct node *addNode(struct node *l, int v)
{
  struct node *n = (struct node *) malloc(sizeof(struct node));
  n->v = v;
  n->next = l;
  n->prev = 0;
  if (l != 0)
  {
    l->prev = n;
  }
  else
  {
    
  }

  return n;
}

void swapNodes(struct node **head, struct node **n)
{
  struct node *prevX = (*n)->prev;
  struct node *currX = *n;
  struct node *prevY = 0;
  struct node *currY = *head;
  struct node *temp;
  if ((*head)->v == (*n)->v)
  {
    return;
  }
  else
  {
    
  }

  if (prevX != 0)
  {
    prevX->next = currY;
  }
  else
  {
    *head = currY;
  }

  if (prevY != 0)
  {
    prevY->next = currX;
  }
  else
  {
    *head = currX;
  }

  temp = currY->next;
  currY->next = currX->next;
  currX->next = temp;
}

void freeList(struct node *l)
{
  struct node *n;
  while (l != 0)
  {
    n = l;
    l = l->next;
    free(n);
  }

}

AdjListNode newAdjListNode(int dest, int cap)
{
  AdjListNode newNode = (AdjListNode) malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->cap = cap;
  newNode->flow = 0;
  newNode->next = 0;
  return newNode;
}

Graph newGraph(int V)
{
  Graph g = (Graph) malloc(sizeof(struct Graph));
  g->V = V;
  g->ver = (Vertex) malloc(V * (sizeof(struct Vertex)));
  g->array = (AdjList) malloc(V * (sizeof(struct AdjList)));
  int i;
  for (i = 0; i < V; i++)
  {
    g->array[i].head = 0;
    g->ver[i].h = 0;
    g->ver[i].e_flow = 0;
  }

  return g;
}

void freeGraph(Graph g)
{
  int i;
  for (i = 0; i < g->V; i++)
  {
    AdjListNode adj = g->array[i].head;
    while (adj != 0)
    {
      AdjListNode aux = adj->next;
      free(adj);
      adj = aux;
    }

  }

  free(g->array);
  free(g->ver);
  free(g);
}

void addEdge(Graph g, int src, int dest, int cap)
{
  AdjListNode newNode = newAdjListNode(dest, cap);
  newNode->next = g->array[src].head;
  g->array[src].head = newNode;
  newNode = newAdjListNode(src, cap);
  newNode->next = g->array[dest].head;
  g->array[dest].head = newNode;
}

void printGraph(Graph g)
{
  int i;
  for (i = 0; i < g->V; i++)
  {
    AdjListNode adj = g->array[i].head;
    while (adj != 0)
    {
      adj = adj->next;
    }

    printf("\n");
  }

}

int capacity(Graph g, int u, int v)
{
  AdjListNode adj = g->array[u].head;
  while (adj != 0)
  {
    if (adj->dest == v)
    {
      return adj->cap;
    }
    else
    {
      
    }

    adj = adj->next;
  }

  return 0;
}

int residualCapacity(Graph g, int u, int v)
{
  int c = 0;
  int f = 0;
  AdjListNode adj = g->array[u].head;
  while (adj != 0)
  {
    if (adj->dest == v)
    {
      c = adj->cap;
      f = adj->flow;
      break;
    }
    else
    {
      
    }

    adj = adj->next;
  }

  return c - f;
}

int flow(Graph g, int u, int v)
{
  AdjListNode adj = g->array[u].head;
  while (adj != 0)
  {
    if (adj->dest == v)
    {
      return adj->flow;
    }
    else
    {
      
    }

    adj = adj->next;
  }

  return 0;
}

void changeFlow(Graph g, int u, int v, int flow)
{
  AdjListNode adj = g->array[u].head;
  while (adj != 0)
  {
    if (adj->dest == v)
    {
      adj->flow = flow;
    }
    else
    {
      
    }

    adj = adj->next;
  }

}

int PUSH(Graph g, int u, int v)
{
  int aux = residualCapacity(g, u, v);
  if (((e(g, u) > 0) && (aux > 0)) && (h(g, u) == (h(g, v) + 1)))
  {
    int f = flow(g, u, v);
    if (aux > e(g, u))
    {
      aux = e(g, u);
    }
    else
    {
      
    }

    changeFlow(g, u, v, aux + f);
    changeFlow(g, v, u, (-1) * f);
    g->ver[u].e_flow -= aux;
    g->ver[v].e_flow += aux;
    return 1;
  }
  else
  {
    
  }

  return 0;
}

int canRELABEL(Graph g, int u)
{
  AdjListNode n = g->array[u].head;
  while (n != 0)
  {
    if (g->ver[n->dest].h >= h(g, u))
    {
      return 1;
    }
    else
    {
      
    }

    n = n->next;
  }

  return g->ver[u].e_flow > 0;
}

void RELABEL(Graph g, int u)
{
  if (canRELABEL(g, u))
  {
    int min;
    AdjListNode adj = g->array[u].head;
    min = g->ver[adj->dest].h;
    while (adj != 0)
    {
      if (min > g->ver[adj->dest].h)
      {
        min = g->ver[adj->dest].h;
      }
      else
      {
        
      }

      adj = adj->next;
    }

    g->ver[u].h = 1 + min;
  }
  else
  {
    
  }

}

void PREFLOW(Graph g, int s)
{
  g->ver[s].h = g->V;
  AdjListNode adj = g->array[s].head;
  while (adj != 0)
  {
    int cap = capacity(g, s, adj->dest);
    changeFlow(g, s, adj->dest, cap);
    changeFlow(g, adj->dest, s, (-1) * cap);
    g->ver[adj->dest].e_flow = cap;
    g->ver[s].e_flow -= cap;
    adj = adj->next;
  }

}

void DISCHARGE(Graph g, int u)
{
  AdjListNode v = g->array[u].head;
  while (e(g, u) > 0)
  {
    if (v == 0)
    {
      RELABEL(g, u);
      v = g->array[u].head;
    }
    else
    {
      PUSH(g, u, v->dest);
    }

    v = v->next;
  }

}

int maxFlow(Graph g)
{
  AdjListNode adj = g->array[0].head;
  int fluxo_max = 0;
  while (adj != 0)
  {
    AdjListNode inv = g->array[adj->dest].head;
    fluxo_max += adj->flow - inv->flow;
    adj = adj->next;
  }

  return fluxo_max;
}

int RELABEL_TO_FRONT(Graph g, int s, int t)
{
  int old_h;
  int i;
  struct node *L = 0;
  struct node *u;
  for (i = g->V; i > 1; i--)
  {
    L = addNode(L, i);
  }

  PREFLOW(g, s);
  u = L;
  while (u != 0)
  {
    old_h = h(g, u->v);
    DISCHARGE(g, u->v);
    if (h(g, u->v) > old_h)
    {
      swapNodes(&L, &u);
    }
    else
    {
      
    }

    u = u->next;
    printf("\n");
  }

  freeList(L);
  return maxFlow(g);
}

int main(int argc, const char *argv[])
{
  int fornecedores;
  int estacoes_abastecimento;
  int ligacoes;
  int producao_fornecedor;
  int capacidade_estacao;
  int origem;
  int destino;
  int capacidade_ligacao;
  int total_vertices;
  int i;
  int nova_estacao;
  fornecedores = new_sym_var(sizeof(int) * 8);
  estacoes_abastecimento = new_sym_var(sizeof(int) * 8);
  ligacoes = new_sym_var(sizeof(int) * 8);
  total_vertices = (fornecedores + (2 * estacoes_abastecimento)) + 2;
  Graph grafo = newGraph(total_vertices);
  for (i = 0; i < fornecedores; i++)
  {
    producao_fornecedor = new_sym_var(sizeof(int) * 8);
    addEdge(grafo, 0, i + 2, producao_fornecedor);
  }

  for (i = 0; i < estacoes_abastecimento; i++)
  {
    nova_estacao = ((i + estacoes_abastecimento) + fornecedores) + 2;
    capacidade_estacao = new_sym_var(sizeof(int) * 8);
    addEdge(grafo, (i + 2) + fornecedores, nova_estacao, capacidade_estacao);
  }

  for (i = 0; i < ligacoes; i++)
  {
    origem = new_sym_var(sizeof(int) * 8);
    destino = new_sym_var(sizeof(int) * 8);
    capacidade_ligacao = new_sym_var(sizeof(int) * 8);
    if (origem >= (fornecedores + 2))
    {
      addEdge(grafo, origem + estacoes_abastecimento, destino, capacidade_ligacao);
    }
    else
    {
      if (destino)
      {
        addEdge(grafo, origem, destino, capacidade_ligacao);
      }
      else
      {
        
      }

    }

  }

  printf("fluxo maximo= %d\n", RELABEL_TO_FRONT(grafo, 0, 1));
  return 0;
}
