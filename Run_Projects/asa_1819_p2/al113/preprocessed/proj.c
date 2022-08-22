/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
  int destination;
  int cap;
  int flow;
  int main;
  struct node *rev;
  struct node *next;
} *Link;
typedef struct list
{
  Link head;
} *List;
List init_list()
{
  List l = (List) malloc(sizeof(struct list));
  l->head = 0;
  return l;
}

void insert_list(List l, int d, int c, int m, Link r)
{
  Link new = (Link) malloc(sizeof(struct node));
  new->destination = d;
  new->cap = c;
  new->flow = 0;
  new->main = m;
  new->rev = r;
  new->next = l->head;
  l->head = new;
}

void clear_list(List l)
{
  Link x = l->head;
  Link aux;
  while (x != 0)
  {
    aux = x;
    x = aux->next;
    free(aux);
  }

  l->head = 0;
}

typedef struct Qnode
{
  int key;
  struct Qnode *next;
} *QNode;
typedef struct queue
{
  QNode front;
  QNode rear;
} *Queue;
QNode newNode(int k)
{
  QNode new = (QNode) malloc(sizeof(struct Qnode));
  new->key = k;
  new->next = 0;
  return new;
}

Queue init_queue()
{
  Queue q = (Queue) malloc(sizeof(struct queue));
  q->front = (q->rear = 0);
  return q;
}

void enQueue(Queue q, int k)
{
  QNode temp = newNode(k);
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

int deQueue(Queue q)
{
  QNode temp = q->front;
  q->front = q->front->next;
  if (q->front == 0)
  {
    q->rear = 0;
  }
  else
  {
    
  }

  int key = temp->key;
  free(temp);
  return key;
}

int queue_empty(Queue q)
{
  return (q->front == 0) ? (1) : (0);
}

typedef struct graph
{
  int numVertices;
  int numSuppliers;
  List *vertices;
} *Graph;
Graph init_graph()
{
  Graph g = (Graph) malloc(sizeof(struct graph));
  g->numVertices = 0;
  g->numSuppliers = 0;
  g->vertices = 0;
  return g;
}

void free_graph(Graph g)
{
  int i;
  for (i = 0; i < g->numVertices; i++)
  {
    if (g->vertices[i] != 0)
    {
      clear_list(g->vertices[i]);
    }
    else
    {
      
    }

    free(g->vertices[i]);
  }

  free(g->vertices);
  free(g);
}

int push(int *e, int u, int v, int curr_f)
{
  int flow = (e[u] < curr_f) ? (e[u]) : (curr_f);
  e[u] -= flow;
  e[v] += flow;
  return flow;
}

void relabel(Graph g, int *h, int u)
{
  Link k;
  int min = -1;
  for (k = g->vertices[u]->head; k != 0; k = k->next)
  {
    if ((k->cap - k->flow) <= 0)
    {
      continue;
    }
    else
    {
      
    }

    min = (min == (-1)) ? (h[k->destination]) : ((min < h[k->destination]) ? (min) : (h[k->destination]));
  }

  h[u] = min + 1;
}

void discharge(Graph g, Queue q, int *e, int *h, int u)
{
  int curr_f;
  int prev_e;
  Link k;
  for (k = g->vertices[u]->head; (k != 0) && (e[u] != 0); k = k->next)
  {
    if (((curr_f = k->cap - k->flow) > 0) && (h[u] > h[k->destination]))
    {
      prev_e = e[k->destination];
      curr_f = push(e, u, k->destination, curr_f);
      k->flow += curr_f;
      k->rev->flow = -k->flow;
      if ((prev_e == 0) && (k->destination != 1))
      {
        enQueue(q, k->destination);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  if (e[u] != 0)
  {
    relabel(g, h, u);
    enQueue(q, u);
  }
  else
  {
    
  }

}

int pushRelabel(Graph g)
{
  int i;
  int flow;
  Link k;
  int *e = (int *) malloc((sizeof(int)) * g->numVertices);
  int *h = (int *) malloc((sizeof(int)) * g->numVertices);
  Queue q = init_queue();
  for (i = 0; i < g->numVertices; i++)
  {
    h[i] = 0;
    e[i] = 0;
  }

  h[0] = g->numVertices;
  for (k = g->vertices[0]->head; k != 0; k = k->next)
  {
    if (k->main != 0)
    {
      k->flow = k->cap;
      k->rev->flow = -k->cap;
      e[k->destination] = k->cap;
      e[0] -= k->cap;
      enQueue(q, k->destination);
    }
    else
    {
      
    }

  }

  while (!queue_empty(q))
  {
    i = deQueue(q);
    discharge(g, q, e, h, i);
  }

  flow = e[1];
  free(e);
  free(h);
  free(q);
  return flow;
}

void getReach(Graph g, int v, int *reach)
{
  Link k;
  for (k = g->vertices[v]->head; k != 0; k = k->next)
  {
    if (((k->rev->cap - k->rev->flow) != 0) && (reach[k->destination] == 0))
    {
      reach[k->destination] = 1;
      getReach(g, k->destination, reach);
    }
    else
    {
      
    }

  }

}

void performAlgorithm(Graph g)
{
  int i;
  int j;
  int maxFlow;
  Link k;
  int *reach = (int *) malloc((sizeof(int)) * g->numVertices);
  int *critical = (int *) malloc((sizeof(int)) * g->numVertices);
  for (i = 0; i < g->numVertices; i++)
  {
    critical[i] = 0;
    reach[i] = 0;
  }

  maxFlow = pushRelabel(g);
  reach[1] = 1;
  getReach(g, 1, reach);
  printf("%d\n", maxFlow);
  int space = 0;
  for (i = g->numSuppliers + 2; i < g->numVertices; i += 2)
  {
    if ((reach[i] == 0) && (reach[i + 1] == 1))
    {
      if (space)
      {
        printf(" ");
      }
      else
      {
        space = 1;
      }

      printf("%d", (i < (g->numSuppliers + 2)) ? (i) : (((((i - g->numSuppliers) - 2) / 2) + g->numSuppliers) + 2));
    }
    else
    {
      
    }

  }

  printf("\n");
  for (i = 2; i < g->numVertices; i++)
  {
    if (i >= (g->numSuppliers + 2))
    {
      i++;
    }
    else
    {
      
    }

    if (reach[i] == 0)
    {
      for (k = g->vertices[i]->head; k != 0; k = k->next)
      {
        if ((k->main != 0) && (reach[k->destination] == 1))
        {
          critical[(k->destination < (g->numSuppliers + 2)) ? (k->destination) : (((((k->destination - g->numSuppliers) - 2) / 2) + g->numSuppliers) + 2)] = 1;
        }
        else
        {
          
        }

      }

      for (j = 0; j < g->numVertices; j++)
      {
        if (critical[j])
        {
          printf("%d %d\n", (i < (g->numSuppliers + 2)) ? (i) : (((((i - g->numSuppliers) - 2) / 2) + g->numSuppliers) + 2), j);
          critical[j] = 0;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

  free(critical);
  free(reach);
}

int main(int argc, char *argv[])
{
  int suppliers;
  int stations;
  int connections;
  int numV;
  int i;
  int o;
  int d;
  int c;
  Link k;
  Graph network = init_graph();
  suppliers = new_sym_var(sizeof(int) * 8);
  stations = new_sym_var(sizeof(int) * 8);
  connections = new_sym_var(sizeof(int) * 8);
  numV = (suppliers + (stations * 2)) + 2;
  network->numVertices = numV;
  network->numSuppliers = suppliers;
  network->vertices = (List *) malloc((sizeof(List)) * numV);
  for (i = 0; i < numV; i++)
    network->vertices[i] = init_list();

  for (i = 2; i < (suppliers + 2); i++)
  {
    c = new_sym_var(sizeof(int) * 8);
    insert_list(network->vertices[0], i, c, 1, 0);
  }

  for (; i < numV; i += 2)
  {
    c = new_sym_var(sizeof(int) * 8);
    insert_list(network->vertices[i], i + 1, c, 1, 0);
  }

  for (i = 0; i < connections; i++)
  {
    o = new_sym_var(sizeof(int) * 8);
    d = new_sym_var(sizeof(int) * 8);
    c = new_sym_var(sizeof(int) * 8);
    if (o <= (suppliers + 1))
    {
      insert_list(network->vertices[o], (d < (suppliers + 2)) ? (d) : (((((d - suppliers) - 2) * 2) + suppliers) + 2), c, 1, 0);
    }
    else
    {
      insert_list(network->vertices[(o < (suppliers + 2)) ? (o) : ((((((o - suppliers) - 2) * 2) + suppliers) + 2) + 1)], (d < (suppliers + 2)) ? (d) : (((((d - suppliers) - 2) * 2) + suppliers) + 2), c, 1, 0);
    }

  }

  for (i = 0; i < numV; i++)
  {
    for (k = network->vertices[i]->head; k != 0; k = k->next)
    {
      if (k->main != 0)
      {
        insert_list(network->vertices[k->destination], i, 0, 0, k);
        k->rev = network->vertices[k->destination]->head;
      }
      else
      {
        
      }

    }

  }

  performAlgorithm(network);
  free_graph(network);
  return 0;
}

